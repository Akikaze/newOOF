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
	
		// --- METHODS ---
		virtual void load( const std::string & filename = "" ) const = 0 ;
		virtual void save( const std::string & folder, const time_t & save_time = 0 ) const = 0 ;
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
		
		// --- METHODS ---
		virtual void load( const std::string & ) const ;
		virtual void save( const std::string &, const time_t & ) const ;
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
	const time_t & save_time
)
const
{
	std::cerr << "No save method for this type of object." << std::endl ;
	
	// need to sort the vector of instance thanks to time_t value
	// save everything on the vector after the time_t value
}

#endif // PROJECT_STORAGE_HPP
