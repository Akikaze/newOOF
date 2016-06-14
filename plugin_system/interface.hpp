#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <climits>
#include <iostream>

class Interface
{
	public :
		Interface() ;
		
		virtual ~Interface() = 0 ;
		
		virtual std::string get_name()
			{ return name_ ; }
		
		virtual std::string get_description()
			{ return description_ ; }
			
		virtual short get_rank()
			{ return rank_ ; }
	
	protected :
		std::string name_ ;
		std::string description_ ;
		unsigned short rank_ ;
} ;

#endif // INTERFACE_HPP
