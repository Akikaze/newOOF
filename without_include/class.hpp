#ifndef CLASS_HPP
#define CLASS_HPP

#include "interface.hpp"

class Class
: public Interface
{
	public:
		Class() ;
		
		virtual void printX() ;
		
	private:
		int x ;
} ;

#endif

