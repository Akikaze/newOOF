#include "core.hpp"

// ===== Core =====

// --- CONSTRUCTORS ---

Core::Core
()
{
	cp_ = CommandParser::get_instance() ;
	im_ = InstanceManager::get_instance() ;
	ld_ = LogDevice::get_instance() ;
	ps_ = ProjectStorage::get_instance() ;
}

// --- DESTRUCTORS ---

Core::~Core
()
{
	/*
	 * because it is the last destructor called, maybe we need to save
	 * every logs before ending the process.
	 */
	ld_->save() ;
	
	delete cp_ ;
	delete im_ ;
	delete ld_ ;
	delete ps_ ;
}

// --- METHODS ---

void
Core::display_logs
()
const
{
	std::cout << *ld_ ;
}
