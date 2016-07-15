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
