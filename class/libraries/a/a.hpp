#ifndef A_HPP
#define A_HPP

#include "../../interface.hpp"

class A
: public Interface
{
	public:
		A() ;
		virtual ~A() ;
		
		virtual void display() ;
} ;

#endif
