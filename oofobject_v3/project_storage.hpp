#ifndef PROJECT_STORAGE_HPP
#define PROJECT_STORAGE_HPP

// #define __DEBUG__

#include "oofobject.hpp"
#include "std.hpp"

// ===== IObjectStorage =====

class IObjectStorage
{
	friend class ProjectStorage ; // load and save
	
	private :
	
		// --- GETTERS ---
		virtual std::string get_typename() const = 0 ;
	
		// --- METHODS ---
		virtual void load( const std::string & filename = "" ) const = 0 ;
		virtual void save( const std::string & folder, const IOOF_OBJ * ) const = 0 ;
} ;

// ===== ProjectStorage =====

class ProjectStorage
: public OOF_SINGLETON< ProjectStorage >
{
	friend class OOF_SINGLETON< ProjectStorage > ; // constructor
	
	public :
	
		// --- DESTRUCTORS ---
		~ProjectStorage() ;
		
		// --- METHODS ---
		void add_list( IObjectStorage * ) ;
		void display_list() const ;
		void load( const std::string & filename = "" ) ;
		void save( const std::string & project_name = "", bool all = false ) ;
		
	private :
		
		// --- CONSTRUCTORS ---
		ProjectStorage() ;
		
		// --- METHODS ---
		IObjectStorage * find_ObjectStorage( const std::string & ) ;
		
		// --- ATTRIBUTES ---
		std::vector< IObjectStorage * > list_storage_ ;
		std::string project_name_ ;
		time_t last_save_ ;
} ;

// ===== ObjectStorage =====

template < typename T >
class ObjectStorage
: public OOF_SINGLETON< ObjectStorage< T > >
, public IObjectStorage
{
	friend class OOF_SINGLETON< ObjectStorage< T > > ; // constructor
	
	private :
		
		// --- CONSTRUCTORS ---
		ObjectStorage() ;
		
		// --- DESTRUCTORS ---
		~ObjectStorage() ;
		
		// --- GETTERS ---
		std::string get_typename() const ;
		
		// --- METHODS ---
		virtual void load( const std::string & ) const ;
		virtual void save( const std::string &, const IOOF_OBJ * ) const ;
} ;

// --- CONSTRUCTORS ---

template < typename T >
ObjectStorage< T >::ObjectStorage
()
{
#ifdef __DEBUG__
	std::cout << "ObjectStorage construction" << std::endl ;
#endif
	
	ProjectStorage::get_instance()->add_list( this ) ;
}

// --- DESTRUCTORS ---

template < typename T >
ObjectStorage< T >::~ObjectStorage
()
{
#ifdef __DEBUG__
	std::cout << "ObjectStorage destruction" << std::endl ;
#endif
}

// --- GETTERS ---

template < typename T >
std::string
ObjectStorage< T >::get_typename
()
const
{
	return ( OOF_OBJ< T >::_type_instance_ )->get_typename() ;
}

// --- METHODS ---

template < typename T >
void
ObjectStorage< T >::load
(
	const std::string & filename
)
const
{
	std::cerr << "No load method for this type of file : " << filename << std::endl ;
}

template < typename T >
void
ObjectStorage< T >::save
(
	const std::string & folder,
	const IOOF_OBJ * object
)
const
{
	std::cerr << "No save method for this type of object." << std::endl ;
}

#endif // PROJECT_STORAGE_HPP
