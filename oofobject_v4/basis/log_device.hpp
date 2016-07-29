#ifndef LOG_DEVICE_HPP
#define LOG_DEVICE_HPP

#include "config.hpp"
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

///
/// \brief Transform several flags into string
/// \param flags Several LOG_FLAG
/// \return String
///
std::string flag_to_string( int flags ) ;

///
/// \brief Transform LOG_FLAG into string
/// \param flags LOG_FLAG
/// \return String
///
std::string flag_to_string( LOG_FLAG flags ) ;

///
/// \brief Display a LOG_FLAG
/// \param os Stream for the display
/// \param flags Flags which needs to be displayed
/// \return Stream with the LOG_FLAG displayed in it
///
std::ostream & operator<<( std::ostream & os, LOG_FLAG flags ) ;

// ===== Log =====

struct Log
{
	LOG_FLAG flags ;
	std::string message ;
	time_t date ;
} ;

///
/// \brief Display a log
/// \param os Stream for the display
/// \param l Log which needs to be displayed
/// \return Stream with the log displayed in it
///
std::ostream & operator<<( std::ostream & os, Log l ) ;

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
	
		// --- GETTERS ---
		
		///
		/// \brief Get the time code
		/// \return The time code in a string
		///
		inline std::string get_time_code()
			{ return time_code_ ; }
		
		// --- METHODS ---
		
		///
		/// \brief Store a log message
		/// \param message Message of the log
		/// \param flags Several LOG_FLAG
		///
		void log( const std::string & message, int flags ) ;
		
		///
		/// \brief Store a log message
		/// \param message Message of the log
		/// \param flags LOG_FLAG
		///
		void log( const std::string & message, LOG_FLAG flags ) ;
		
		///
		/// \brief Save a log
		/// \param flags Several LOG_FLAG
		///
		void save( int flags ) ;
		
		///
		/// \brief Save a log
		/// \param flags LOG_FLAG
		///
		void save( LOG_FLAG flags = LOG_FLAG::ALL ) ;
		
		///
		/// \brief Save a a specific type of LOG_FLAG
		/// \param flags LOG_FLAG
		///
		void save_flag( LOG_FLAG ) ; 
	
	protected :
	
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		LogDevice() ;
		
		// --- DESTRUCTORS ---
		
		///
		/// \brief Destructor
		///
		~LogDevice() ;
		
		// --- OPERATORS ---
		
		///
		/// \brief Display every logs
		/// \param os Stream for the display
		/// \param ld LogDevice
		/// \return Stream with logs displayed in it
		///
		friend std::ostream & operator<<( std::ostream & os, const LogDevice & ld ) ;
		
		// --- METHODS ---
		
		///
		/// \brief Extract specific logs
		/// \param flags Several LOG_FLAG
		/// \param Vector which contains logs
		///
		std::vector< Log > extract( int flags ) const ;
		
		///
		/// \brief Extract specific logs
		/// \param flags LOG_FLAG
		/// \param Vector which contains logs
		///
		std::vector< Log > extract( LOG_FLAG flags = LOG_FLAG::ALL ) const ; // extract a specific flag
		
		///
		/// \brief Transform a number of seconds into a date
		/// \param seconds String which represents the number of seconds
		/// \return String which represents the date
		///
		std::string format_date( const std::string & seconds ) const ;
		
		// --- ATTRIBUTES ---
		std::string time_code_ ; ///< Time code of the LogDevice
		std::vector< Log > logs_ ; ///< Vector of logs
} ;

#endif // LOG_DEVICE_HPP
