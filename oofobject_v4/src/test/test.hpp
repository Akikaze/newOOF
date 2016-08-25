#ifndef TEST_HPP
#define TEST_HPP

#include "../../basis/oof_object.hpp"

class Test
: public OOF_OBJECT< Test >
{
	friend class SubCommandParser< Test > ;
	friend class ObjectStorage< Test > ;
	
	public :
	
		Test( const std::string & name = "", const std::string & code = "" ) ;
		~Test() ;
		void test() ;
		
		static std::string _extension_ ;
		static std::string _typename_ ;
		
	protected :
		
		int variable_ ;
} ;

#endif // TEST_HPP
