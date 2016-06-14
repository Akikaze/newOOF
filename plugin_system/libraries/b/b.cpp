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
: Interface()
{
	name_ = "B" ;
	description_ = "Example of plugin with a specific rank" ;
	rank_ = 1 ;
}

B::~B
()
{
	
}
