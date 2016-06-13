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
	Interface * interface
)
{
	delete interface ;
}

Interface::Interface
()
{
	x = 9 ;
}

void
Interface::DoSomething
()
{
	std::cout << x << std::endl ;
}
