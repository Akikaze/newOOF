#include <iostream>

#include "plugin.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	Plugin * plugin = new Plugin( "./libraries/a" ) ;
	delete plugin ;
}
