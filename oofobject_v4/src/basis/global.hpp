#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream> // cerr
#include <sys/stat.h> // mkdir
#include <dirent.h> // opendir
#include <errno.h> // errno
#include <cstring> // strerrno
#include <string> // operator+

// ===== GLOBAL FUNCTIONS =====

///
/// \brief Check if a directory exist and try to create it if it doesn't
/// \param directory Path to the directory which needs to be check
/// \return true if the file exist, false otherwise
///
inline bool
test_directory
(
	const std::string & directory
)
{
	bool result = true ;
	DIR * test = opendir( directory.c_str() ) ;
	
	// if the directory is not here, we create it.
	if( test == NULL )
	{
		std::cerr << directory + " doesn't exist. Need to create one." << std::endl ;
		
		if( mkdir( directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == -1 )
		{
			// the most common error is to try save in a forbidden place
			std::cerr << "Impossible to create " + directory + " : " + std::string( strerror( errno ) ) << std::endl ;
			
			result = false ;
		}
	}
	
	closedir( test ) ;
	return result ;
}

#endif // GLOBAL_HPP
