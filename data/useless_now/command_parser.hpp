#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "oofobject.hpp"

template < typename T >
class CommandParser
: public OOFOBJECT< CommandParser >
{
	public :
		void parse( std::string ) ;
	
	protected :
		
	
	private :
		
	
} ;

/*
template<>
class CommandParser< void >
: public OOFOBJECT< CommandParser< void > >
{
	public :
		
	
	protected :
		
	
	private :
		
	
} ;
*/
