#ifndef OOF_OBJECT_HPP
#define OOF_OBJECT_HPP

#include "global.hpp"
#include "std.hpp"

// ===== IOOF_OBJECT =====

/*
 * 
 */

// ----- prior definition -----

class InstanceManager ;
class LogDevice ;

// ----- class -----

class IOOF_OBJECT
{
	public :
		
		// --- DESTRUCTORS ---
		virtual ~IOOF_OBJECT() ;
		
		// --- GETTERS ---
		std::string get_name() const
			{ return name_ ; }
		virtual std::string get_typename() const = 0 ;
		
		// --- COMPARATORS ---
		struct ComparatorName {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				return ( l->get_name() < r->get_name() ) ;
			}
		} ;
		struct ComparatorTime {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				return ( l->last_update_ < r->last_update_ ) ;
			}
		} ;
		struct ComparatorTypename {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				return ( l->get_typename() < r->get_typename() ) ;
			}
		} ;
		
		// --- ATTRIBUTES ---
		time_t last_update_ ;
		static LogDevice * _ld_ ;
		static InstanceManager * _im_ ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		IOOF_OBJECT() ;
		
		// --- METHODS ---
		void add( IOOF_OBJECT * ) const ;
		std::vector< IOOF_OBJECT * > extract( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		std::string name_ ;
} ;

// ===== OOF_SINGLETON =====

/*
 * OOF_SINGLETON is a template class which store the pattern Singleton.
 * For creating a Singleton from CLASS_B, you need three steps :
 * 1 - your class must inherit from OOF_SINGLETON< CLASS_B >
 * 2 - define that OOF_SINGLETON< CLASS_B > is a friend of CLASS_B
 * 3 - make the CLASS_B constructor private
 */

// ----- class -----

template < class T >
class OOF_SINGLETON
{
	public :
		
		// --- GETTERS ---
		static T * get_instance() ;
		
		// --- METHODS ---
		static void construct() ;
		static void destroy() ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		OOF_SINGLETON() ;
		OOF_SINGLETON( const OOF_SINGLETON & ) ;
		
		// --- DESTRUCTORS ---
		virtual ~OOF_SINGLETON() ;
		
		// --- ATTRIBUTES ---
		static T * _instance_ ;
} ;

// --- ATTRIBUTES ---

template < class T >
T * OOF_SINGLETON< T >::_instance_ = nullptr ;

// --- CONSTRUCTORS ---

template < class T >
OOF_SINGLETON< T >::OOF_SINGLETON
()
{
}

template < class T >
OOF_SINGLETON< T >::OOF_SINGLETON
(
	const OOF_SINGLETON< T > &
)
{
}

// --- DESTRUCTORS ---

template < class T >
OOF_SINGLETON< T >::~OOF_SINGLETON
()
{
}

// --- GETTERS ---

template < class T >
T *
OOF_SINGLETON< T >::get_instance
()
{
	construct() ;
	return _instance_ ;
}

// --- METHODS ---

template < class T >
void
OOF_SINGLETON< T >::construct
()
{
	if( _instance_ == nullptr )
	{
		_instance_ = new T() ;
	}
}

template < class T >
void
OOF_SINGLETON< T >::destroy
()
{
	if( _instance_ != nullptr )
	{
		delete _instance_ ;
		_instance_ = nullptr ;
	}
}

// ===== IOOF_OBJECT ======

// ----- late includes -----

#include "instance_manager.hpp"
#include "log_device.hpp"

// ===== OOF_OBJECT =====

/*
 * 
 */

// ----- prior definition -----

template < class T > class ObjectStorage ;
template < class T > class SubCommandParser ;

// ----- class -----

template < class T >
class OOF_OBJECT
: public IOOF_OBJECT
{
	public :
	
		// --- GETTERS ---
		virtual std::string get_typename() const ;
		
		// --- ATTRIBUTES ---
		static unsigned short _index_ ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		OOF_OBJECT( const std::string & name = "" ) ;
		
		// --- DESTRUCTORS ---
		~OOF_OBJECT() ;
		
		// --- METHODS ---
		void give_name( const std::string & ) ;
		
		// --- ATTRIBUTES ---
		static std::string _typename_ ;
} ;

// ----- late includes -----

#include "command_parser.hpp"
#include "project_storage.hpp"

// --- ATTRIBUTES ---

template < class T >
unsigned short OOF_OBJECT< T >::_index_ = 0 ;

template < class T >
std::string OOF_OBJECT< T >::_typename_ = "OOF_OBJECT<?>" ;

// --- CONSTRUCTORS ---

template < class T >
OOF_OBJECT< T >::OOF_OBJECT
(
	const std::string & name
)
: IOOF_OBJECT()
{
	add( this ) ;
	give_name( name ) ;
	
	ObjectStorage< T >::construct() ;
	SubCommandParser< T >::construct() ;
}

// --- DESTRUCTORS ---

template < class T >
OOF_OBJECT< T >::~OOF_OBJECT
()
{
}

// --- GETTERS ---

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

#endif // OOF_OBJECT_HPP
