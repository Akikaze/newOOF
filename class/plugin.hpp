#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <dlfcn.h>
#include <iostream>
#include <string>
#include "interface.hpp"

class Plugin
{
	public :
		
		// --- CONSTRUCTORS ---
		///
		/// \brief Constructor
		/// \param address of plugin's folder
		///
		Plugin( const std::string & ) ;
		
		// --- DESTRUCTORS ---
		///
		/// \brief Destructor
		///
		~Plugin() ;
		
		// --- GETTERS / SETTERS ---
		///
		/// \brief Getter for name_
		///
		std::string get_name() const
			{ return name_ ; }
		
		///
		/// \brief Getter for description_
		///
		std::string get_description() const
			{ return description_ ; }
			
		///
		/// \brief Getter for address_
		///
		std::string get_adress() const
			{ return address_ ; }
			
		///
		/// \brief Getter for pointer_
		///
		Interface * get_pointer() const
			{ return pointer_ ; }
		
		// --- METHODS ---
		///
		/// \brief Tell if the library is correctly load
		///
		bool is_loaded() const
			{ return ( pointer_ != NULL ) ; }
		
		// --- OPERATORS ---
		
		
	private :
		
		// --- CONSTRUCTORS ---
		///
		/// \brief Constructor
		///
		Plugin() ;
		
		// --- METHODS ---
		///
		/// \brief find the library path thanks to the folder's address
		/// \param address of plugin's folder
		///
		std::string find_library( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		std::string name_ ;
		std::string description_ ;
		std::string address_ ;
		Interface * pointer_ ;
		// attribute for plugin's construction and destruction
		void * handle_ ;
		Interface * ( * create_ )() ;
		void ( * destroy_ )( Interface * ) ;
} ;

#endif // PLUGIN_HPP
