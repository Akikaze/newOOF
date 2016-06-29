#include "command_parser.hpp"

// ===== MainCommandParser =====

// --- CONSTRUCTORS ---

MainCommandParser::MainCommandParser
()
{
#ifdef __DEBUG__
	std::cout << "MainCommandParser construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

MainCommandParser::~MainCommandParser
()
{
#ifdef __DEBUG__
	std::cout << "MainCommandParser destruction" << std::endl ;
#endif

	while( !( _list_.empty() ) )
	{
		delete _list_[ 0 ] ;
		_list_.erase( _list_.cbegin() ) ;
	}
}

// --- METHODS ---

void
MainCommandParser::add_list
(
	ISubCommandParser * command_parser
)
{
	_list_.push_back( command_parser ) ;
}

void
MainCommandParser::display_list
()
const
{
	std::cout << _list_ << std::endl ;
}

void
MainCommandParser::parse
(
	const std::string & command
)
{
	
}

// ===== SubCommandParser (specialization) =====
