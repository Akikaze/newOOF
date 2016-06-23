#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	TEST_A * a = new TEST_A() ;
	TEST_B * b = new TEST_B() ;
	
	std::cout << a << std::endl ;
	std::cout << b << std::endl ;
	
	std::cout << TEST_A::_list_ << std::endl ;
	std::cout << TEST_B::_list_ << std::endl ;
	
	delete a ;
	delete b ;
	
	return 0 ;
}
