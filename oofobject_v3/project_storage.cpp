#include "project_storage.hpp"

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
		
		std::vector< std::string > objects_list ;
		// read list of objects' file and add it in objects_list
		
		project_file.close() ;
		
		// this for loop could be parallize
		std::vector< std::string >::const_iterator cit ;
		for( cit = objects_list.cbegin() ; cit != objects_list.cend() ; ++cit )
		{
			IObjectStorage * os = find_ObjectStorage( * cit ) ;
			
			/*
			std::vector< IObjectStorage * >::const_iterator citOS ;
			for( cit ; cit != objects_list.cend() ; ++cit )
			{
				citOS = list_storage_.cbegin() ;
				std::string type = find_typename( *cit ) ;
				while( ( *citOS )->get_typename() != type )
				{
					++citOS ;
				}
				
				( *citOS )->load( *cit ) ;
			}
			*/
		}
	}
	else
	{
		std::cerr << "Impossible to open the project file." << std::endl ;
	}
	
	// reading of Project file
	// extract project_name_ from the file
	// find which file need to be load
	// for each file
		// call the right ObjectStorage to load the file
		// ObjectStorage< TYPE >::get_instance()->load( subfilename ) ;
	
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
	
	if( project_name_.empty() )
	{
		project_exist = false ;
		project_name_ = project_name ;
	}
	
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
		
		std::vector< IOOF_OBJ * > objects = IOOF_OBJ::_list_list_ ;
		std::sort( objects.begin(), objects.end(), IOOF_OBJ::IOOF_OBJComparator() ) ;
		std::vector< IOOF_OBJ * >::const_iterator cit = objects.cbegin() ;
		
		if( all != true )
		{
			while( cit != objects.cend() && ( *cit )->last_update_ < last_save_ )
			{
				++cit ;
			}
		}
		
		// this for loop could be parallize
		std::vector< IObjectStorage * >::const_iterator citOS ;
		for( cit ; cit != objects.cend() ; ++cit )
		{
			citOS = list_storage_.cbegin() ;
			std::string type = ( *cit )->get_typename() ;
			while( ( *citOS )->get_typename() != type )
			{
				++citOS ;
			}
			
			// ( *citOS )->save( folder ) ;
			
			// if parallize, be careful on the following action
			// add a link in the project file
		}
	
		last_save_ = time( NULL ) ;
		
		// save the project file
	}
}
