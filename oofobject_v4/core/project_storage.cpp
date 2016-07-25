#include "project_storage.hpp"

// ===== StorageDependency =====

std::ostream &
operator<<
(
	std::ostream & os,
	const StorageDependency & sd
)
{
	os << sd.to << " : " << sd.where << " <- " << sd.from ;
	return os ;
}
		
// ===== Type =====

// --- CONSTRUCTORS ---

Type::Type
(
	const std::string & extension,
	const std::string & name
)
{
	* static_cast< std::string * > ( this ) = extension ;
	name_ = name ;
}

std::ostream &
operator<<
(
	std::ostream & os,
	const Type & t
)
{
	os << "( " << t.name_ << " : " << &( t[0] ) << " )" ;
	return os ;
}

// ===== ProjectStorage =====

// --- CONSTRUCTORS ---

ProjectStorage::ProjectStorage
()
{
	// get pointers to the InstanceManager and the LogDevice
	im_ = InstanceManager::get_instance() ;
	ld_ = LogDevice::get_instance() ;
	
	// initialize project info
	project_code_ = ld_->get_time_code() ;
	project_name_ = "" ;
	project_path_ = "" ;
}

// --- DESTRUCTORS ---

ProjectStorage::~ProjectStorage
()
{
	// delete every ObjectStorage
	while( !( map_storage_.empty() ) )
	{
		delete ( *( map_storage_.begin() ) ).second ;
		map_storage_.erase( map_storage_.cbegin() ) ;
	}
}

// --- METHODS ---

void
ProjectStorage::add_map
(
	const Type & type,
	IObjectStorage * project_storage
)
{
	// add the type in the vector and the ObjectStorage in the map
	types_.push_back( type ) ;
	map_storage_.insert( std::make_pair( type.name_, project_storage ) ) ;
}

void
ProjectStorage::display_map
()
const
{
	std::cout << map_storage_ << std::endl ;
}

std::string
ProjectStorage::find_extension
(
	const std::string & type
)
const
{
	std::string result = "" ;
	std::vector< Type >::const_iterator cit ;
	
	// look for the type and return the extension
	cit = std::find_if( types_.cbegin(), types_.cend(),
						[&type] (const Type & t) -> bool { return t.name_ == type ; } ) ;
	
	result = ( *cit ) ;
	return result ;
}

std::string
ProjectStorage::find_type
(
	const std::string & extension
)
const
{
	std::string result = "" ;
	std::vector< Type >::const_iterator cit ;
	
	// look for the extension and return the type
	cit = std::find( types_.cbegin(), types_.cend(), extension ) ;
	
	if( cit == types_.cend() )
	{
		// Project is not a real type so we need to check the extension manually
		if( extension == ".oof_proj" )
		{
			result = "Project" ;
		}
		else
		{
			ld_->log( "Extension " + extension + " is not recognized", LOG_FLAG::ERROR ) ;
		}
	}
	else
	{
		result = ( *cit ).name_ ;
	}
	
	return result ;
}

void
ProjectStorage::load
(
	const std::string & address
)
{	
	// get extension and find the right type
	size_t pos = address.find_last_of('.') ;
	std::string type = find_type( address.substr( pos ) ) ;
	
	if( !( type.empty() ) )
	{
		if( type == "Project" )
		{
			load_project( address ) ;
		}
		else
		{
			load_file( address ) ;
		}
	}
}

void
ProjectStorage::load_all_dependencies
()
const
{
	std::vector< IObjectStorage * > os = extract( map_storage_ ) ;
	std::vector< IObjectStorage * >::iterator it ;
	
	// call the load_dependenceis for each ObjectStorage
	for( it = os.begin() ; it != os.end() ; ++it )
	{
		( *it )->load_dependencies() ;
	}
}

