#ifndef TEST_HPP
#define TEST_HPP

// #define __DEBUG__

/*
 * WARNING: oofobject.hpp needs to be include before command_parser.hpp
 * But command_parser.hpp needs to be include eve if there is no link
 * between test.hpp and command_parser.hpp
 */
 
#include "oofobject.hpp"
#include "command_parser.hpp"

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
