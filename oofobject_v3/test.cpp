#include "test.hpp"

// ===== TEST_A =====

// --- CONSTRUCTORS ---

TEST_A::TEST_A
()
{
#ifdef __DEBUG__
	std::cout << "TEST_A construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

TEST_A::~TEST_A
()
{
#ifdef __DEBUG__
	std::cout << "TEST_A destruction" << std::endl ;
#endif
}

// --- ObjectStorage ---

template <>
void
ObjectStorage< TEST_A >::load
(
	const std::string & filename
)
const
{
	std::cout << "TEST_A load" << std::endl ;
}

template <>
void
ObjectStorage< TEST_A >::save
(
	const std::string & folder,
	const time_t & save_time
)
const
{
	std::cout << "TEST_A save" << std::endl ;
}

// ===== TEST_B =====

// --- CONSTRUCTORS ---

TEST_B::TEST_B
()
{
#ifdef __DEBUG__
	std::cout << "TEST_B construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

TEST_B::~TEST_B
()
{
#ifdef __DEBUG__
	std::cout << "TEST_B destruction" << std::endl ;
#endif
}

// --- SubCommandParser ---

template <>
void
SubCommandParser< TEST_B >::parse
(
	const std::string & command
)
const
{
	std::cerr << "TEST_B parsing: " << command << std::endl ;
}
