#include <dlfcn.h>
#include <dirent.h>

#include <iostream>
#include <vector>

#include "interface.hpp"

using namespace std ;

int
main
(
	int argc,
	char ** argv
)
{
	std::vector< std::string > list_directories ;
	DIR * directory = opendir( "./libraries" ) ;
	struct dirent * ent ;
	
	if( directory != NULL )
	{
		int i = 0 ;
		while( ( ent = readdir( directory ) ) != NULL )
		{
			if( i > 2 )
			{
				list_directories.push_back( ent->d_name ) ;
			}
			
			++i ;
		}
		closedir( directory ) ;
	}
	else
	{
		std:cout << "Error when loading libraries folder" << std::endl ;
	}
	
	std::cout << "List of folders in ./libraries" << std::endl ;
	for(std::vector< std::string >::iterator it = list_directories.begin() ;
		it != list_directories.end() ; ++it )
	{
		std::cout << *it << std::endl ;
	}
	std::cout << std::endl ;
	
	std::vector< Interface * > list_modules ;
		
	char * error ;
	void* handle = dlopen( "./interface.so", RTLD_LAZY ) ;
	if ( ( error = dlerror() ) != NULL )
	{
		std::cout << error << std::endl ;
	}
	
	Interface * ( *create )() ;
	void ( *destroy )( Interface * ) ;
	
	create = ( Interface * ( * )() ) dlsym ( handle, "create" ) ;
	if ( ( error = dlerror() ) != NULL )
	{
		std::cout << error << std::endl ;
	}
	
	destroy = ( void ( * )( Interface * ) ) dlsym( handle, "destroy" ) ;
	if ( ( error = dlerror() ) != NULL )
	{
		std::cout << error << std::endl ;
	}
	
	Interface * interface = ( Interface * ) create() ;
	
	list_modules.push_back( interface ) ;
	
	interface->DoSomething() ;
	destroy( interface ) ;
}
