#include <iostream>

#include "plugin_list.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	PluginList pl( "./libraries" ) ;
	pl.display_name() ;
}
