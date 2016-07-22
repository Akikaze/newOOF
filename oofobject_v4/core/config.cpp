#include "config.hpp"

#include <cstring>

// --- ATTRIBUTES ---

bool Config::__DEBUG__ = 0 ;
bool Config::__OPENMP__ = 0 ;
std::string Config::__DIR__ = "" ;
std::string Config::__LOG__ = "" ;
std::string Config::__PROJECT__ = "" ;
std::string Config::__SESSION__ = "" ;

// --- CONSTRUCTORS ---

Config::Config
()
{
	if( read_config() == false )
	{
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
	
	__DEBUG__ = 0 ;
	__OPENMP__ = 0 ;
	__DIR__ = std::string( std::getenv( "PWD" ) ) ;
	__LOG__ = ".logs/" ;
	__PROJECT__ = "projects/" ;
}

bool
Config::read_config
()
{
	bool result = true ;
	std::ifstream file( "config", std::ios::in ) ;
	
	if( file )
	{
		std::string line ;
		size_t pos ;
		
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		__DEBUG__ = std::stoi( line ) ;
		
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		__OPENMP__ = std::stoi( line ) ;
		
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ;
		__DIR__ = line ;
		
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ;
		__LOG__ = line ;
		
		std::getline( file, line ) ;
		pos = line.find( " " ) ;
		line = line.substr( pos + 1 ) ;
		result &= !( line.empty() ) ;
		__PROJECT__ = line ;
		
		file.close() ;
		
		if( result == false )
		{
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
