#include "test.hpp"

TEST_A::TEST_A
()
{
#ifdef __DEBUG__
	std::cout << "TEST_A construction" << std::endl ;
#endif
}

TEST_A::~TEST_A
()
{
#ifdef __DEBUG__
	std::cout << "TEST_A destruction" << std::endl ;
#endif
}

TEST_B::TEST_B
()
{
#ifdef __DEBUG__
	std::cout << "TEST_B construction" << std::endl ;
#endif
}

TEST_B::~TEST_B
()
{
#ifdef __DEBUG__
	std::cout << "TEST_B destruction" << std::endl ;
#endif
}
