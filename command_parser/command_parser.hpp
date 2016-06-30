#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

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
		std::vector< ISubCommandParser * > _list_ ;
	
} ;

// ===== SubCommandParser< T > =====

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
