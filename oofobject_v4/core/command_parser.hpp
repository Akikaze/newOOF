#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "instance_manager.hpp"
#include "log_device.hpp"

// ===== ISubCommandParser =====

/*
 * The aim of this interface is just to be able to create a vector in
 * CommandParser that contains all SubCommandParser
 */

class ISubCommandParser
{
	friend class CommandParser ; // parse
	
	protected :
		
		// --- DESTRUCTORS ---
		inline virtual ~ISubCommandParser() {}
		
		// --- METHODS ---
		virtual void parse( const std::string & ) const = 0 ;
} ;

// ===== CommandParser =====

/*
 * CommandParser is a Singleton class. It parses a command and transfers
 * the command line to the specific SubCommandParser. It contains the list
 * of all SubCommandParser. The destruction of the CommandParser provoke
 * the destruction of every SubCommandParser in the list.
 */

class CommandParser
: public OOF_SINGLETON< CommandParser >
{
	friend class OOF_SINGLETON< CommandParser > ; // constructor
	friend class Core ; // destructor
	
	public :
	
		// --- DESTRUCTORS ---
		~CommandParser() ;
		
		// --- METHODS ---
		void add_map( const std::string &, ISubCommandParser * ) ;
		void display_map() const ;
		void parse( const std::string & ) ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		CommandParser() ;
		
		// --- ATTRIBUTES ---
		LogDevice * ld_ ;
		std::map< std::string, ISubCommandParser * > map_parser_ ;
} ;

// ===== SubCommandParser =====

/*
 * SubCommandParser is a Singleton class with a private destructor. It's 
 * a portion of the whole pattern Chain of Responsability. The only way
 * to destroy a SubCommandParser is to destroy the CommandParser.
 * Every OOF_OBJ object has got his own SubCommandParser which is defined
 * when the typename is created.
 */

template < class T >
class SubCommandParser
: public OOF_SINGLETON< SubCommandParser< T > >
, public ISubCommandParser
{
	friend class OOF_SINGLETON< SubCommandParser< T > > ; // constructor
	
	protected :
		
		// --- CONSTRUCTORS ---
		SubCommandParser() ;
	
		// --- DESTRUCTORS ---
		~SubCommandParser() ;
		
		// --- METHODS ---
		virtual void parse( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		InstanceManager * im_ ;
		LogDevice * ld_ ;
} ;

// --- CONSTRUCTORS ---

template < class T >
SubCommandParser< T >::SubCommandParser
()
{
	CommandParser::get_instance()->add_map( T::_typename_, this ) ;
	
	im_ = InstanceManager::get_instance() ;
	ld_ = LogDevice::get_instance() ;
}

// --- DESTRUCTORS ---

template < class T >
SubCommandParser< T >::~SubCommandParser
()
{
}

// --- METHODS ---

template < class T >
void
SubCommandParser< T >::parse
(
	const std::string & command
)
const
{
	ld_->log( "No parse method was defined for the command: " + command, LOG_FLAG::REPORT ) ;
}

#endif // COMMAND_PARSER_HPP
