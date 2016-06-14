#include "a.hpp"

#include <iostream>

extern "C"
Interface *
create
()
{
	return new A ;
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

A::A
()
{
	
}

A::~A
()
{
	
}

void
A::display
()
{
	std::cout << "Hi, I'm an object of A" << std::endl ;
}
