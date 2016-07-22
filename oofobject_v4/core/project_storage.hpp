#ifndef PROJECT_STORAGE_HPP
#define PROJECT_STORAGE_HPP

#include "config.hpp"
#include "oof_singleton.hpp"
#include "ioof_object.hpp"

// ===== StorageDependency =====

struct StorageDependency
{
	IOOF_OBJECT * to ; // receiver of the dependency
	std::string where ; // variable for the dependency
	std::string from ; // target for the dependency
} ;

std::ostream & operator<<( std::ostream &, const StorageDependency & ) ;

// ===== IObjectStorage =====

class IObjectStorage
{
	friend class ProjectStorage ;
	
	protected :
		
		// --- DESTRUCTORS ---
		inline virtual ~IObjectStorage() {}
		
		// --- METHODS ---
		virtual void load( const std::string & adress = "" ) = 0 ;
		virtual void load_dependencies() = 0 ;
		virtual void save( const std::string &, const IOOF_OBJECT * ) = 0 ;
		
		// --- ATTRIBUTES ---
		std::vector< StorageDependency > dependencies_ ;
} ;

// ===== Type =====

class Type
: public std::string
{
	public :
		
		// --- CONSTRUCTORS ---
		Type( const std::string &, const std::string & );
		
		// --- ATTRIBUTES ---
		std::string name_ ;
} ;

// ===== ProjectStorage =====

class ProjectStorage
: public OOF_SINGLETON< ProjectStorage >
{
	friend class OOF_SINGLETON< ProjectStorage > ; // constructor
	friend class Core ; // destructor
	
	public :
	
		// --- GETTER ---
		inline std::string get_project_code()
			{ return project_code_ ; }
		inline std::string get_project_name()
			{ return project_name_ ; }
		inline std::string get_project_path()
			{ return project_path_ ; }
	
		// --- METHODS ---
		void add_map( const Type &, IObjectStorage * ) ;
		void display_map() const ;
		void load( const std::string & address = "" ) ;
		void load_files( const std::vector< std::string > & ) ;
		
		void save( const std::string & project_name = "", bool all = false ) ;
		void save_project( std::ofstream & ) const ;
	
	protected :
	
		// --- CONSTRUCTORS ---
		ProjectStorage() ;
		
		// --- DESTRUCTORS ---
		~ProjectStorage() ;
		
		// --- METHODS ---
		std::string find_extension( const std::string & ) const ;
		std::string find_type( const std::string & ) const ;
		void load_all_dependencies() const ;
		void load_file( const std::string & path = "", const std::string & type = "" ) ;
		void load_files( const std::map< std::string, std::string > & ) ;
		void load_project( const std::string & ) ;
		std::map< std::string, std::string > read_project_files( std::ifstream & ) ;
		bool read_project_info( std::ifstream & ) ;
	
		// --- ATTRIBUTES ---
		InstanceManager * im_ ;
		LogDevice * ld_ ;
		
		std::map< std::string, IObjectStorage * > map_storage_ ;
		std::vector< Type > types_ ;
		
		std::string project_code_ ;
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
	
	protected :
	
		// --- CONSTRUCTORS ---
		ObjectStorage() ;
		
		// --- DESTRUCTORS ---
		~ObjectStorage() ;
		
		// --- METHODS ---
		void create_dependency( const std::string &, T * ) ;
		IOOF_OBJECT * find_dependency( const std::vector< IOOF_OBJECT * > &, const std::string & ) const ;
		void load( const std::string & ) ;
		void load_dependencies() ;
		void read_dependencies( std::ifstream &, T * ) ;
		void save( const std::string &, const IOOF_OBJECT * ) ;
		void write_dependencies( std::ofstream & ) ;
		
		// could work without override
		virtual T * read_info( std::ifstream & ) const ;
		virtual void write_info( std::ofstream &, const T * ) const ;
		
		// defined by user
		virtual void link_dependency( T *, std::string, IOOF_OBJECT * ) const ;
		virtual void read_data( std::ifstream &, T * ) const ;
		virtual void write_data( std::ofstream &, const T * ) ;
		
		// --- ATTRIBUTES ---
		InstanceManager * im_ ;
		LogDevice * ld_ ;
} ;

