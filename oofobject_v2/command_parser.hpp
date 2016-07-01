#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

// #define __DEBUG__

#include "oofobject.hpp"
#include "std.hpp"

// ===== ISubCommandParser =====

/*
 * The aim of this interface is just to be able to create a vector in
 * MainCommandParser that contains all SubCommandParser
 */

class ISubCommandParser
{
	friend class MainCommandParser ; // parse
	
	private :
		
		// --- METHODS ---
		virtual void parse( const std::string & ) const = 0 ;
} ;

// ===== MainCommandParser =====

/*
 * MainCommandParser is a Singleton class. It parses a command and transfers
 * the command line to the specific SubCommandParser. It contains the list
 * of all SubCommandParser. The destruction of the MainCommandParser provoke
 * the destruction of every SubCommandParser in the list.
 */

class MainCommandParser
: public OOF_SINGLETON< MainCommandParser >
{
	friend class OOF_SINGLETON< MainCommandParser > ; // constructor
	
	public :
	
		// --- DESTRUCTORS ---
		~MainCommandParser() ;
		
		// --- METHODS ---
		void add_list( ISubCommandParser * ) ;
		void display_list() const ;
		void parse( const std::string & ) ;
	
	private :
		
		// --- CONSTRUCTORS ---
		MainCommandParser() ;
		
		// --- ATTRIBUTES ---
		std::vector< ISubCommandParser * > _list_parser_ ;
	
} ;

// ===== SubCommandParser< T > =====

/*
 * SubCommandParser is a Singleton class with a private destructor. It's 
 * a portion of the whole pattern Chain of Responsability. The only way
 * to destroy a SubCommandParser is to destroy the MainCommandParser.
 * Every OOF_OBJ object has got his own SubCommandParser which is defined
 * when the typename is created.
 */

template < typename T >
class SubCommandParser
: public OOF_SINGLETON< SubCommandParser< T > >
, public ISubCommandParser
{
	friend class OOF_SINGLETON< SubCommandParser< T > > ; // constructor
	
	private :
		
		// --- CONSTRUCTORS ---
		SubCommandParser() ;
	
		// --- DESTRUCTORS ---
		~SubCommandParser() ;
		
		// --- METHODS ---
		virtual void parse( const std::string & ) const ;
	
} ;

// --- CONSTRUCTORS ---

template < typename T >
SubCommandParser< T >::SubCommandParser
()
{
#ifdef __DEBUG__
	std::cout << "SubCommandParser construction" << std::endl ;
#endif

	MainCommandParser::get_instance()->add_list( this ) ;
}

// --- DESTRUCTORS ---

template < typename T >
SubCommandParser< T >::~SubCommandParser
()
{
#ifdef __DEBUG__
	std::cout << "SubCommandParser destruction" << std::endl ;
#endif
}

// --- METHODS ---

template < typename T >
void
SubCommandParser< T >::parse
(
	const std::string & command
)
const
{
	std::cerr << "No parse method was defined for the command: " << command << std::endl ;
}

#endif // COMMAND_PARSER_HPP
