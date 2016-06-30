#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	MainCommandParser * mcp = MainCommandParser::get_instance() ;
	
	TEST_A * ta1 = new TEST_A() ;
	TEST_A * ta2 = new TEST_A() ;
	TEST_B() ;
	
	std::cout << IOOF_LIST::_object_ << std::endl ;
	std::cout << IOOF_SINGLETON::_object_ << std::endl ;
	
	/*
	std::vector< IOOF_LIST * > test = IOOF_LIST::_object_ ;
	std::vector< IOOF_LIST * >::const_iterator cit ;
	
	for( cit = test.cbegin() ; cit != test.cend() ; ++cit )
	{
		
		std::cout << ( *cit )->get_list() << std::endl ;
	}
	*/
	
	delete ta1 ;
	delete ta2 ;
	delete mcp ;
	
	return 0 ;
}
