#include "plugin.hpp"

Plugin::Plugin
(
	const std::string & address
)
{
	address_ = address ;
	pointer_ = NULL ;
	
	char * error ;
	
	handle_ = dlopen( find_library( address ).c_str(), RTLD_LAZY ) ;
	if ( ( error = dlerror() ) != NULL )
	{
		std::cout << error << std::endl ;
	}
	else
	{
		bool fail = false ;
				
		create_ = ( Interface * ( * )() ) dlsym ( handle_, "create" ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			fail = true ;
			std::cout << error << std::endl ;
		}
		
		destroy_ = ( void ( * )( Interface * ) ) dlsym( handle_, "destroy" ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			fail = true ;
			std::cout << error << std::endl ;
		}
		
		if( fail != true )
		{
			pointer_ = ( Interface * ) create_() ;
			
			// get name + get description
		}
	}
}

Plugin::~Plugin
()
{
	if( pointer_ != NULL )
	{
		destroy_( pointer_ ) ;
	}
	
	dlclose( handle_ ) ;
}

std::string
Plugin::find_library
(
	const std::string & address
)
const
{
	size_t last_slash = 0 ;
	std::string library ;
	std::string::const_reverse_iterator crit = address.crbegin() ;
	
	while( crit != address.crend() && *crit != '/' )
	{
		++last_slash ;
		++crit ;
	}
	last_slash = address.length() - last_slash ;
	library = address + "/" + address.substr( last_slash, address.length() - last_slash ) + ".so" ;
	
	return library ;
}
