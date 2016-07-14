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
		erase( begin() ) ;
	}
}

// --- METHODS ---

void
InstanceManager::add
(
	IOOF_OBJECT * instance
)
{
	insert( make_pair( instance->get_typename(), instance ) ) ;
}

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
		
		if( ptr->last_update_ > date )
		{
			result.push_back( ptr ) ;
		}
	}
	
	return result ;
}
