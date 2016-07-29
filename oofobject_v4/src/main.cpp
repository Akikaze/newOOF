#include "../basis/core.hpp"
#include "test.hpp"

#include <cstring>

int
main
(
	int argc,
	char ** argv
)
{
	Core::construct() ;
	
	
	Core::get_instance()->load() ;
	
	std::cout << *( InstanceManager::get_instance() ) << std::endl ;
	Test * t = static_cast< Test * >( ( ( InstanceManager::get_instance() )->begin() )->second ) ;
	
	std::cout << t << " " ;
	t->test() ;
	
	
	/*
	Test * t = new Test() ;
	std::cout << t << std::endl ;
	std::cout << t->get_name() << std::endl ;
	std::cout << t->get_typename() << std::endl ;
	
	Test *t2 = new Test( "Test_1" ) ;
	std::cout << t2 << std::endl ;
	std::cout << t2->get_name() << std::endl ;
	std::cout << t2->get_typename() << std::endl ;
	
	std::cout << *( InstanceManager::get_instance() ) << std::endl ;
	CommandParser::get_instance()->parse( "Prout.new_test" ) ;
	
	delete t ;
	
	Core::get_instance()->save() ;
	*/
	
	Core::destroy() ;
	
	return 0 ;
}
