#include <iostream>

#include "plugin_list.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	PluginList pl( "./plugins" ) ;
	pl.display_name() ;
}
