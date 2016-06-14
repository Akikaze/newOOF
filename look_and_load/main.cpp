#include <dlfcn.h>
#include <dirent.h>

#include <iostream>
#include <vector>

#include "interface.hpp"

using namespace std ;

std::vector< std::string > find_directories() ;
void find_libraries( std::vector< std::string > & list_directories ) ;

std::vector< Interface * > load_libraries( const std::vector< std::string > & list_libraries ) ;
void unload_libraries( const std::vector< std::string > & list_libraries,
					   std::vector< Interface * > & list_pointers ) ;

int
main
(
	int argc,
	char ** argv
)
{
	std::vector< std::string > directories = find_directories() ;
	
	find_libraries( directories ) ;
	
	std::vector< Interface * > libraries = load_libraries( directories ) ;
	
	for( std::vector< Interface * >::const_iterator cit = libraries.cbegin() ;
		 cit != libraries.cend() ; ++cit )
	{
		( *cit )->display() ;
	}
	
	unload_libraries( directories, libraries ) ;
}

std::vector< std::string >
find_directories
()
{
	std::vector< std::string > list_directories ;
	DIR * directory = opendir( "./libraries" ) ;
	struct dirent * ent ;
	
	if( directory != NULL )
	{
		int i = 0 ;
		while( ( ent = readdir( directory ) ) != NULL )
		{
			if( i >= 2 )
			{
				list_directories.push_back( ent->d_name ) ;
			}
			
			++i ;
		}
		closedir( directory ) ;
	}
	else
	{
		std::cout << "Error when loading libraries folder" << std::endl ;
	}
	
	return list_directories ;
}

void
find_libraries
(
	std::vector< std::string > & list_directories
)
{
	for( std::vector< std::string >::iterator it = list_directories.begin() ;
		 it != list_directories.end() ; ++it )
	{
		( *it ) = "./libraries/" + ( *it ) + "/" + ( *it ) + ".so" ;
	}
}

std::vector< Interface * >
load_libraries
(
	const std::vector< std::string > & list_libraries
)
{
	char * error ;
	std::vector< Interface * > list_pointers ;
	void * handle ;
	
	for( std::vector< std::string >::const_iterator cit = list_libraries.cbegin() ;
		 cit != list_libraries.cend() ; ++cit )
	{		
		handle = dlopen( ( *cit ).c_str(), RTLD_LAZY ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			std::cout << error << std::endl ;
		}
		else
		{
			Interface * ( * create )() ;
			
			create = ( Interface * ( * )() ) dlsym ( handle, "create" ) ;
			if ( ( error = dlerror() ) != NULL )
			{
				std::cout << error << std::endl ;
			}
			else
			{
				Interface * object = ( Interface * ) create() ;
				list_pointers.push_back( object ) ;
			}
		}
	}
	
	return list_pointers ;	
}

void
unload_libraries
(
	const std::vector< std::string > & list_libraries,
	std::vector< Interface * > & list_pointers
)
{
	char * error ;
	void * handle ;
	
	for( size_t s = 0 ; s < list_pointers.size() ; ++s )
	{
		handle = dlopen( list_libraries[ s ].c_str(), RTLD_LAZY ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			std::cout << error << std::endl ;
		}
		else
		{
			void ( * destroy )( Interface * ) ;
			
			destroy = ( void ( * )( Interface * ) ) dlsym( handle, "destroy" ) ;
			if ( ( error = dlerror() ) != NULL )
			{
				std::cout << error << std::endl ;
			}
			else
			{
				destroy( list_pointers[ s ] ) ;
				list_pointers[ s ] = NULL ;
			}
		}
	}
}
