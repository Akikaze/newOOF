#include "log_device.hpp"

// ===== LogDevice =====

// --- CONSTRUCTORS ---

LogDevice::LogDevice
()
{
#ifdef __DEBUG__
	std::cout << "LogDevice construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

LogDevice::~LogDevice
()
{
#ifdef __DEBUG__
	std::cout << "LogDevice destruction" << std::endl ;
#endif
}
