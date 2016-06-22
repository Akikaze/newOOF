#include "a.hpp"

extern "C"
Interface *
load
()
{
	return new A ;
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
