#ifndef PROJECT_STORAGE_HPP
#define PROJECT_STORAGE_HPP

#include "oof_singleton.hpp"
#include "ioof_object.hpp"

// ===== StorageDependency =====

struct StorageDependency
{
	std::string to ; // which object need the dependency
	std::string where ; // which variable is going to use the dependency
	std::string from ; // which object is the dependency
} ;

// ===== IObjectStorage =====

class IObjectStorage
{
	friend class ProjectStorage ;
	
	protected :
	
		// --- DESTRUCTORS ---
		virtual ~IObjectStorage() ;
	
		// --- METHODS ---
		virtual void load( const std::string & filename = "" ) = 0 ;
		virtual void load_dependencies() = 0 ;
		virtual void save( const std::string & folder, const IOOF_OBJECT * ) const = 0 ;
		
		// --- ATTRIBUTES ---
		std::vector< StorageDependency > dependencies_ ;
} ;

// ===== ProjectStorage =====

class ProjectStorage
: public OOF_SINGLETON< ProjectStorage >
{
	friend class OOF_SINGLETON< ProjectStorage > ; // constructor
	friend class Core ; // destructor
	
	public :
	
		// --- GETTERS ---
		inline std::string get_project_name()
			{ return project_name_ ; }
	
		// --- METHODS ---
		void add_list( const std::string &, IObjectStorage * ) ;
		void display_list() const ;
		void load( const std::string & filename = "" ) ;
		void save( const std::string & project_name = "", bool all = false ) ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		ProjectStorage() ;
		
		// --- DESTRUCTORS ---
		~ProjectStorage() ;
		
		// --- ATTRIBUTES ---
		InstanceManager * im_ ;
		LogDevice * ld_ ;
		std::map< std::string, IObjectStorage * > map_storage_ ;
		std::string project_name_ ;
		std::string project_path_ ;
		time_t last_save_ ;
} ;

// ===== ObjectStorage =====

template < class T >
class ObjectStorage
: public OOF_SINGLETON< ObjectStorage< T > >
, public IObjectStorage
{
	friend class OOF_SINGLETON< ObjectStorage< T > > ; // constructor
	friend T ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		ObjectStorage() ;
		
		// --- DESTRUCTORS ---
		~ObjectStorage() ;
		
		// --- METHODS ---
		virtual void load( const std::string & ) ;
		virtual void load_dependencies() ;
		virtual void save( const std::string &, const IOOF_OBJECT * ) const ;
		
		// --- ATTRIBUTES ---
		InstanceManager * im_ ;
		LogDevice * ld_ ;
} ;

// --- CONSTRUCTORS ---

template < class T >
ObjectStorage< T >::ObjectStorage
()
{
	ProjectStorage::get_instance()->add_list( T::_typename_, this ) ;
	
	im_ = InstanceManager::get_instance() ;
	ld_ = LogDevice::get_instance() ;
}

// --- DESTRUCTORS ---

template < class T >
ObjectStorage< T >::~ObjectStorage
()
{
}

// --- METHODS ---

template < class T >
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
	
	ld_->log( "No load method for this type of file: " + filename, LOG_FLAG::REPORT ) ;
}

template < class T >
void
ObjectStorage< T >::load_dependencies
()
{
	/*
	 * The load_dependencies method is called after the creation of objects.
	 * First of all, it reads the vector which contains every object concerned
	 * by the problem of dependency linked with dependency name and variable.
	 * Just need to put each dependency in the right variable.
	 */
	
	ld_->log( "No load_dependencies method for this type of object.", LOG_FLAG::REPORT ) ;
}

template < class T >
void
ObjectStorage< T >::save
(
	const std::string & folder,
	const IOOF_OBJECT * object
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
	
	ld_->log( "No save method for this type of object.", LOG_FLAG::REPORT ) ;
}

#endif // PROJECT_STORAGE_HPP
