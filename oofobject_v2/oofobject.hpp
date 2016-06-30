#ifndef OOFOBJECT_HPP
#define OOFOBJECT_HPP

#include "std.hpp"

// ===== prior definition =====

template < typename T > class SubCommandParser ;

// ===== IOOF_LIST =====

/*
 * Interface for the OOF_LIST class: the aim is to keep trace of each 
 * typename which define a OOF_LIST in _object_. _object_ is accessible
 * from all object which inherit from OOF_LIST.
 */

class IOOF_LIST
{
	public :
		
		// --- ATTRIBUTES ---
		
		// --- static ---
		static std::vector< IOOF_LIST * > _object_ ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		IOOF_LIST() ;
		
		// --- DESTRUCTORS ---
		virtual ~IOOF_LIST() = 0 ;
} ;

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
		static std::vector< IOOF_SINGLETON * > _object_ ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		IOOF_SINGLETON() ;
		
		// --- DESTRUCTORS ---
		~IOOF_SINGLETON() ;
} ;

// ===== OOF_LIST =====

/*
 * OOF_LIST is a template class which store any instance of an object of 
 * a specific typename.
 * For example : if you have three instance of CLASS_A and if CLASS_A inherit
 * from OOF_LIST< CLASS_A >, in this case, you can reach any instance with
 * OOF_LIST< CLASS_A >::_list_.
 * The construction of a object OOF_LIST create a SubCommandParser specific
 * for the typename.
 */

template < typename T >
class OOF_LIST
: public IOOF_LIST
{
	public :
	
		// --- GETTERS ---
		inline std::vector< T * > get_list()
			{ return _list_ ; }
	
		// --- ATTRIBUTES ---
		
		// --- static ---
		static std::vector< T * > _list_ ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		OOF_LIST() ;
		
		// --- DESTRUCTORS ---
		~OOF_LIST() ;
		
} ;

// --- static ---

template < typename T > std::vector< T * > OOF_LIST< T >::_list_ = std::vector< T * >() ;

// --- CONSTRUCTORS ---

template < typename T >
OOF_LIST< T >::OOF_LIST
()
{
#ifdef __DEBUG__
	std::cout << "OOF_LIST construction" << std::endl ;
#endif

	_list_.push_back( ( T* ) this ) ;
	SubCommandParser< T >::get_instance() ;
}

// --- DESTRUCTORS ---

template < typename T >
OOF_LIST< T >::~OOF_LIST
()
{
#ifdef __DEBUG__
	std::cout << "OOF_LIST destruction" << std::endl ;
#endif

	typename std::vector< T * >::const_iterator cit = _list_.cbegin() ;
	T * t = ( T* ) this ;
	
	while( *cit != t )
	{
		++cit ;
	}
	
	_list_.erase( cit ) ;
}

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


#endif // OOFOBJECT_HPP
