#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class Interface
{
	public:
		Interface() ;
		
		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething() ;
		
	private:
		int x ;
} ;

#endif
