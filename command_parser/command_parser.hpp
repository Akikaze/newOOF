#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "oofobject.hpp"

// === CommandParser === (template)

template < typename T >
class CommandParser
: public OOF_LIST< CommandParser< T > >
, public OOF_SINGLETON< CommandParser< T > >
{
	friend class OOF_SINGLETON< CommandParser< T > > ;
	
	public :
		
		// --- DESTRUCTORS ---
		~CommandParser() ;
		
		// --- METHODS ---
		void parse( std::string ) ;
	
	protected :
		
	
	private :
		
		// --- CONSTRUCTORS ---
		CommandParser() ;
	
} ;

// --- CONSTRUCTORS ---

template < typename T >
CommandParser< T >::CommandParser
()
{
#if __DEBUG__
	std::cout << "CommandParser construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

template < typename T >
CommandParser< T >::~CommandParser
()
{
#if __DEBUG__
	std::cout << "CommandParser destruction" << std::endl ;
#endif
}



#endif // COMMAND_PARSER_HPP
