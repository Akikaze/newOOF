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
	const std::string & filename
)
{
	std::ifstream project_file( filename.c_str(), std::ios::in ) ;
	
	if( project_file )
	{
		// read Project info
		std::string line ;
		std::getline( project_file, line ) ; // ===== INFO =====
		std::getline( project_file, line ) ; // empty line
		
		std::getline( project_file, line ) ; // project_name_ - ???
		project_name_ = line.substr( 16, line.length() - 16 ) ;
		
		std::getline( project_file, line ) ; // empty line
		std::getline( project_file, line ) ; // ===== FILES =====
		std::getline( project_file, line ) ; // empty line
		
		std::map< std::string, std::string > objects_list ;
		//         typename      address
		size_t pos = 0 ;
		while( std::getline( project_file, line ) ) // filename
		{
			if( !( line.empty() ) )
			{
				pos = line.find( " " ) ;
				objects_list.insert( make_pair( line.substr( 0, pos ), line.substr( pos + 1 ) ) ) ;
			}
		}
		
		project_file.close() ;
		
		// this for loop could be parallize with extract method (cf InstanceManager::extract)
		std::map< std::string, std::string >::const_iterator cit ;
		for( cit = objects_list.cbegin() ; cit != objects_list.cend() ; ++cit )
		{
			IObjectStorage * os = map_storage_[ ( *cit ).first ] ;
			os->load( ( *cit ).second ) ;
		}
		
		// this for loop could be parallize
		/*
		std::vector< IObjectStorage * >::const_iterator citOS ;
		for( citOS = map_storage_.cbegin() ; citOS != map_storage_.cend() ; ++citOS )
		{
			// if there are dependencies, call the load_dependencies method
			if( !( ( *citOS )->dependencies_.empty() ) )
			{
				( *citOS )->load_dependencies() ;
			}
		}
		*/
	}
	else
	{
		std::cerr << "Impossible to open the project file." << std::endl ;
	}
	
	last_save_ = time( NULL ) ;
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
	
	// if the project name is still missing, it's a problem
	if( project_name_.empty() )
	{
		std::cerr << "The project doesn't have a name." << std::endl ;
	}
	else
	{
		if( project_exist == false )
		{
			// create the project folder
		}
		
		// Sort instances by last_update_ time
		std::vector< IOOF_OBJECT * > objects = im_->extract( last_save_ ) ;
		std::vector< IOOF_OBJECT * >::const_iterator ioof_cit ;
		
		for( ioof_cit = objects.cbegin() ; ioof_cit != objects.cend() ; ++ioof_cit )
		{
			IObjectStorage * ios = map_storage_[ ( *ioof_cit )->get_typename() ] ;
			// ios->save( folder ) ;
		}
	
		// save the project file
		// type file_address
		// don't forget to add all im links in the file in map reverse order in order to boost the load
		
		last_save_ = time( NULL ) ;
	}
}
