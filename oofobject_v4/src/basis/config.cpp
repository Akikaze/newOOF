#include "config.hpp"

#include <cstring>

// --- ATTRIBUTES ---

bool Config::__DEBUG__ = 0 ; // 1 -> DEBUG mode
bool Config::__OPENMP__ = 0 ; // 1 -> parallelization with OPENMP
std::string Config::__DIR__ = "" ; // main directory
std::string Config::__LOG__ = "" ; // log directory in __DIR__
std::string Config::__PROJECT__ = "" ; // project directory in __DIR__
std::string Config::__SESSION__ = "" ; // time code for the SESSION
unsigned int Config::__DIMENSION__ = 0 ; // dimension for the project

// --- CONSTRUCTORS ---

Config::Config
()
{
	// try to read the config file
	if( read_config() == false )
	{
		// read the default config if the config file is not right
		default_config() ;
	}
}

// --- DESTRUCTORS ---

Config::~Config
()
{

}

// --- METHODS ---

void
Config::default_config
()
{
	std::cerr << "Use of default config." << std::endl ;
	
	__DEBUG__ = 0 ; // no debug
	__OPENMP__ = 0 ; // no parallelization
	__DIR__ = std::string( std::getenv( "PWD" ) ) ; // $PWD
	__LOG__ = ".logs/" ; // $PWD/.logs/
	__PROJECT__ = "projects/" ; // $PWD/projects/
	__DIMENSION__ = 3 ; // 3D by default
}

bool
Config::read_config
()
{
	// signal if one data is not present in the config file
	bool result = true ;
	std::ifstream file( "config", std::ios::in ) ;
	
	if( file )
	{
		std::string line ;
		size_t pos ;
		
		// __DEBUG__
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ; // false if empty
		__DEBUG__ = std::stoi( line ) ;
		
		// __OPENMP__
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ; // false if empty
		__OPENMP__ = std::stoi( line ) ;
		
		// __DIR__
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ; // false if empty
		__DIR__ = line ;
		
		// __LOG__
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ; // false if empty
		__LOG__ = line ;
		
		// __PROJECT__
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ; // false if empty
		__PROJECT__ = line ;
		
		// __DIMENSION__
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ; // false if empty
		__DIMENSION__ = std::stoi( line ) ;
		
		file.close() ;
		
		if( result == false )
		{
			// it is going to use the default configuration
			std::cerr << "Invalid config file." << std::endl ;
		}
	}
	else
	{
		std::cerr << "Inexistant config file." << std::endl ;
		result = false ;
	}
	
	return result ;
}
