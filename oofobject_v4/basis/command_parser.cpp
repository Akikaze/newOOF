#include "command_parser.hpp"

// ===== CommandParser =====

// --- CONSTRUCTORS ---

CommandParser::CommandParser
()
{
	// get a pointer on the LogDevice
	ld_ = LogDevice::get_instance() ;
}

// --- DESTRUCTORS ---

CommandParser::~CommandParser
()
{
	// delete every SubCommandParser
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
	// add a SubCommandParser in the CommandParser map
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
	// take the prefix of the command
	size_t pos = command.find( "." ) ;
	std::string prefix = command.substr( 0, pos ) ;
	
	// choose the right SubCommandParser thanks to the prefix
	ISubCommandParser * iscp = map_parser_[prefix] ;
	
	if( iscp == nullptr )
	{
		// invalid prefix
		ld_->log( "Command " + command + " doesn't have a valid prefix", LOG_FLAG::ERROR ) ;
	}
	else
	{
		// transfer the rest of the command to the SubCommandParser
		iscp->parse( command.substr( pos + 1 ) ) ;
	}
}
