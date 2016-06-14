#include "a.hpp"

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
	name_ = "A" ;
	description_ = "Example of plugin" ;
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
