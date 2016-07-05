#ifndef OOFOBJECT_HPP
#define OOFOBJECT_HPP

// #define __DEBUG__

#include <ctime>

#include "std.hpp"

// ===== prior definition =====

template < typename T > class SubCommandParser ;
template < typename T > class ObjectStorage ;

// ===== IOOF_SINGLETON =====

/*
 * Interface for the OOF_SINGLETON class: the aim is to keep trace of each 
 * typename which define a OOF_SINGLETON in _object_. _object_ is accessible
 * from all object which inherit from OOF_SINGLETON.
 */

class IOOF_SINGLETON
{
	public :
		
		// --- ATTRIBUTES ---
		
		// --- static ---
		static std::vector< IOOF_SINGLETON * > _list_singleton_ ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		IOOF_SINGLETON() ;
		
		// --- DESTRUCTORS ---
		~IOOF_SINGLETON() ;
} ;

// ===== OOF_SINGLETON =====

/*
 * OOF_SINGLETON is a template class which store the pattern Singleton.
 * For creating a Singleton from CLASS_B, you need three steps :
 * 1 - your class must inherit from OOF_SINGLETON< CLASS_B >
 * 2 - define that OOF_SINGLETON< CLASS_B > is a friend of CLASS_B
 * 3 - make the CLASS_B constructor private
 */

template < typename T >
class OOF_SINGLETON
: public IOOF_SINGLETON
{
	public :
		
		// --- DESTRUCTORS ---
		~OOF_SINGLETON() ;
		
		// --- GETTERS ---
		static T * get_instance() ;
		
	protected :
	
		// --- CONSTRUCTORS ---
		OOF_SINGLETON() ;
		OOF_SINGLETON( const OOF_SINGLETON & ) ;
		
		// --- ATTRIBUTES ---
		static T * _instance_ ;
} ;

// --- static ---

template < typename T >
T * OOF_SINGLETON< T >::_instance_ = NULL ;

// --- CONSTRUCTORS ---

template < typename T >
OOF_SINGLETON< T >::OOF_SINGLETON
()
{
#ifdef __DEBUG__
	std::cout << "OOF_SINGLETON construction" << std::endl ;
#endif
}

template < typename T >
OOF_SINGLETON< T >::OOF_SINGLETON
(
	const OOF_SINGLETON< T > &
)
{
#ifdef __DEBUG__
	std::cout << "OOF_SINGLETON copy construction" << std::endl ;
#endif
}

// --- DESTRUCTORS ---

template < typename T >
OOF_SINGLETON< T >::~OOF_SINGLETON
()
{
#ifdef __DEBUG__
	std::cout << "OOF_SINGLETON destruction" << std::endl ;
#endif
}

// --- GETTERS ---

template < typename T >
T *
OOF_SINGLETON< T >::get_instance
()
{
	if( _instance_ == NULL )
	{
		_instance_ = new T() ;
	}
	
	return _instance_ ;
}

// ===== IOOF_OBJ =====

/*
 * Interface for the OOF_OBJ class: the aim is to keep trace of each 
 * typename which define a OOF_OBJ in _object_. _object_ is accessible
 * from all object which inherit from OOF_OBJ.
 */

class IOOF_OBJ
{
	public :
	
		// --- GETTERS ---
		virtual std::string get_typename() const = 0 ;
		
		// --- COMPARATOR ---
		struct IOOF_OBJComparator {
			bool operator()( const IOOF_OBJ * l, const IOOF_OBJ * r ) {
				return ( l->last_update_ < r->last_update_ ) ;
			}
		} ;
		
		// --- ATTRIBUTES ---
		time_t last_update_ ;
		
		// --- static ---
		static std::vector< IOOF_OBJ * > _list_list_ ;
		static std::vector< IOOF_OBJ * > _list_type_ ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		IOOF_OBJ() ;
		
		// --- DESTRUCTORS ---
		~IOOF_OBJ() ;
} ;

// ===== OOF_OBJ =====

/*
 * OOF_OBJ is a template class which store any instance of an object of 
 * a specific typename.
 * For example : if you have three instance of CLASS_A and if CLASS_A inherit
 * from OOF_OBJ< CLASS_A >, in this case, you can reach any instance with
 * OOF_OBJ< CLASS_A >::_list_.
 * The construction of a object OOF_OBJ create a SubCommandParser and a
 * ObjectStorage specific.
 */

template < typename T >
class OOF_OBJ
: public IOOF_OBJ
{
	public :
	
		// --- GETTERS ---
		virtual std::string get_typename() const = 0 ;
		
		// --- static ---
		static std::vector< T * > _list_instance_ ;
		static T * _type_instance_ ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		OOF_OBJ() ;
		
		// --- DESTRUCTORS ---
		~OOF_OBJ() ;
		
} ;

// --- static ---

template < typename T > std::vector< T * > OOF_OBJ< T >::_list_instance_ = std::vector< T * >() ;
template < typename T > T * OOF_OBJ< T >::_type_instance_ = NULL ;

// --- CONSTRUCTORS ---

template < typename T >
OOF_OBJ< T >::OOF_OBJ
()
{
#ifdef __DEBUG__
	std::cout << "OOF_OBJ construction" << std::endl ;
#endif

	T * this_cast = ( T* ) this ;
	
	// if it's a new type, we add the instance in _list_type_
	if( _list_instance_.empty() )
	{
		_type_instance_ = this_cast ;
		_list_type_.push_back( _type_instance_ ) ;
	}
	
	// we add the instance in _list_instance_
	_list_instance_.push_back( this_cast ) ;
	
	SubCommandParser< T >::get_instance() ;
	ObjectStorage< T >::get_instance() ;
}

// --- DESTRUCTORS ---

template < typename T >
OOF_OBJ< T >::~OOF_OBJ
()
{
#ifdef __DEBUG__
	std::cout << "OOF_OBJ destruction" << std::endl ;
#endif

	typename std::vector< T * >::const_iterator cit = _list_instance_.cbegin() ;
	T * cast_this = ( T* ) this ;
	
	while( *cit != cast_this )
	{
		++cit ;
	}
	
	_list_instance_.erase( cit ) ;
	
	// if _type_instance_ is this instance, we need to change it there and in _list_type_
	if( _type_instance_ == cast_this )
	{
		// iterator on the type in _list_type_
		std::vector< IOOF_OBJ * >::iterator it = _list_type_.begin() ;
		
		while( *it != cast_this )
		{
			++it ;
		}
		
		// if _list_instance_ is empty, we erase the type
		if( _list_instance_.empty() )
		{
			_type_instance_ = NULL ;
			_list_type_.erase( it ) ;
		}
		// else, we change the _type_instance_
		else
		{
			_type_instance_ = _list_instance_[ 0 ] ;
			( *it ) = _type_instance_ ;
		}
		
	}
}

#endif // OOFOBJECT_HPP
