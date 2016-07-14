#include "core.hpp"
#include "test.hpp"


int
main
(
	int argc,
	char ** argv
)
{
	Core::construct() ;
	
	
	
	Test * t = new Test() ;
	std::cout << t << std::endl ;
	std::cout << t->get_name() << std::endl ;
	std::cout << t->get_typename() << std::endl ;
	
	Test *t2 = new Test( "Test_1" ) ;
	std::cout << t2 << std::endl ;
	std::cout << t2->get_name() << std::endl ;
	std::cout << t2->get_typename() << std::endl ;
	
	std::cout << *( InstanceManager::get_instance() ) << std::endl ;
	CommandParser::get_instance()->parse( "Test.new_test" ) ;
	
	
	
	Core::destroy() ;
	
	return 0 ;
}
