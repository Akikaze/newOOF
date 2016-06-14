#include "b.hpp"

#include <iostream>

extern "C"
Interface *
create
()
{
	return new B ;
}

extern "C"
void
destroy
(
	Interface * object
)
{
	delete object ;
}

B::B
()
{
	
}

B::~B
()
{
	
}

void
B::display
()
{
	std::cout << "Hi, I'm an object of B" << std::endl ;
}
