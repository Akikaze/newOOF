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
		/// \brief Constructor with parameter
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
		
		///
		/// \brief Getter for rank_
		///
		unsigned short get_rank() const
			{ return rank_ ; }
		
		// --- METHODS ---
		///
		/// \brief Tell if the library is correctly load
		///
		bool is_loaded() const
			{ return ( pointer_ != NULL ) ; }
		
		// --- OPERATORS ---
		///
		/// \brief Operator <
		///
		bool operator<( const Plugin & ) const ;
		
	private :
		
		// --- CONSTRUCTORS ---
		///
		/// \brief Constructor
		///
		Plugin() ;
		
		// --- METHODS ---
		///
		/// \brief Unload a plugin
		///
		void unload_plugin( Interface * object ) ;

		///
		/// \brief Find the library path thanks to the folder's address
		///
		std::string find_library( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		std::string name_ ;
		std::string description_ ;
		std::string address_ ;
		Interface * pointer_ ;
		unsigned short rank_ ;
		void * lib_descriptor_ ;
} ;

#endif // PLUGIN_HPP