void
ProjectStorage::load_file
(
	const std::string & address,
	const std::string & type
)
{
	std::string tmp ;
	
	// if the type is not known, we just look the extension
	if( type.empty() )
	{
		tmp = find_type( address ) ;
	}
	else
	{
		tmp = type ;
	}
	
	// find the right ObjectStorage
	IObjectStorage * ios = map_storage_[ tmp ] ;
	
	if( ios == nullptr )
	{
		ld_->log( "No loader for the type : " + tmp, LOG_FLAG::ERROR ) ;
	}
	else
	{
		// loading of the file
		ios->load( address ) ;
	}
}

void
ProjectStorage::load_files
(
	const std::map< std::string, std::string > & files
)
{
	std::map< std::string, std::string >::const_iterator cit ;
	
	for( cit = files.cbegin() ; cit != files.cend() ; ++cit )
	{
		// call the load_file function for each file of the project
		load_file( ( *cit ).second, ( *cit ).first ) ;
	}
	
	// create dependencies if it's possible
	load_all_dependencies() ;
}

void
ProjectStorage::load_files
(
	const std::vector< std::string > & files
)
{
	std::vector< std::string >::const_iterator cit ;
	
	for( cit = files.cbegin() ; cit != files.cend() ; ++cit )
	{
		// call the load_file function for each file
		load_file( *cit ) ;
	}
	
	// create dependencies if it's possible
	load_all_dependencies() ;
}

void
ProjectStorage::load_project
(
	const std::string & address
)
{
	std::ifstream file( address.c_str(), std::ios::in ) ;
	
	if( file )
	{
		// return true if InstanceManager is empty
		bool nothing_stored_before = read_project_info( file ) ;
		
		if( nothing_stored_before )
		{
			// update of project info in order to continue
			size_t pos = address.find_last_of( "/" ) ;
			project_path_ = address.substr( 0, pos + 1 ) ;
		}
		
		std::map< std::string, std::string > objects_list = read_project_files( file ) ;
		file.close() ;
		
		load_files( objects_list ) ;
		
		if( nothing_stored_before )
		{
			// update last_save_ in order to avoid a useless save
			last_save_ = time( NULL ) ;
		}
	}
	else
	{
		ld_->log( "Impossible to load a project", LOG_FLAG::ERROR ) ;
		ld_->log( "Impossible to open " + address + " in read mode", LOG_FLAG::REPORT ) ;
	}
}

std::map< std::string, std::string >
ProjectStorage::read_project_files
(
	std::ifstream & file
)
{
	std::string line ;
	std::map< std::string, std::string > objects_list ;
	//          typename     code

	std::getline( file, line ) ; // ===== FILES =====
	std::getline( file, line ) ; // empty line
	
	size_t pos = 0 ;
	std::string type ;
	std::string address ;
	while( std::getline( file, line ) ) // typename file
	{
		if( !( line.empty() ) )
		{
			pos = line.find( " " ) ;
			
			// extract the type and the address
			type = line.substr( 0, pos ) ;
			address = project_path_ + line.substr( pos + 1 ) + find_extension( type ) ;
			
			objects_list.insert( make_pair( type, address ) ) ;
		}
	}
	
	return objects_list ;
}

bool
ProjectStorage::read_project_info
(
	std::ifstream & file
)
{
	bool nothing_stored_before = im_->empty() ;
	std::string line ;
	
	std::getline( file, line ) ; // ===== INFO =====
	std::getline( file, line ) ; // empty line
	
	std::getline( file, line ) ; // project_code_ - __________
	if( nothing_stored_before )
	{
		ld_->log( "The current session is going to continue the project", LOG_FLAG::REPORT ) ;
		project_code_ = line.substr( 16, line.length() - 16 ) ;
		Config::__SESSION__ = project_code_ ;
	}
	else
	{
		ld_->log( "The project is going to be merge with in the current session", LOG_FLAG::REPORT ) ;
	}
	
	std::getline( file, line ) ; // project_name_ - ???
	if( nothing_stored_before )
	{
		project_name_ = line.substr( 16, line.length() - 16 ) ;
	}
	
	std::getline( file, line ) ; // empty line
	
	return nothing_stored_before ;
}

