#ifndef TEST_HPP
#define TEST_HPP

#include "oofobject.hpp"

class TEST_A
: public OOF_SINGLETON< TEST_A >
{
	
} ;

class TEST_B
: public OOF_LIST< TEST_B >
, public OOF_SINGLETON< TEST_B >
{
	
} ;

#endif // TEST_HPP
