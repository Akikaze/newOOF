#include "plugin_list.hpp"

// --- CONSTRUCTORS ---

///
/// \fn PluginList::PluginList( const std::string & address )
/// \brief Constructor with parameter
///
PluginList::PluginList
(
	const std::string & address
)
{
	address_ = address ;
	
	std::vector< std::string > list_directories ;
	DIR * directory = opendir( address_.c_str() ) ;
	struct dirent * ent ;
	
	if( directory != NULL )
	{
		while( ( ent = readdir( directory ) ) != NULL )
		{
			if( strcmp( ent->d_name, "." ) != 0 &&
				strcmp( ent->d_name, ".." ) != 0  )
			{
				list_directories.push_back( address_ + "/" + ent->d_name ) ;
			}
		}
		closedir( directory ) ;
	}
	else
	{
		std::cout << "Error when loading libraries folder" << std::endl ;
	}
	
	for( std::vector< std::string >::const_iterator cit = list_directories.cbegin() ;
		 cit != list_directories.cend() ; ++cit )
	{
		this->push_back( new Plugin( *cit ) ) ;
	}
	
	sort( this->begin(), this->end() ) ;
}

// --- DESTRUCTORS ---

///
/// \fn PluginList::~PluginList()
/// \brief Destructor
///
PluginList::~PluginList
()
{
	for( PluginList::iterator it = this->begin() ;
		 it != this->end() ; ++it )
	{		
		delete *it ;
	}
}

// --- METHODS ---

///
/// \fn void PluginList::display_name() const
/// \brief Display items' name
///
void
PluginList::display_name
()
const
{
	for( PluginList::const_iterator cit = this->cbegin() ;
		 cit != this->cend() ; ++cit )
	{
		std::cout << ( *cit )->get_name() << std::endl ;
	}
}

///
/// \fn std::vector< std::string > extract_name() const
/// \brief Extract the name of each plugin
/// \return A vector which contains the name of each plugin stored in the PluginList
///
std::vector< std::string >
PluginList::extract_name
()
const
{
	std::vector< std::string > list_name ;
	
	for( PluginList::const_iterator cit = this->cbegin() ;
		 cit != this->cend() ; ++cit )
	{
		list_name.push_back( ( *cit )->get_name() ) ;
	}
	
	return list_name ;
}
