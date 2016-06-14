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
		Plugin( const std::string & ) ;
		
		// --- DESTRUCTORS ---
		~Plugin() ;
		
		// --- GETTERS / SETTERS ---
		std::string get_name()
			{ return name_ ; }
		
		std::string get_description()
			{ return description_ ; }
			
		std::string get_adress()
			{ return address_ ; }
			
		Interface * get_pointer()
			{ return pointer_ ; }
		
	private :
		
		// --- METHODS ---
		std::string find_library( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		std::string name_ ;
		std::string description_ ;
		std::string address_ ;
		Interface * pointer_ ;
		void * handle_ ;
		Interface * ( * create_ )() ;
		void ( * destroy_ )( Interface * ) ;
} ;

#endif // PLUGIN_HPP
