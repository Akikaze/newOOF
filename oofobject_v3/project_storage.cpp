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
()
const
{
	std::vector< IObjectStorage * >::const_iterator cit ;
	
	for( cit = list_storage_.cbegin() ; cit != list_storage_.cend() ; ++cit )
	{
		( *cit )->load() ;
	}
}

void
ProjectStorage::save
()
const
{
	std::vector< IObjectStorage * >::const_iterator cit ;
	
	for( cit = list_storage_.cbegin() ; cit != list_storage_.cend() ; ++cit )
	{
		( *cit )->save() ;
	}
}
