#ifndef OOF_OBJECT_HPP
#define OOF_OBJECT_HPP

#include "ioof_object.hpp"
#include "command_parser.hpp"
#include "project_storage.hpp"

// ===== OOF_OBJECT =====

/*
 * 
 */

// ----- class -----

template < class T >
class OOF_OBJECT
: public IOOF_OBJECT
{	
	public :
	
		// --- GETTERS ---
		virtual std::string get_extension() const ;
		virtual std::string get_typename() const ;
				
		// --- ATTRIBUTES ---
		static unsigned short _index_ ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		OOF_OBJECT( const std::string & name = "", const std::string & code = "" ) ;
		
		// --- DESTRUCTORS ---
		~OOF_OBJECT() ;
		
		// --- METHODS ---
		void give_name( const std::string & ) ;
		void update() ;
		
		// --- ATTRIBUTES ---
		static std::string _extension_ ;
		static std::string _typename_ ;
} ;

// --- ATTRIBUTES ---

template < class T >
unsigned short OOF_OBJECT< T >::_index_ = 0 ;

template < class T >
std::string OOF_OBJECT< T >::_extension_ = ".oof_????" ;

template < class T >
std::string OOF_OBJECT< T >::_typename_ = "OOF_OBJECT<?>" ;

// --- CONSTRUCTORS ---

template < class T >
OOF_OBJECT< T >::OOF_OBJECT
(
	const std::string & name,
	const std::string & code
)
: IOOF_OBJECT()
{
	add( this ) ;
	give_name( name ) ;
	
	loaded_ = !( code.empty() ) ;
	if( loaded_ )
	{
		code_ = code ;
	}
	else
	{
		code_ = "[" + Config::__SESSION__ + "]" + name_ ;
	}
	
	_ld_->log( "Construction of a " + T::_typename_ + " object named " + name_, LOG_FLAG::REPORT ) ;
	
	ObjectStorage< T >::construct() ;
	SubCommandParser< T >::construct() ;
}

// --- DESTRUCTORS ---

template < class T >
OOF_OBJECT< T >::~OOF_OBJECT
()
{
	remove( this ) ;
	
	_ld_->log( "Destruction of a " + T::_typename_ + " object named " + name_, LOG_FLAG::REPORT ) ;
}

// --- GETTERS ---

template < class T >
std::string
OOF_OBJECT< T >::get_extension
()
const
{
	return T::_extension_ ;
}

template < class T >
std::string
OOF_OBJECT< T >::get_typename
()
const
{
	return T::_typename_ ;
}

// --- METHODS ---

template < class T >
void
OOF_OBJECT< T >::give_name
(
	const std::string & name
)
{
	// signal
	bool rename = false ;
	
	// no name -> rename
	if( name.empty() )
	{
		rename = true ;
	}
	else
	{
		std::vector< IOOF_OBJECT * >::iterator it ;
		std::vector< IOOF_OBJECT * > list_instance = extract( this->get_typename() ) ;
		
		it = std::find_if( list_instance.begin(),
						   list_instance.end(),
						   [&name] (IOOF_OBJECT * i) -> bool { return ( i->get_name() == name ) ; } ) ;
		
		// name already used -> rename
		if ( it != list_instance.end() )
		{
			rename = true ;
		}
	}
	
	if( rename == true )
	{
		// name is a combination of the type and 
		_index_++ ;
		name_ = get_typename() + "_" + std::to_string( _index_ ) ;
	}
	else
	{
		name_ = name ;
	}
}

template < class T >
void
OOF_OBJECT< T >::update
()
{
	last_update_ = time( NULL ) ;
	
	if( loaded_ )
	{
		code_ = "[" + Config::__SESSION__ + "]" + name_ ;
		loaded_ = false ;
	}
}

#endif // OOF_OBJECT_HPP
