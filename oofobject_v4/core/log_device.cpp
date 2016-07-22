#include "log_device.hpp"

#include "global.hpp"
#include "project_storage.hpp"

// ===== LOG_FLAG =====

std::string
flag_to_string
(
	int flags
)
{
	return flag_to_string( LOG_FLAG( flags ) ) ;
}

std::string
flag_to_string
(
	LOG_FLAG flags
)
{
	bool add = false ;
	std::string result ;
	
	if( flags & LOG_FLAG::ERROR ) { result += "ERROR" ; add = true ; }
	if( flags & LOG_FLAG::QUERY ) { if( add ) { result += " " ; } result += "QUERY" ; add = true ; }
	if( flags & LOG_FLAG::REPORT ) { if( add ) result += " " ; result += "REPORT" ; add = true ; }
	if( flags & LOG_FLAG::WARNING ) { if( add ) result += " " ; result += "WARNING" ; add = true ; }
	if( flags & LOG_FLAG::SCRIPT ) { if( add ) result += " " ; result += "SCRIPT" ; }
	
	return result ;
}

std::ostream &
operator<<
(
	std::ostream & os,
	LOG_FLAG flags
)
{
	os << flag_to_string( flags ) ;
	return os ;
}

// ===== Log =====

std::ostream &
operator<<
(
	std::ostream & os,
	Log l
)
{
	os << l.flags << " : " << l.message << " (" << display( l.date ) << ")" ;
	return os ;
}

// ===== LogDevice =====

// --- CONSTRUCTORS ---

LogDevice::LogDevice
()
{
	time_code_ = std::to_string( time( NULL ) ) ;
	Config::__SESSION__ = time_code_ ;
}

// --- DESTRUCTORS ---

LogDevice::~LogDevice
()
{
}

// --- OPERATORS ---

std::ostream &
operator<<
(
	std::ostream & os,
	const LogDevice & ld
)
{
	std::vector< Log >::const_iterator cit ;
	
	for( cit = ld.logs_.cbegin() ; cit != ld.logs_.cend() ; ++cit )
	{
		os << *cit << std::endl ;
	}
	
	return os ;
}

// --- METHODS ---

std::vector< Log >
LogDevice::extract
(
	int flags
)
const
{
	return extract( LOG_FLAG( flags ) ) ;
}

std::vector< Log >
LogDevice::extract
(
	LOG_FLAG flags
)
const
{
	std::vector< Log > result ;
	std::vector< Log >::const_iterator cit ;
	
	for( cit = logs_.cbegin() ; cit != logs_.cend() ; ++cit )
	{
		if( ( *cit ).flags & flags )
		{
			result.push_back( *cit ) ;
		}
	}	
	
	return result ;
}

std::string
LogDevice::format_date
(
	const std::string & seconds
)
const
{
	struct tm date ;
	char buffer[ 100 ] ;
	
	strptime( seconds.c_str(), "%s", &date ) ;	
	strftime( buffer, 100, "%F-%T", &date ) ;
	
	return std::string( buffer ) ;
}

void
LogDevice::log
(
	const std::string & message,
	int flags
)
{
	log( message, LOG_FLAG( flags ) ) ;
}

void
LogDevice::log
(
	const std::string & message,
	LOG_FLAG flags
)
{
	// create a log object and store info in it
	Log tmp ;
	tmp.flags = flags ;
	tmp.message = message ;
	tmp.date = time( NULL ) ;
	
	if( Config::__DEBUG__ )
	{
		std::cout << tmp << std::endl ;
	}
	
	logs_.push_back( tmp ) ;
}

void
LogDevice::save
(
	int flags
)
{
	save( LOG_FLAG( flags ) ) ;
}

void
LogDevice::save
(
	LOG_FLAG flags
)
{
	// reverse order because SCRIPT is  likely able to log some REPORTS and ERRORS
	if( flags & LOG_FLAG::SCRIPT ) { save_flag( LOG_FLAG::SCRIPT ) ; }
	if( flags & LOG_FLAG::WARNING ) { save_flag( LOG_FLAG::WARNING ) ; }
	if( flags & LOG_FLAG::REPORT ) { save_flag( LOG_FLAG::REPORT ) ; }
	if( flags & LOG_FLAG::QUERY ) { save_flag( LOG_FLAG::QUERY ) ; }
	if( flags & LOG_FLAG::ERROR ) { save_flag( LOG_FLAG::ERROR ) ; }
}

void
LogDevice::save_flag
(
	LOG_FLAG flag
)
{
	bool test = true ;
	std::vector< Log > logs = extract( flag ) ;
	
	// it is useless to save logs if they are empty
	if( !( logs.empty() ) )
	{
		std::vector< Log >::const_iterator cit ;
		std::string filename ;
		
		// if it's for the script, we need to save it in the project folder
		if( flag & LOG_FLAG::SCRIPT )
		{
			std::string project_name = ProjectStorage::get_instance()->get_project_name() ;
			
			// if the project is not defined
			if( project_name.empty() )
			{
				log( "The project is not defined, script is going to be saved in the log directory", LOG_FLAG::REPORT ) ;
				
				filename = Config::__DIR__ ;
				filename += "/" + Config::__LOG__ ;
				
				// test the directory
				test &= test_directory( filename ) ;
				
				filename += time_code_ + "/" ;
				
				// test the subdirectory
				test &= test_directory( filename ) ;				
			}
			else
			{
				log( "The script is going to be saved in the project directory", LOG_FLAG::REPORT ) ;
				filename = ProjectStorage::get_instance()->get_project_path() ;
			}
			
			filename += "SCRIPT" ;
		}
		else
		{
			filename = Config::__DIR__ ;
			filename += "/" + Config::__LOG__ ;
			
			// test the directory
			test &= test_directory( filename ) ;
			
			filename += time_code_ + "/" ;
			
			// test the subdirectory
			test &= test_directory( filename ) ;
			
			filename += flag_to_string( flag ) ;
		}
		
		if( test == true )
		{
			// clear the file everytime
			std::ofstream file( filename.c_str(), std::ios::out | std::ios::trunc ) ;
			
			if( file )
			{
				// save every logs
				for( cit = logs.cbegin() ; cit != logs.cend() ; ++cit )
				{
					file << display( ( *cit ).date ) << " : " << ( *cit ).message ;
					
					// if the log is shared by several flag, we add the info
					if( flag ^ ( *cit ).flags )
					{
						file << " ( also : " << flag_to_string( flag ^ ( *cit ).flags ) << " )" ;
					}
					
					file << std::endl ;
				}
				
				file.close() ;
			}
			else
			{
				log( "Impossible to save log " + flag_to_string( flag ), LOG_FLAG::ERROR ) ;
				log( "Impossible to open " + filename + " in write mode", LOG_FLAG::REPORT ) ;
			}
		}
		else
		{
			log( "Impossible to create directories for the log system", LOG_FLAG::ERROR ) ;
		}
	}
}
