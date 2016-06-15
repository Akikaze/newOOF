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
	lib_descriptor_ = dlopen( find_library( address ).c_str(), RTLD_LAZY ) ;
	if ( ( error = dlerror() ) != NULL )
	{
		std::cout << error << std::endl ;
	}
	else
	{
		bool fail = false ;
		
		// find the load function
		Interface * ( * load )() = ( Interface * ( * )() ) dlsym ( lib_descriptor_, "load" ) ;
		if ( ( error = dlerror() ) != NULL )
		{
			fail = true ;
			std::cout << error << std::endl ;
		}
		
		if( fail != true )
		{
			// create the pointer to the plugin
			pointer_ = ( Interface * ) load() ;
			
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
		// unload the plugin
		unload_plugin( pointer_ ) ;
	}
	
	if( lib_descriptor_ )
	{
		// end the read of the shared library
		dlclose( lib_descriptor_ ) ;
	}
}

// --- METHODS ---

///
/// \fn void Plugin::unload_plugin( Interface * plugin )
/// \brief Unload a plugin by release the pointer
/// \param plugin Pointer on the plugin
///
void
Plugin::unload_plugin
(
	Interface * plugin
)
{
	delete plugin ;
}

///
/// \fn std::string Plugin::find_library( const std::string & address )
/// \brief Find the library path thanks to the folder's address
/// \param address Address of plugin's folder
/// \return Address of the library
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
