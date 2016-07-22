#include "command_parser.hpp"

// ===== CommandParser =====

// --- CONSTRUCTORS ---

CommandParser::CommandParser
()
{
	ld_ = LogDevice::get_instance() ;
}

// --- DESTRUCTORS ---

CommandParser::~CommandParser
()
{
	while( !( map_parser_.empty() ) )
	{
		delete ( *( map_parser_.begin() ) ).second ;
		map_parser_.erase( map_parser_.cbegin() ) ;
	}
}

// --- METHODS ---

void
CommandParser::add_map
(
	const std::string & type,
	ISubCommandParser * command_parser
)
{
	map_parser_.insert( make_pair( type, command_parser ) ) ;
}

void
CommandParser::display_map
()
const
{
	std::cout << map_parser_ << std::endl ;
}

void
CommandParser::parse
(
	const std::string & command
)
{
	size_t pos = command.find( "." ) ;
	std::string prefix = command.substr( 0, pos ) ;
	
	ISubCommandParser * iscp = map_parser_[prefix] ;
	
	if( iscp == nullptr )
	{
		ld_->log( "Command " + command + " doesn't have a valid prefix", LOG_FLAG::ERROR ) ;
	}
	else
	{
		iscp->parse( command.substr( pos + 1 ) ) ;
	}
}
