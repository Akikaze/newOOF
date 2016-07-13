#include "test.hpp"

#include "command_parser.hpp"
#include "instance_manager.hpp"
#include "log_device.hpp"
#include "project_storage.hpp"

int
main
(
	int argc,
	char ** argv
)
{
	Test * t = new Test() ;
	std::cout << t << std::endl ;
	std::cout << t->get_name() << std::endl ;
	std::cout << t->get_typename() << std::endl ;
	
	Test *t2 = new Test( "Test_1" ) ;
	std::cout << t2 << std::endl ;
	std::cout << t2->get_name() << std::endl ;
	
	std::cout << *( InstanceManager::get_instance() ) << std::endl ;
	CommandParser::get_instance()->parse( "Test.new_test" ) ;
	
	delete CommandParser::get_instance() ;
	delete InstanceManager::get_instance() ;
	delete LogDevice::get_instance() ;
	delete ProjectStorage::get_instance() ;
	
	return 0 ;
}
