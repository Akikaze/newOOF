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

void ProjectStorage::display_list
()
const
{
	std::cout << list_storage_ << std::endl ;
}

void
ProjectStorage::load
(
	const std::string & filename
)
{
	// switch on file's extension
		// call the right ObjectStorage to load the file
		// ObjectStorage< TYPE >::get_instance()->load( subfilename ) ;
	
	// reading of Project file
	// extract project_name_ from the file
	// find which file need to be load
	// for each file
		// call the right ObjectStorage to load the file
		// ObjectStorage< TYPE >::get_instance()->load( subfilename ) ;
}

void
ProjectStorage::save
(
	const std::string & project_name,
	bool all
)
{
	if( project_name_.empty() )
	{
		project_name_ = project_name ;
	}
	
	if( project_name_.empty() )
	{
		std::cerr << "The project doesn't have a name." << std::endl ;
	}
	else
	{
		// create the project folder and the project file
		
		// for each type
			// call the right ObjectStorage to save the object thanks to the boolean all
			// ObjectStorage< TYPE >::get_instance()->save( folder, last_save ) ; // without all
			// ObjectStorage< TYPE >::get_instance()->save( folder ) ; // with all
			// add a link in the project file
	}
	
	last_save_ = time( NULL ) ;
}
