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
#ifdef __DEBUG__
	std::cout << "ProjectStorage construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

ProjectStorage::~ProjectStorage
()
{
#ifdef __DEBUG__
	std::cout << "ProjectStorage destruction" << std::endl ;
#endif
	
	while( !( list_storage_.empty() ) )
	{
		delete list_storage_[ 0 ] ;
		list_storage_.erase( list_storage_.cbegin() ) ;
	}
}

// --- METHODS ---

void
ProjectStorage::add_list
(
	IObjectStorage * project_storage
)
{
	list_storage_.push_back( project_storage ) ;
}

void
ProjectStorage::display_list
()
const
{
	std::cout << list_storage_ << std::endl ;
}

IObjectStorage *
ProjectStorage::find_ObjectStorage
(
	const std::string & filename
)
{
	IObjectStorage * pointer = NULL ;
	std::string extension = filename.substr( filename.find_last_of( '.' ) + 1 ) ;
	
	// sort extension to find the good ObjectStorage
	if( extension.empty() )
	{
		std::cerr << "The extension of " << filename << " was not found." << std::endl ;
	}
	/*
	// Template for new object
	else if( extension == "" )
	{
		pointer = ObjectStorage< type >::get_instance() ;
	}
	*/
	else
	{
		std::cerr << "The extension ." << extension << " is not recognized." << std::endl ;
	}
	
	return pointer ;
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
		
		std::vector< std::string > objects_list ;
		while( std::getline( project_file, line ) ) // filename
		{
			if( !( line.empty() ) )
			{
				objects_list.push_back( line ) ;
			}
		}
		
		project_file.close() ;
		
		// this for loop could be parallize
		std::vector< std::string >::const_iterator cit ;
		for( cit = objects_list.cbegin() ; cit != objects_list.cend() ; ++cit )
		{
			// find the perfect ObjectStorage and call the load method
			IObjectStorage * os = find_ObjectStorage( *cit ) ;
			os->load( *cit ) ;
		}
		
		// this for loop could be parallize
		std::vector< IObjectStorage * >::const_iterator citOS ;
		for( citOS = list_storage_.cbegin() ; citOS != list_storage_.cend() ; ++citOS )
		{
			// if there are dependencies, call the load_dependencies method
			if( !( ( *citOS )->dependencies_.empty() ) )
			{
				( *citOS )->load_dependencies() ;
			}
		}
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
		
		// list all instances and sort by last_update_ time
		std::vector< IOOF_OBJ * > objects = IOOF_OBJ::_list_obj_ ;
		std::sort( objects.begin(), objects.end(), IOOF_OBJ::IOOF_OBJComparatorTime() ) ;
		std::vector< IOOF_OBJ * >::const_iterator cit = objects.cbegin() ;
		
		if( all != true )
		{
			// find the first object update after the last_save_
			while( cit != objects.cend() && ( *cit )->last_update_ < last_save_ )
			{
				++cit ;
			}
		}
		
		// this for loop could be parallize
		std::vector< IObjectStorage * >::const_iterator citOS ;
		for( ; cit != objects.cend() ; ++cit )
		{
			// find the perfect ObjectStorage to save
			citOS = list_storage_.cbegin() ;
			std::string type = ( *cit )->get_typename() ;
			while( ( *citOS )->get_typename() != type )
			{
				++citOS ;
			}
			
			// call the save method by transmitting the name of the folder
			// ( *citOS )->save( folder ) ;
			
			// if parallize, be careful on the following action
			// add a link in the project file
		}
	
		last_save_ = time( NULL ) ;
		
		// save the project file
	}
}
