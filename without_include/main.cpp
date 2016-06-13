#include <dlfcn.h>
#include <iostream>
#include "interface.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	char * error ;
	void* handle = dlopen( "./class.so", RTLD_LAZY ) ;
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
	
	std::cout << "before" << std::endl ;
	Interface * interface = ( Interface * ) create() ;
	std::cout << "after" << std::endl ;
	interface->printX() ;
	destroy( interface ) ;
}
