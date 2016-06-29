#ifndef OOFOBJECT_HPP
#define OOFOBJECT_HPP

#include <iostream>
#include <vector>

// --- prior definition ---

template < typename T > class SubCommandParser ;

// ===== OOF_LIST =====

template < typename T >
class OOF_LIST
{
	public :
		
		// --- CONSTRUCTORS ---
		OOF_LIST() ;
		
		// --- DESTRUCTORS ---
		~OOF_LIST() ;
		
		// --- ATTRIBUTES ---
		
		// --- static ---
		static std::vector< T * > _list_ ;
	
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

template < typename T >
class OOF_SINGLETON
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
