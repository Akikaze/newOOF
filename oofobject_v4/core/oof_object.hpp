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

// in order to rename an object if it already exist in the system
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
	// tell to InstanceManager that it exists
	add( this ) ;
	
	// find a unique name for the session 
	give_name( name ) ;
	
	loaded_ = !( code.empty() ) ;
	if( loaded_ )
	{
		// if it is loaded, it already have its code
		code_ = code ;
	}
	else
	{
		// it creates its code thanks to the session time code
		code_ = "[" + Config::__SESSION__ + "]" + name_ ;
	}
	
	_ld_->log( "Construction of a " + T::_typename_ + " object named " + name_, LOG_FLAG::REPORT ) ;
	
	// in a normal case, those are useless. But to be safe, it's better to keep it
	ObjectStorage< T >::construct() ;
	SubCommandParser< T >::construct() ;
}

// --- DESTRUCTORS ---

template < class T >
OOF_OBJECT< T >::~OOF_OBJECT
()
{
	// tell to the InstanceManager to remove the pointer
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
	if( name.empty() || name.find( get_typename() + "_" ) != name.npos )
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
	
	// it the object was loaded and modified after
	if( loaded_ )
	{
		// create a new code (because it is not the same object)
		code_ = "[" + Config::__SESSION__ + "]" + name_ ;
		loaded_ = false ;
	}
}

#endif // OOF_OBJECT_HPP
