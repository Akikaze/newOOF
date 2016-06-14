#include <iostream>

#include "plugin.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	Plugin * pluginA = new Plugin( "./libraries/a" ) ;
	if( pluginA->is_loaded() )
		std::cout << pluginA->get_name() << std::endl ;
	else
		std::cout << "The library of pluginA was not correctly loaded." << std::endl ;
	delete pluginA ;
	
	Plugin * pluginB = new Plugin( "./libraries/b" ) ;
	if( pluginB->is_loaded() )
		std::cout << pluginB->get_name() << std::endl ;
	else
		std::cout << "The library of pluginB was not correctly loaded." << std::endl ;
	delete pluginB ;
}
