#ifndef TEST_HPP
#define TEST_HPP

#include "oof_object.hpp"

class Test
: public OOF_OBJECT< Test >
{
	public :
	
		Test( const std::string & name = "" ) ;
		~Test() ;
		static std::string _typename_ ;
} ;

#endif // TEST_HPP
