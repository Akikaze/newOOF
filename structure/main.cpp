#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	Core::construct() ;
	
	TEST_A ta1 ;
	TEST_A * ta2 = new TEST_A() ;
	TEST_B tb ;
	
	delete ta2 ;
	
	Core::destroy() ;
	
	return 0 ;
}
