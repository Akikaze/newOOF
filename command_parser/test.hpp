#ifndef TEST_HPP
#define TEST_HPP

// #define __DEBUG__

#include "command_parser.hpp"
#include "oofobject.hpp"

class TEST_A
: public OOF_LIST< TEST_A >
{
	public :
		TEST_A() ;
		~TEST_A() ;
} ;

class TEST_B
: public OOF_LIST< TEST_B >
{
	public :
		TEST_B() ;
		~TEST_B() ;
} ;

#endif // TEST_HPP
