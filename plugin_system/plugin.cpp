#include "plugin.hpp"

// --- CONSTRUCTORS ---

///
/// \fn Plugin::Plugin( const std::string & address )
/// \brief Constructor
/// \param address Address of plugin's folder
///
Plugin::Plugin
(
	const std::string & address
)
{
	address_ = address ;
	pointer_ = NULL ;
	
	name_ = "NULL" ;
	description_ = "NULL" ;
	rank_ = USHRT_MAX ;
	
	char * error ;
	
	// open the shared library
	handle_ = dlopen( find_library( address ).c_str(), RTLD_LAZY ) ;
	if ( ( error = dlerror() ) != NULL )
	{
		std::cout << error << std::endl ;
	}
	else
	{
		bool fail = false ;
		
		// find the create function
		create_ = ( Interface * ( * )() ) dlsym ( handle_, "create" ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			fail = true ;
			std::cout << error << std::endl ;
		}
		
		// find the destroy function
		destroy_ = ( void ( * )( Interface * ) ) dlsym( handle_, "destroy" ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			fail = true ;
			std::cout << error << std::endl ;
		}
		
		if( fail != true )
		{
			// create the pointer to the plugin
			pointer_ = ( Interface * ) create_() ;
			
			// find plugin's information
			name_ = pointer_->get_name() ;
			description_ = pointer_->get_description() ;
			rank_ = pointer_->get_rank() ;
		}
	}
}

// --- DESTRUCTORS ---

///
/// \fn Plugin::~Plugin()
/// \brief Destructor
/// 
Plugin::~Plugin
()
{
	if( pointer_ != NULL )
	{
		// release the object thanks to the destroy function
		destroy_( pointer_ ) ;
	}
	
	if( handle_ )
	{
		// end the read of the shared library
		dlclose( handle_ ) ;
	}
}

// --- METHODS ---

///
/// \fn std::string Plugin::find_library( const std::string & address )
/// \brief find the library path thanks to the folder's address
/// \param address of plugin's folder
/// \return address of the library
///
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
	
	// try to find the last / in order to get only shared library's folder's name
	while( crit != address.crend() && *crit != '/' )
	{
		++last_slash ;
		++crit ;
	}
	last_slash = address.length() - last_slash ;
	
	// create the path to the library by adding the folder's name and .so
	library = address + "/" + address.substr( last_slash, address.length() - last_slash ) + ".so" ;
	
	return library ;
}

// --- OPERATORS ---

///
/// \fn bool Plugin::operator<( const Plugin & plugin ) const
/// \brief Operator <
/// \param Plugin for the comparison
/// \return true if the rank of this plugin is less than the parameter's rank
///
bool
Plugin::operator<
(
	const Plugin & plugin
)
const
{
	return ( rank_ < plugin.rank_ ) ;
}
