#include "class.hpp"

#include <iostream>

extern "C"
Interface *
create
()
{
	return new Class ;
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

Class::Class
()
{
	x = 7 ;
}

Class::~Class
()
{
	
}

void
Class::DoSomething
()
{
	std::cout << x << std::endl ;
}
