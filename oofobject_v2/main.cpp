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
	TEST_B * tb1 = new TEST_B() ;
	
	std::cout << std::endl ;
	std::cout << "ROUND 1" << std::endl ;
	std::cout << std::endl ;
	
	std::cout << "List of all listed objects" << std::endl ;
	std::cout << IOOF_OBJ::_list_list_ << std::endl ;
	
	std::cout << "List of all type of objects" << std::endl ;
	std::cout << IOOF_OBJ::_list_type_ << std::endl ;
	
	std::cout << "List of all singletons" << std::endl ;
	std::cout << IOOF_SINGLETON::_list_singleton_ << std::endl ;
	
	std::cout << "List of TEST_A elements" << std::endl ;
	std::cout << OOF_OBJ< TEST_A >::_list_instance_ << std::endl ;
	
	std::cout << "List of TEST_A elements from an instance of TEST_A" << std::endl ;
	std::cout << ta2->_list_instance_ << std::endl ;
	
	std::cout << "List of TEST_B elements" << std::endl ;
	std::cout << OOF_OBJ< TEST_B >::_list_instance_ << std::endl ;
	
	std::cout << "List of void elements" << std::endl ;
	std::cout << OOF_OBJ< void >::_list_instance_ << std::endl ;
	
	std::cout << IOOF_OBJ::_list_type_[ 0 ]->get_typename() << std::endl ;
	
	delete ta1 ;
	delete ta2 ;
	delete tb1 ;
	delete mcp ;
	
	return 0 ;
}
