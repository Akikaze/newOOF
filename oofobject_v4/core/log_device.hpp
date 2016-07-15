#ifndef LOG_DEVICE_HPP
#define LOG_DEVICE_HPP

#include "oof_singleton.hpp"
#include "std.hpp"

// ===== LOG_FLAG =====

/*
 * It is possible to associate several flags but SCRIPT should always be alone.
 * If we add other flag to SCRIPT, the SCRIPT command will not be loadable by the system.
 */

enum LOG_FLAG
{
	ERROR		= 0x01,
	QUERY		= 0x02,
	REPORT		= 0x04,
	WARNING 	= 0x08,
	// all problems
	BUGS		= 0x0F,
	
	SCRIPT		= 0x10,
	// everything
	ALL			= 0x1F
} ;

std::string flag_to_string( int ) ;
std::string flag_to_string( LOG_FLAG ) ;
std::ostream & operator<<( std::ostream &, LOG_FLAG ) ;

// ===== Log =====

struct Log
{
	LOG_FLAG flags ;
	std::string message ;
	time_t date ;
} ;

std::ostream & operator<<( std::ostream &, Log ) ;

// ===== LogDevice =====

/*
 * This class should be a friend of the Message Window to allow the use of
 * extract to display logs.
 */

class LogDevice
: public OOF_SINGLETON< LogDevice >
{
	friend class OOF_SINGLETON< LogDevice > ; // constructor
	friend class Core ; // destructor, ...
	
	public :
		
		// --- METHODS ---
		void log( const std::string &, int ) ; // override for several flags
		void log( const std::string &, LOG_FLAG ) ; // log something
		
		void save( int flags ) ; // override for several flags
		void save( LOG_FLAG flags = LOG_FLAG::ALL ) ; // save logs
		
		void save_flag( LOG_FLAG ) ; // save only one flag
	
	protected :
	
		// --- CONSTRUCTORS ---
		LogDevice() ;
		
		// --- DESTRUCTORS ---
		~LogDevice() ;
		
		// --- OPERATORS ---
		friend std::ostream & operator<<( std::ostream &, const LogDevice & ) ;
		
		// --- METHODS ---
		std::vector< Log > extract( int ) const ; // override for several flags
		std::vector< Log > extract( LOG_FLAG flags = LOG_FLAG::ALL ) const ; // extract a specific flag
		
		std::string format_date( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		std::string filename_ ;
		std::vector< Log > logs_ ;
} ;

#endif // LOG_DEVICE_HPP
