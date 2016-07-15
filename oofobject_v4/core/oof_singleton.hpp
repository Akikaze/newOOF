#ifndef OOF_SINGLETON_HPP
#define OOF_SINGLETON_HPP

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

#endif // OOF_SINGLETON_HPP
