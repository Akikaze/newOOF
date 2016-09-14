#include "instance_manager.hpp"

// --- CONSTRUCTORS ---

InstanceManager::InstanceManager
()
{
}

// --- DESTRUCTORS ---

InstanceManager::~InstanceManager
()
{
	while( ! empty() )
	{
		delete ( * ( begin() ) ).second ;
		// no need to erase here because it is erased in the object destructor
	}
}

// --- METHODS ---

void
InstanceManager::add
(
	IOOF_OBJECT * instance
)
{
	// add a instance in the map of instance
	insert( make_pair( instance->get_typename(), instance ) ) ;
}

/*
 * Extract all instance as a vector of instance
 */
std::vector< IOOF_OBJECT * >
InstanceManager::extract
()
const
{
	std::vector< IOOF_OBJECT * > result ;
	InstanceManager::const_iterator cit ;
	
	for( cit = cbegin() ; cit != cend() ; ++cit )
	{
		result.push_back( ( *cit ).second ) ;
	}

	return result ;
}

/*
 * Extract all instance which are a specific type
 */
std::vector< IOOF_OBJECT * >
InstanceManager::extract
(
	const std::string & type
)
const
{
	std::vector< IOOF_OBJECT * > result ;
	
	InstanceManager::const_iterator cit ;
	InstanceManager::const_iterator cit_begin = cbegin() ;
	InstanceManager::const_iterator cit_end = cend() ;
	
	// if type is empty, we extract everything
	if( !( type.empty() ) )
	{
		cit_begin = lower_bound( type ) ;
		cit_end = upper_bound( type ) ;
	}
	
	for( cit = cit_begin ; cit != cit_end ; ++cit )
	{
		result.push_back( ( *cit ).second ) ;
	}

	return result ;
}

/*
 * Extract all instance which were modified after the date
 */
std::vector< IOOF_OBJECT * >
InstanceManager::extract
(
	const time_t & date
)
const
{
	std::vector< IOOF_OBJECT * > result ;
	
	InstanceManager::const_iterator cit ;
	for( cit = cbegin() ; cit != cend() ; ++cit )
	{
		IOOF_OBJECT * ptr = ( *cit ).second ;
		
		// check last_update_ attribute
		if( ptr->last_update_ > date )
		{
			result.push_back( ptr ) ;
		}
	}

	return result ;
}

/* 
 * This method is used to remove an instance from the multimap.
 * It is called at each destruction of an object.
 */
void
InstanceManager::remove
(
	IOOF_OBJECT * instance
)
{
	InstanceManager::iterator it = begin() ;
	
	while( ( *it ).second != instance )
	{
		++it ;
	}
	
	erase( it ) ;
}
