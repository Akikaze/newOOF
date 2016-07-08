#include "core.hpp"

// ===== Core =====

// --- CONSTRUCTORS ---

Core::Core
()
{
	command_parser_ = CommandParser::get_instance() ;
	log_device_ = LogDevice::get_instance() ;
	project_storage_ = ProjectStorage::get_instance() ;
}

// --- DESTRUCTORS ---

Core::~Core
()
{
	delete command_parser_ ;
	delete log_device_ ;
	delete project_storage_ ;
}
