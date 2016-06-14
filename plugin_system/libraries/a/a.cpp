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
: Interface()
{
	name_ = "A" ;
	description_ = "Example of plugin without a specific rank" ;
}

A::~A
()
{
	
}
