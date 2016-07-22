#include "core.hpp"

/* includes for preparation */

#include "../src/test.hpp"

// ===== Core =====

// --- CONSTRUCTORS ---

Core::Core
()
{
	Config::construct() ;
	
	cp_ = CommandParser::get_instance() ;
	im_ = InstanceManager::get_instance() ;
	ld_ = LogDevice::get_instance() ;
	ps_ = ProjectStorage::get_instance() ;
	
	// preparation for type
	void * useless = nullptr ;
	prepare( static_cast< Test * >( useless ) ) ;
}

// --- DESTRUCTORS ---

Core::~Core
()
{
	delete cp_ ;
	delete ps_ ;
	delete im_ ;
	
	/*
	 * because it is the last destructor called, maybe we need to save
	 * every logs before ending the process.
	 */
	ld_->save() ;
	delete ld_ ;
	
	Config::destroy() ;
}

// --- METHODS ---

void
Core::display_logs
()
const
{
	std::cout << *ld_ ;
}

void
Core::load
()
const
{
	ps_->load( "/users/dpf1/Desktop/Chut/Work/git/newOOF/oofobject_v4/projects/1469195975/1469195975.oof_proj" ) ;
}

template < class T >
void
Core::prepare
(
	T * useless
)
const
{
	ObjectStorage< T >::construct() ;
	SubCommandParser< T >::construct() ;
}

void
Core::save
()
const
{
	ps_->save() ;
}
