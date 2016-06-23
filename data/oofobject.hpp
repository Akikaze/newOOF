#ifndef OOFOBJECT_HPP
#define OOFOBJECT_HPP

#include <vector>

template < typename T >
class OOFOBJECT
{
	public :
		
		// --- CONSTRUCTORS ---
		OOFOBJECT() ;
		
		// --- DESTRUCTORS ---
		~OOFOBJECT() ;
		
		// --- ATTRIBUTES ---
		
		// --- static ---
		static std::vector< T * > _list_ ;
	
} ;

template < typename T > std::vector< T * > OOFOBJECT< T >::_list_ = std::vector< T * >() ;

template < typename T >
OOFOBJECT< T >::OOFOBJECT
()
{
	_list_.push_back( ( T* ) this ) ;
}

template < typename T >
OOFOBJECT< T >::~OOFOBJECT
()
{
	typename std::vector< T * >::const_iterator cit = _list_.cbegin() ;
	T * t = ( T* ) this ;
	
	while( *cit != t )
	{
		++cit ;
	}
	
	_list_.erase( cit ) ;
}

#endif // OOFOBJECT_HPP
