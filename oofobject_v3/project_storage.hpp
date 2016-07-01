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
		virtual void load() const = 0 ;
		virtual void save() const = 0 ;
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
		void load() const ;
		void save() const ;
		
	private :
		
		// --- CONSTRUCTORS ---
		ProjectStorage() ;
		
		// --- ATTRIBUTES ---
		std::vector< IObjectStorage * > list_storage_ ;
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
		virtual void load() const ;
		virtual void save() const ;
} ;

// --- CONSTRUCTORS ---

template < typename T >
ObjectStorage< T >::ObjectStorage
()
{
#ifndef __DEBUG__
	std::cout << "ObjectStorage construction" << std::endl ;
#endif
	
	ProjectStorage::get_instance()->add_list( this ) ;
}

// --- DESTRUCTORS ---

template < typename T >
ObjectStorage< T >::~ObjectStorage
()
{
#ifndef __DEBUG__
	std::cout << "ObjectStorage destruction" << std::endl ;
#endif
}

// --- METHODS ---

template < typename T >
void
ObjectStorage< T >::load
()
const
{
	std::cerr << "No load method for this type of object." << std::endl ;
}

template < typename T >
void
ObjectStorage< T >::save
()
const
{
	std::cerr << "No save method for this type of object." << std::endl ;
}

#endif // PROJECT_STORAGE_HPP
