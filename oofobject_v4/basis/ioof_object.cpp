#include "ioof_object.hpp"

// ===== IOOF_OBJECT =====

// --- ATTRIBUTES ---

InstanceManager * IOOF_OBJECT::_im_ = nullptr ;
LogDevice * IOOF_OBJECT::_ld_ = nullptr ;

// --- CONSTRUCTORS ---

IOOF_OBJECT::IOOF_OBJECT
()
{
	if( _im_ == NULL )
	{
		// get pointer to InstanceManager
		_im_ = InstanceManager::get_instance() ;
	}
	
	if( _ld_ == NULL )
	{
		// get pointer to LogDevice
		_ld_ = LogDevice::get_instance() ;
	}
	
	last_update_ = time( NULL ) ;
}

// --- DESTRUCTORS ---

IOOF_OBJECT::~IOOF_OBJECT
()
{
}

// --- METHODS ---

void
IOOF_OBJECT::add
(
	IOOF_OBJECT * instance
)
const
{
	// add itself to the InstanceManager
	_im_->add( instance ) ;
}

std::vector< IOOF_OBJECT * > 
IOOF_OBJECT::extract
(
	const std::string & type
)
const
{
	return _im_->extract( type ) ;
}

void
IOOF_OBJECT::remove
(
	IOOF_OBJECT * instance
)
const
{
	// remove itself
	_im_->remove( instance ) ;
}
