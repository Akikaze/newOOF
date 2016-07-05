#ifndef PROJECT_STORAGE_HPP
#define PROJECT_STORAGE_HPP

// #define __DEBUG__

#include "oofobject.hpp"
#include "std.hpp"

// ===== IObjectStorage =====

class IObjectStorage
{
	friend class ProjectStorage ;
	
	private :
	
		// --- GETTERS ---
		virtual std::string get_typename() const = 0 ;
	
		// --- METHODS ---
		virtual void load( const std::string & filename = "" ) = 0 ;
		virtual void load_dependencies() = 0 ;
		virtual void save( const std::string & folder, const IOOF_OBJ * ) const = 0 ;
		
		// --- ATTRIBUTES ---
		std::vector< IOOF_OBJ * > dependencies_ ;
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
	friend T ;
	
	private :
		
		// --- CONSTRUCTORS ---
		ObjectStorage() ;
		
		// --- DESTRUCTORS ---
		~ObjectStorage() ;
		
		// --- GETTERS ---
		std::string get_typename() const ;
		
		// --- METHODS ---
		virtual void load( const std::string & ) ;
		virtual void load_dependencies() ;
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
{
	/*
	 * The load method is here to read a file and link attributes of a new
	 * object with value from the file. The file could be divided in three:
	 * 1 - main info (name)
	 * 2 - attributes' value in a specific order
	 * 3 - list of dependencies in a specific order
	 * The load method read the whole file, create the object and store 
	 * objects which need to call load_dependencies in dependencies_
	 */
	
	std::cerr << "No load method for this type of file: " << filename << std::endl ;
}

template < typename T >
void
ObjectStorage< T >::load_dependencies
()
{
	/*
	 * The load_dependencies method is called after the creation of objects.
	 * First of all, it reads the vector which contains every object concerned
	 * by the problem of dependency.
	 * After that, it extracts the dependencies vector for each file which
	 * has attribute's name for key and object's name for value. It links
	 * both of them.
	 */
	
	std::cerr << "No load_dependencies method for this type of object." << std::endl ;
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
	/*
	 * The save method is here to save a specific object in order to be
	 * readable by the load method.
	 * It will save data using the following format:
	 * name_attribute - value_attribute
	 * Of course, if the attribute is a vector, several value will have the same attribute
	 */
	
	std::cerr << "No save method for this type of object." << std::endl ;
}

#endif // PROJECT_STORAGE_HPP
