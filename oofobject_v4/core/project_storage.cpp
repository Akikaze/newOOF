#include "project_storage.hpp"

// ===== IObjectStorage =====

// --- DESTRUCTORS ---

IObjectStorage::~IObjectStorage
()
{
}

// ===== ProjectStorage =====

// --- CONSTRUCTORS ---

ProjectStorage::ProjectStorage
()
{
	im_ = InstanceManager::get_instance() ;
	ld_ = LogDevice::get_instance() ;
	
	project_name_ = "" ;
	project_path_ = "" ;
}

// --- DESTRUCTORS ---

ProjectStorage::~ProjectStorage
()
{
	while( !( map_storage_.empty() ) )
	{
		delete ( *( map_storage_.begin() ) ).second ;
		map_storage_.erase( map_storage_.cbegin() ) ;
	}
}

// --- METHODS ---

void
ProjectStorage::add_list
(
	const std::string & type,
	IObjectStorage * project_storage
)
{
	map_storage_.insert( make_pair( type, project_storage ) ) ;
}

void
ProjectStorage::display_list
()
const
{
	std::cout << map_storage_ << std::endl ;
}

void
ProjectStorage::load
(
	const std::string & project_path
)
{
	std::ifstream file( project_path.c_str(), std::ios::in ) ;
	
	if( file )
	{
		// read Project info
		std::string line ;
		std::getline( file, line ) ; // ===== INFO =====
		std::getline( file, line ) ; // empty line
		
		std::getline( file, line ) ; // project_name_ - ???
		project_name_ = line.substr( 16, line.length() - 16 ) ;
		
		std::getline( file, line ) ; // empty line
		std::getline( file, line ) ; // ===== FILES =====
		std::getline( file, line ) ; // empty line
		
		std::map< std::string, std::string > objects_list ;
		//          typename     address
		size_t pos = 0 ;
		while( std::getline( file, line ) ) // filename
		{
			if( !( line.empty() ) )
			{
				pos = line.find( " " ) ;
				objects_list.insert( make_pair( line.substr( 0, pos ), line.substr( pos + 1 ) ) ) ;
			}
		}
		
		file.close() ;
		
		// this for loop could be parallize with extract method (cf InstanceManager::extract)
		std::map< std::string, std::string >::const_iterator cit ;
		for( cit = objects_list.cbegin() ; cit != objects_list.cend() ; ++cit )
		{
			IObjectStorage * os = map_storage_[ ( *cit ).first ] ;
			os->load( ( *cit ).second ) ;
		}
		
		// this for loop could be parallize
		std::map< std::string, IObjectStorage * >::const_iterator map_cit ;
		for( map_cit = map_storage_.cbegin() ; map_cit != map_storage_.cend() ; ++map_cit )
		{
			// if there are dependencies, call the load_dependencies method
			if( !( ( ( *map_cit ).second )->dependencies_.empty() ) )
			{
				( ( *map_cit ).second )->load_dependencies() ;
			}
		}
		last_save_ = time( NULL ) ;
	}
	else
	{
		ld_->log( "Impossible to load a project", LOG_FLAG::ERROR ) ;
		ld_->log( "Impossible to open " + project_path + " in read mode", LOG_FLAG::REPORT ) ;
	}
	
}

void
ProjectStorage::save
(
	const std::string & project_name,
	bool all
)
{
	bool project_exist = true ;
		
	// if there is no project at the start
	if( project_name_.empty() )
	{
		// use the parameter and indicate that we need to create a folder
		project_exist = false ;
		project_name_ = project_name ;
	}
	else if( !( project_name.empty() ) && project_name_ != project_name )
	{
		// we need to test the new path
		project_exist = false ;
		project_name_ = project_name ;
	}
	
	// if the project name is still missing, it's a problem
	if( project_name_.empty() )
	{
		ld_->log( "The project doesn't have a name.", LOG_FLAG::ERROR ) ;
		ld_->log( "At the first save, you need to give a name for the project.",LOG_FLAG::REPORT ) ;
	}
	else
	{
		if( project_exist == false )
		{
			// test __DIR__
			project_path_ = __DIR__ ;
			test_directory( project_path_ ) ;
			
			// test __DIR__/__PROJECT__
			project_path_ += "/" + std::string( __PROJECT__ ) ;
			test_directory( project_path_ ) ;
			
			// test __DIR__/__PROJECT__/project_name_
			project_path_ += project_name_ ;
			test_directory( project_path_ ) ;
		}
		
		// Sort instances by last_update_ time
		std::vector< IOOF_OBJECT * > objects = im_->extract( last_save_ ) ;
		std::vector< IOOF_OBJECT * >::const_iterator ioof_cit ;
		
		for( ioof_cit = objects.cbegin() ; ioof_cit != objects.cend() ; ++ioof_cit )
		{
			IObjectStorage * ios = map_storage_[ ( *ioof_cit )->get_typename() ] ;
			ios->save( project_path_, *ioof_cit ) ;
		}
		
		std::string project_file = std::string( __DIR__ ) ;
		project_file += "/" + std::string( __PROJECT__ ) ;
		project_file += project_name_ + ".project" ;
		
		// clear the file everytime
		std::ofstream file( project_file.c_str(), std::ios::out | std::ios::trunc ) ;
		
		if( file )
		{
			/*
			 * We use the reverse order to simplify the load. At each new
			 * object, the system is going to load it at the beginning of
			 * the map. A lot of comparison will be avoid.
			 */
			InstanceManager::const_reverse_iterator crit ;
			
			for( crit = im_->crbegin() ; crit != im_->crend() ; ++crit )
			{
				file << ( *crit ).first << " " << ( *crit ).second << std::endl ;
			}
			
			file.close() ;
			last_save_ = time( NULL ) ;
		}
		else
		{
			ld_->log( "Impossible to save the project", LOG_FLAG::ERROR ) ;
			ld_->log( "Impossible to open " + project_file + " in write mode", LOG_FLAG::REPORT ) ;
		}
		
	}
}
