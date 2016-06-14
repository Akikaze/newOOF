#include "b.hpp"

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
	name_ = "B" ;
	description_ = "Example of plugin" ;
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
