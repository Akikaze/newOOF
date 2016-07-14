#include "log_device.hpp"

// ===== LOG_FLAG =====

std::ostream &
operator<<
(
	std::ostream & os,
	LOG_FLAG flags
)
{
	bool add = false ;
	
	if( flags & LOG_FLAG::ERROR ) { os << "ERROR" ; add = true ; }
	if( flags & LOG_FLAG::QUERY ) { if( add ) { os << " " ; } os << "QUERY" ; add = true ; }
	if( flags & LOG_FLAG::REPORT ) { if( add ) os << " " ; os << "REPORT" ; add = true ; }
	if( flags & LOG_FLAG::WARNING ) { if( add ) os << " " ; os << "WARNING" ; add = true ; }
	if( flags & LOG_FLAG::SCRIPT ) { if( add ) os << " " ; os << "SCRIPT" ; }
		
	return os ;
}

// ===== LogDevice =====

// --- CONSTRUCTORS ---

LogDevice::LogDevice
()
{
	filename_ = std::to_string( time( NULL ) ) ;
	
	std::cout << format_date() << std::endl ;
	std::cout << LOG_FLAG( LOG_FLAG::ERROR | LOG_FLAG::REPORT ) << std::endl ;
}

// --- DESTRUCTORS ---

LogDevice::~LogDevice
()
{
}

// --- METHODS ---

std::string
LogDevice::format_date
()
const
{
	struct tm date ;
	char buffer[ 100 ] ;
	
	strptime( filename_.c_str(), "%s", &date ) ;	
	strftime( buffer, 100, "%F-%T", &date ) ;
	
	return std::string( buffer ) ;
}
