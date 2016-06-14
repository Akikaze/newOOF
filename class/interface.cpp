#include "interface.hpp"

#include <iostream>

Interface::Interface
()
{
	
}

Interface::~Interface
()
{
	
}

void
Interface::display
()
{
	std::cout << "Hi, I'm an object of Interface, I should not be visible." << std::endl ;
}
