#ifndef PLUGIN_LIST_HPP
#define PLUGIN_LIST_HPP

#include <algorithm>
#include <dirent.h>
#include <string.h>
#include <vector>

#include "plugin.hpp"

class PluginList
: public std::vector< Plugin * >
{
	public :
		
		// --- CONSTRUCTORS ---
		///
		/// \brief Constructor with parameter
		///
		PluginList( const std::string & ) ;
		
		// --- DESTRUCTORS ---
		///
		/// \brief Destructor
		///
		~PluginList() ; 
		
		// --- METHODS ---
		///
		/// \brief Display items' name
		///
		void display_name() const ;
		
		///
		/// \brief Extract the name of each plugin
		///
		std::vector< std::string > extract_name() const ;
		
		///
		/// \brief Extract the name of rank plugin
		///
		std::vector< unsigned short > extract_rank() const ;
		
	private :
		
		// --- CONSTRUCTORS ---
		///
		/// \brief Constructor
		///
		PluginList() ;
		
		// --- ATTRIBUTES ---
		std::string address_ ;
		
		// --- COMPARATOR ---
		///
		/// \brief Functor for the comparison of plugin in PluginList
		///
		struct PluginComparator {
			bool operator()(const Plugin * l, const Plugin * r) {
				return ( *l < *r ) ;
			}
		} ;
} ;

#endif // PLUGIN_LIST_HPP
