#include "test.hpp"

std::string Test::_typename_ = "Test" ;
std::string Test::_extension_ = ".oof_test" ;

Test::Test
(
	const std::string & name,
	const std::string & code
)
: OOF_OBJECT< Test >( name, code )
{
	variable_ = 5 ;
}

Test::~Test
()
{
}

void
Test::test
()
{
	std::cout << variable_ << std::endl ;
}

template <>
void
ObjectStorage< Test >::read_data
(
	std::ifstream & file,
	Test * object
)
const
{
	size_t pos ;
	std::string line ;
	
	std::getline( file, line ) ; // ===== DATA =====
	std::getline( file, line ) ; // empty line
	
	std::getline( file, line ) ;
	pos = line.find( " " ) ;
	object->variable_ = std::stoi( line.substr( pos + 1 ) ) ;
	
	std::getline( file, line ) ; // empty line
}

template <>
void
ObjectStorage< Test >::write_data
(
	std::ofstream & file,
	const Test * object
)
{
	file << "===== DATA =====" << std::endl ;
	file << std::endl ;
	
	file << "variable_ " << object->variable_ << std::endl ;
	
	file << std::endl ;
}
