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

	while( !( _list_parser_.empty() ) )
	{
		delete _list_parser_[ 0 ] ;
		_list_parser_.erase( _list_parser_.cbegin() ) ;
	}
}

// --- METHODS ---

void
MainCommandParser::add_list
(
	ISubCommandParser * command_parser
)
{
	_list_parser_.push_back( command_parser ) ;
}

void
MainCommandParser::display_list
()
const
{
	std::cout << _list_parser_ << std::endl ;
}

void
MainCommandParser::parse
(
	const std::string & command
)
{
	/*
	 * Ths content is not the real definition of the MainCommandParser
	 * main method. Normally, you need to choose which SubCommandParser
	 * is going to receive the command.
	 */

	std::vector< ISubCommandParser * >::const_iterator cit ;
	
	for( cit = _list_parser_.cbegin() ; cit != _list_parser_.cend() ; ++cit )
	{
		( *cit )->parse( command ) ;
	}
}

// ===== SubCommandParser (specialization) =====

/*
 * There is the location of all specialization of SubCommandParser. A parse
 * method is often a switch condition on the command line. Each case of 
 * the switch describe a specific list of command like creating a object,
 * changing its name, ...
 */

class TEST_B ; // prior definition

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
