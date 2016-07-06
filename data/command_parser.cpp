#include "command_parser.hpp"

// ===== CommandParser =====

// --- CONSTRUCTORS ---

CommandParser::CommandParser
()
{
#ifdef __DEBUG__
	std::cout << "CommandParser construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

CommandParser::~CommandParser
()
{
#ifdef __DEBUG__
	std::cout << "CommandParser destruction" << std::endl ;
#endif

	while( !( list_parser_.empty() ) )
	{
		delete list_parser_[ 0 ] ;
		list_parser_.erase( list_parser_.cbegin() ) ;
	}
}

// --- METHODS ---

void
CommandParser::add_list
(
	ISubCommandParser * command_parser
)
{
	list_parser_.push_back( command_parser ) ;
}

void
CommandParser::display_list
()
const
{
	std::cout << list_parser_ << std::endl ;
}

void
CommandParser::parse
(
	const std::string & command
)
{
	/*
	 * Ths content is not the real definition of the CommandParser main
	 * method. Normally, you need to choose which SubCommandParser is
	 * going to receive the command.
	 */

	std::vector< ISubCommandParser * >::const_iterator cit ;
	
	for( cit = list_parser_.cbegin() ; cit != list_parser_.cend() ; ++cit )
	{
		( *cit )->parse( command ) ;
	}
}
