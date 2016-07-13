#include "test.hpp"

std::string Test::_typename_ = "Test" ;

Test::Test
( const std::string & name )
: OOF_OBJECT< Test >( name )
{
}

Test::~Test
()
{
}
