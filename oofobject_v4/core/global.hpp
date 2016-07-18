#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream> // cerr
#include <cstdlib> // getenv
#include <cstring> // strcat

#include <sys/stat.h> // mkdir
#include <dirent.h> // opendir
#include <errno.h> // errno
#include <cstring> // strerrno
#include <string> // operator+


// ===== GLOBAL VALUES =====

const bool __DEBUG__ = 1 ;
const bool __OPENMP__ = 0 ;

// ===== GLOBAL DIRECTORIES =====

const char * const __DIR__ = std::getenv( "PWD" ) ;
const char * const __PROJECT__ = "projects/" ;
const char * const __LOG__ = ".logs/" ;

// ===== GLOBAL FILES =====



// ===== GLOBAL FUNCTIONS =====

inline bool
test_directory
(
	const std::string & directory
)
{
	DIR * test = opendir( directory.c_str() ) ;
	
	// if the directory is not here, we create it.
	if( test == NULL )
	{
		std::cerr << directory + " doesn't exist. Need to create one." << std::endl ;
		
		if( mkdir( directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == -1 )
		{
			// the most common error is to try save in a forbidden place
			std::cerr << "Impossible to create " + directory + " : " + std::string( strerror( errno ) ) << std::endl ;
		}
	}
	
	closedir( test ) ;
}

#endif // GLOBAL_HPP
