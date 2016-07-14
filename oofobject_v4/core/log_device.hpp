#ifndef LOG_DEVICE_HPP
#define LOG_DEVICE_HPP

#include "oof_object.hpp"

// ===== LOG_FLAG =====

enum LOG_FLAG
{
	ERROR			= 0x01,
	QUERY			= 0x02,
	REPORT			= 0x04,
	WARNING 		= 0x08,
	SCRIPT			= 0x10
} ;

std::ostream & operator<<( std::ostream &, LOG_FLAG ) ;

// ===== Log =====

struct Log
{
	int flags ;
	std::string message ;
	time_t date ;
} ;

// ===== LogDevice =====

class LogDevice
: public OOF_SINGLETON< LogDevice >
{
	friend class OOF_SINGLETON< LogDevice > ; // constructor
	friend class Core ; // destructor
	
	public :
		
		// --- METHODS ---
		std::vector< Log > display( int flags ) ;
		void log( const std::string &, int ) ;
		void save() ;
	
	protected :
	
		// --- CONSTRUCTORS ---
		LogDevice() ;
		
		// --- DESTRUCTORS ---
		~LogDevice() ;
		
		// --- GETTERS ---
		std::string format_date() const ;
		
		// --- ATTRIBUTES ---
		std::string filename_ ;
		std::vector< Log > logs_ ;
} ;

#endif // LOG_DEVICE_HPP
