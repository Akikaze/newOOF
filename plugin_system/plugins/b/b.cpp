#include "b.hpp"

extern "C"
Interface *
load
()
{
	return new B ;
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
