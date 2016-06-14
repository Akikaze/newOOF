#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>

class Interface
{
	public :
		Interface() ;
		
		virtual ~Interface() ;
		
		virtual void display() = 0 ;
		
		virtual std::string get_name()
			{ return name_ ; }
		
		virtual std::string get_description()
			{ return description_ ; }
	
	protected :
		std::string name_ ;
		std::string description_ ;
} ;

#endif
