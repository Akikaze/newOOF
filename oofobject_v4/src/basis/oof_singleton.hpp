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
		
		///
		/// \brief Get the instance of the singleton
		/// \return Instance of the singleton
		///
		static T * get_instance() ;
		
		// --- METHODS ---
		
		///
		/// \brief Construct the unique instance
		///
		static void construct() ;
		
		///
		/// \brief Destroy the unique instance
		///
		static void destroy() ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		OOF_SINGLETON() ;
		
		///
		/// \brief Copy constructor
		/// \param o_s Singleton
		///
		OOF_SINGLETON( const OOF_SINGLETON & o_s ) ;
		
		// --- DESTRUCTORS ---
		
		///
		/// \brief Destructor
		///
		virtual ~OOF_SINGLETON() ;
		
		// --- ATTRIBUTES ---
		static T * _instance_ ; ///< Instance of the singleton
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
	// create the object and return the instance
	construct() ;
	return _instance_ ;
}

// --- METHODS ---

template < class T >
void
OOF_SINGLETON< T >::construct
()
{
	// create the object
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
	// destroy the object and the instance
	if( _instance_ != nullptr )
	{
		delete _instance_ ;
		_instance_ = nullptr ;
	}
}

#endif // OOF_SINGLETON_HPP
