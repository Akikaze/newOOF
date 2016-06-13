#include "interface.hpp"

#include <iostream>

extern "C"
Interface *
create
()
{
	return new Interface ;
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

Interface::Interface
()
{
	x = 9 ;
}

void
Interface::printX
()
{
	std::cout << x << std::endl ;
}
