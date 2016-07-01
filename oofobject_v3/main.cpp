#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{		
	TEST_A * ta1 = new TEST_A() ;
	TEST_A * ta2 = new TEST_A() ;
	TEST_B * tb1 = new TEST_B() ;
	
	delete ta1 ;
	delete ta2 ;
	delete tb1 ;
	
	delete CommandParser::get_instance() ;
	delete ProjectStorage::get_instance() ;
	
	return 0 ;
}