void
ProjectStorage::save
(
	const std::string & project_name,
	bool all
)
{
	bool create_project = false ;
	bool test = true ;
	
	if( project_name_.empty() )
	{
		if( project_name.empty() )
		{
			project_name_ = Config::__SESSION__ ;
			
			ld_->log( "Project doesn't have a name", LOG_FLAG::WARNING ) ;
			ld_->log( "The project is going to be named : " + project_name_, LOG_FLAG::REPORT ) ;
		}
		else
		{
			project_name_ = project_name ;
			
			ld_->log( "New project : " + project_name_, LOG_FLAG::REPORT ) ;
		}
		
		create_project = true ;
	}
	
	if( create_project )
	{
		project_path_ = Config::__DIR__ ;
		project_path_ += "/" + Config::__PROJECT__ ;
		
		// test the directory
		test &= test_directory( project_path_ ) ;
		
		project_path_ += project_name_ + "/" ;
		
		// test the subdirectory
		test &= test_directory( project_path_ ) ;
	}
	
	if( test )
	{
		// clear the project file
		std::string filename = project_path_ + project_name_ + ".oof_proj" ;
		std::ofstream file( filename.c_str(), std::ios::out | std::ios::trunc ) ;
		
		if( file )
		{
			// this part could be parallize between each ObjectStorage< T >
			std::vector< IOOF_OBJECT * > objects ;
			
			// find which objects need to be saved
			
			if( all )
			{
				objects = im_->extract( last_save_ ) ;
			}
			else
			{
				objects = im_->extract() ;
			}
			
			// if nothing is new, we don't need to save anything
			if( !( objects.empty() ) )
			{
				std::vector< IOOF_OBJECT * >::const_iterator cit ;
				
				// call ObjectStorage< T >::save for each object
				for( cit = objects.cbegin() ; cit != objects.cend() ; ++cit )
				{
					IObjectStorage * ios = map_storage_[ ( *cit )->get_typename() ] ;
					ios->save( project_path_, ( *cit ) ) ;
				}
				
				// save the project file
				save_project( file ) ;
			}
			file.close() ;
			
			// update
			last_save_ = time( NULL ) ;
		}
		else
		{
			ld_->log( "Impossible to save the project", LOG_FLAG::ERROR ) ;
			ld_->log( "Impossible to open " + filename + " in write mode", LOG_FLAG::REPORT ) ;
		}
	}
	else
	{
		ld_->log( "Impossible to create directories for the log system", LOG_FLAG::ERROR ) ;
	}
}

void
ProjectStorage::save_object
(
	const IOOF_OBJECT * object
)
{
	// if the project_path is not defined
	std::string path = project_path_ ;
	
	if( path.empty() )
	{
		// put the object on __DIR__
		path = Config::__DIR__ ;
	}
	
	IObjectStorage * ios = map_storage_[ object->get_typename() ] ;
	
	// no need to check the validity of the ObjectStorage
	ios->save( path, object ) ;
}

void
ProjectStorage::save_project
(
	std::ofstream & file
)
const
{
	file << "===== INFO =====" << std::endl ;
	file << std::endl ;
	
	file << "project_code_ - " << project_code_ << std::endl ;
	file << "project_name_ - " << project_name_ << std::endl ;
	
	file << std::endl ;
	file << "===== FILES =====" << std::endl ;
	file << std::endl ;
	
	InstanceManager::const_reverse_iterator crit ;
	
	// we use the reverse order in order to simplify the add in the map when we are going to load
	for( crit = im_->crbegin() ; crit != im_->crend() ; ++crit )
	{
		file << ( *crit ).first << " " << ( *crit ).second->get_code() << std::endl ;
	}
}