// --- CONSTRUCTORS ---

template < class T >
ObjectStorage< T >::ObjectStorage
()
{
	ProjectStorage::get_instance()->add_map( Type( T::_extension_, T::_typename_ ), this ) ;
	
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
ObjectStorage< T >::create_dependency
(
	const std::string & where,
	T * from
)
{
	StorageDependency sd ;
	sd.to = nullptr ;
	sd.where = where ;
	sd.from = from->get_code() ;
	
	dependencies_.push_back( sd ) ;
}

template < class T >
IOOF_OBJECT *
ObjectStorage< T >::find_dependency
(
	const std::vector< IOOF_OBJECT * > & objects,
	const std::string & code
)
const
{
	std::vector< IOOF_OBJECT * >::const_iterator cit ;
	cit = std::find_if( objects.cbegin(), objects.cend(),
						[&code](IOOF_OBJECT * o) -> bool
													{
														return o->get_code() == code ;
													} ) ;
	
	IOOF_OBJECT * dependency = nullptr ;
	if( cit == objects.cend() )
	{
		dependency = nullptr ;
		
		ld_->log( "Unable to make the dependency", LOG_FLAG::ERROR ) ;
		ld_->log( "The object coded " + code + " was not found in the list of object", LOG_FLAG::REPORT ) ;
	}
	else
	{
		dependency = ( *cit ) ;
	}
	
	return dependency ;
}

template < class T >
void
ObjectStorage< T >::link_dependency
(
	T * to,
	std::string where,
	IOOF_OBJECT * from
)
const
{
	/*
	 * This method is here to put the pointer 'from' in the variable 'where'
	 * of the object 'to'. This method needs to be implemented for each object
	 * because the behavior depends of 'where'.
	 */
	
	ld_->log( "No link_dependency method for this type of object: " + T::_typename_, LOG_FLAG::ERROR ) ;
	ld_->log( "Impossible to create the dependency", LOG_FLAG::REPORT ) ;
}
	

template < class T >
void
ObjectStorage< T >::load
(
	const std::string & address
)
{
	std::ifstream file( address.c_str(), std::ios::in ) ;
	
	if( file )
	{
		T * object = read_info( file ) ;
		read_data( file, object ) ;
		read_dependencies( file, object ) ;
	}
	else
	{
		ld_->log( "Impossible to load a file", LOG_FLAG::ERROR ) ;
		ld_->log( "Impossible to open " + address + " in read mode", LOG_FLAG::REPORT ) ;
	}
}

template < class T >
void
ObjectStorage< T >::load_dependencies
()
{	
	if( !( dependencies_.empty() ) )
	{
		std::cout << dependencies_ << std::endl ;
		
		std::vector< StorageDependency >::const_iterator cit ;
		cit = dependencies_.cbegin() ;
		
		std::vector< IOOF_OBJECT * > objects = im_->extract() ;
		
		while( cit != dependencies_.cend() )
		{
			// find target
			IOOF_OBJECT * target = find_dependency( objects, ( *cit ).from ) ;
			
			// link the dependency
			link_dependency( static_cast< T *>( ( *cit ).to ), ( *cit ).where, target ) ;
			
			dependencies_.erase( cit ) ;
		}
	}
}

template < class T >
void
ObjectStorage< T >::read_data
(
	std::ifstream & file,
	T * object
)
const
{
	std::string line ;
	
	std::getline( file, line ) ; // ===== DATA =====
	std::getline( file, line ) ; // empty line
	
	/*
	 * This method is here to read data and link them to the right variable.
	 * The main idea is to store in the file a line for each variable :
	 * variable value_in_the_variable
	 * 
	 * It is also possible to put several value for a variable in order to
	 * describe vector's content.
	 * 
	 * Remember that you are going to implement save_data too, so if you don't
	 * need variable because you know perfectly the variable order, you can
	 * just put values without variables.
	 * 
	 * You need to read the file until the last empty line before 
	 * ===== DEPENDENCIES =====
	 */
	
	std::getline( file, line ) ; // empty line
	
	ld_->log( "No read_data method for this type of object: " + T::_typename_, LOG_FLAG::ERROR ) ;
	ld_->log( "Impossible to fill the object", LOG_FLAG::REPORT ) ;
}

template < class T >
T *
ObjectStorage< T >::read_info
(
	std::ifstream & file
)
const
{
	/*
	 * This method is here to read header of the file and create an object
	 * thanks to the pieces of informations you find here.
	 * 
	 * If you would add more information in the header, you need to reimplement
	 * this method and add your new info.
	 */
	
	size_t pos = 0 ;
	std::string line ;
	
	std::getline( file, line ) ; // ===== INFO =====
	std::getline( file, line ) ; // empty line
	
	std::getline( file, line ) ; // code - __________.???
	std::string code = line.substr( 7, line.length() - 7 ) ;
	
	std:;getline( file, line ) ; // name - ???
	std::string name = line.substr( 7, line.length() - 7 ) ;
	
	std::getline( file, line ) ; // empty line
	
	T * object = new T( name, code ) ;
	return object ;
}

template < class T >
void
ObjectStorage< T >::read_dependencies
(
	std::ifstream & file,
	T * object
)
{
	size_t pos ;
	std::string line ;
	
	std::getline( file, line ) ; // ===== DEPENDENCIES =====
	std::getline( file, line ) ; // empty line
	
	while( std::getline( file, line ) ) // variable code_of_the_object
	{
		pos = line.find( ' ' ) ;
		
		StorageDependency sd ;
		sd.to = object ;
		sd.where = line.substr( 0, pos ) ;
		sd.from = line.substr( pos + 1 ) ;
		
		dependencies_.push_back( sd ) ;
	}
}

template < class T >
void
ObjectStorage< T >::save
(
	const std::string & folder,
	const IOOF_OBJECT * iobject
)
{
	const T * object = static_cast< const T * >( iobject ) ;
	
	std::string filename = folder + object->get_code() + T::_extension_ ;
	std::ofstream file( filename.c_str(), std::ios::out | std::ios::trunc ) ;
	
	if( file )
	{
		write_info( file, object ) ;
		write_data( file, object ) ;
		write_dependencies( file ) ;
	}
	else
	{
		ld_->log( "Impossible to save the object", LOG_FLAG::ERROR ) ;
		ld_->log( "Impossible to open " + filename + " in write mode", LOG_FLAG::REPORT ) ;
	}
}

template < class T >
void
ObjectStorage< T >::write_data
(
	std::ofstream & file,
	const T * object
)
{
	file << "===== DATA =====" << std::endl ;
	file << std::endl ;
	
	/*
	 * The save method is here to save a specific object in order to be
	 * readable by the load method.
	 * It will save data using the following format:
	 * name_attribute - value_attribute
	 * Of course, if the attribute is a vector, several value will have the same attribute
	 * 
	 * Be careful, if you store pointer on other type of IOOF_OBJECT *, you need
	 * to use create_dependency with the name of the variable and the code
	 * of the object instead of storing the pointer or anything else.
	 */
	
	file << std::endl ;
	ld_->log( "No write_data method for this type of object", LOG_FLAG::REPORT ) ;
}

template < class T >
void
ObjectStorage< T >::write_dependencies
(
	std::ofstream & file
)
{
	file << "===== DEPENDENCIES =====" ;
	file << std::endl ;
	
	while( !( dependencies_.empty() ) ) // variable code_of_the_object
	{
		file << ( *( dependencies_.begin() ) ).where << " " ; // variable
		file << ( *( dependencies_.begin() ) ).from << std::endl ; // code of the object
		
		dependencies_.erase( dependencies_.begin() ) ;
	}
}

template < class T >
void
ObjectStorage< T >::write_info
(
	std::ofstream & file,
	const T * object
)
const
{
	file << "===== INFO =====" << std::endl ;
	file << std::endl ;
	
	file << "code - " << object->get_code() << std::endl ;
	file << "name - " << object->get_name() << std::endl ;
	
	file << std::endl ;
}

#endif // PROJECT_STORAGE_HPP
