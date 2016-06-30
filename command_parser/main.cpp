#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	MainCommandParser * mcp = MainCommandParser::get_instance() ;
	mcp->display_list() ;
	
	TEST_A() ;
	mcp->display_list() ;
	
	TEST_B() ;
	mcp->display_list() ;
	
	mcp->parse( "hi !" ) ;
	
	delete mcp ;
	
	return 0 ;
}
