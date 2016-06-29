#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	CommandParser< void > * cpV = CommandParser< void >::get_instance() ;
	std::cout << CommandParser< void >::_list_ << std::endl ;
	
	CommandParser< int > * cpI = CommandParser< int >::get_instance() ;
	std::cout << CommandParser< void >::_list_ << std::endl ;
	std::cout << CommandParser< int >::_list_ << std::endl ;
	
	delete cpI ;
	delete cpV ;
	
	return 0 ;
}
