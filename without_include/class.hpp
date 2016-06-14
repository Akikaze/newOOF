#ifndef CLASS_HPP
#define CLASS_HPP

#include "interface.hpp"

class Class
: public Interface
{
	public:
		Class() ;
		virtual ~Class() ;
		
		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething() ;
		
	private:
		int x ;
} ;

#endif
