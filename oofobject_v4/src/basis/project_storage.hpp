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
		
		///
		/// \brief Destructor
		///
		inline virtual ~IObjectStorage() {}
		
		// --- METHODS ---
		
		///
		/// \brief Load a file
		/// \param address Address of the file
		///
		virtual void load( const std::string & address = "" ) = 0 ;
		
		///
		/// \brief Load the dependencies
		///
		virtual void load_dependencies() = 0 ;
		
		///
		/// \brief Save a file
		/// \param folder Directory where it is going to save the file
		/// \param object Object which needs to be saved
		///
		virtual void save( const std::string & folder, const IOOF_OBJECT * object ) = 0 ;
		
		// --- ATTRIBUTES ---
		std::vector< StorageDependency > dependencies_ ; ///< List of dependencies between objects
} ;

// ===== Type =====

class Type
: public std::string
{
	public :
		
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor with parameter
		/// \param extension Extension of the type
		/// \param name Name of the type
		///
		Type( const std::string & extension, const std::string & type) ;
		
		// --- ATTRIBUTES ---
		std::string name_ ; ///< Name of the type
} ;

// ===== ProjectStorage =====

class ProjectStorage
: public OOF_SINGLETON< ProjectStorage >
{
	friend class OOF_SINGLETON< ProjectStorage > ; // constructor
	friend class Core ; // destructor
	
	public :
	
		// --- GETTER ---
		
		///
		/// \brief Get the code of the project
		/// \return The code in a string
		///
		inline std::string get_project_code()
			{ return project_code_ ; }
		
		///
		/// \brief Get the name of the project
		/// \return The name in a string
		///
		inline std::string get_project_name()
			{ return project_name_ ; }
		
		///
		/// \brief Get the path of the project
		/// \return The path in a string
		///
		inline std::string get_project_path()
			{ return project_path_ ; }
	
		// --- METHODS ---
		
		///
		/// \brief Add a ObjectStorage in the map
		/// \param type Specialization of ObjectStorage
		/// \param project_storage Pointer to the ObjectStorage
		///
		void add_map( const Type & type, IObjectStorage * project_storage ) ;
		
		///
		/// \brief Display the map of ObjectStorage
		///
		void display_map() const ;
		
		///
		/// \brief Load a file
		/// \param address Address of the file
		///
		void load( const std::string & address = "" ) ;
		
		///
		/// \brief Load several files
		/// \param files Vector which contains every files
		///
		void load_files( const std::vector< std::string > & files ) ;
		
		///
		/// \brief Save a project
		/// \param project_name Name of the project
		/// \param all Save every objects, even if they were not modified since the last save
		///
		void save( const std::string & project_name = "", bool all = false ) ;
		
		///
		/// \brief Save an object
		/// \param object Pointer to the object
		///
		void save_object( const IOOF_OBJECT * object ) ;
		
		///
		/// \brief Save the project
		///
		void save_project( std::ofstream & ) const ;
	
	protected :
	
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		ProjectStorage() ;
		
		// --- DESTRUCTORS ---
		
		///
		/// \brief Destructor
		///
		~ProjectStorage() ;
		
		// --- METHODS ---
		
		///
		/// \brief Find the extension thanks to the typename
		/// \param type Typename
		/// \return Extension of the type in a string
		///
		std::string find_extension( const std::string & type ) const ;
		
		///
		/// \brief Find the typename thanks to the extension
		/// \param extension Extension
		/// \return Type linked to the extension in a string
		///
		std::string find_type( const std::string & extension ) const ;
		
		///
		/// \brief Load all dependencies stored during the construction
		///
		void load_all_dependencies() const ;
		
		///
		/// \brief Load a file
		/// \param address Address of the file
		/// \param type Type of the file
		///
		void load_file( const std::string & address, const std::string & type = "" ) ;
		
		///
		/// \brief Load files from a project file
		/// \param files Map which contains address and type of each files in a project
		///
		void load_files( const std::map< std::string, std::string > & files ) ;
		
		///
		/// \brief Load a project
		/// \param address Address of the project file
		///
		void load_project( const std::string & address ) ;
		
		///
		/// \brief Read files stored in a project files
		/// \param file Stream which point the position of files in the project file
		/// \return Map which contains address and type of each files in the project
		///
		std::map< std::string, std::string > read_project_files( std::ifstream & file ) ;
		
		///
		/// \brief Read the project header
		/// \param file Stream which point the header of the project file
		/// \return true if there is no object before the load of this project
		///
		bool read_project_info( std::ifstream & file ) ;
	
		// --- ATTRIBUTES ---
		InstanceManager * im_ ; ///< Pointer to the InstanceManager
		LogDevice * ld_ ; ///< Pointer to the LogDevice
		
		std::map< std::string, IObjectStorage * > map_storage_ ; ///< Map of ObjectStorage
		std::vector< Type > types_ ; ///< List of type
		
		std::string project_code_ ; ///< Code of the project
		std::string project_name_ ; ///< Name of the project
		std::string project_path_ ; ///< Path of the project
		
		time_t last_save_ ; ///< Time of the last save
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
		
		///
		/// \brief Constructor
		///
		ObjectStorage() ;
		
		// --- DESTRUCTORS ---
		
		///
		/// \brief Destructor
		///
		~ObjectStorage() ;
		
		// --- METHODS ---
		
		///
		/// \brief Create a dependency 
		/// \param where Name of the variable
		/// \param from Pointer to the target of the dependency
		///
		void create_dependency( const std::string & where, T * from ) ;
		
		///
		/// \brief Find a dependency
		/// \param objects List of all object in the session
		/// \param code Code of the dependency's target
		///
		IOOF_OBJECT * find_dependency( const std::vector< IOOF_OBJECT * > & objects, const std::string & code ) const ;
		
		///
		/// \brief Load a file
		/// \param address Address of the file
		///
		void load( const std::string & address ) ;
		
		///
		/// \brief Load each dependency
		///
		void load_dependencies() ;
		
		///
		/// \brief Read the dependencies of a object
		/// \param file Stream which point the location of the dependencies
		/// \param object Object which need the dependencies
		///
		void read_dependencies( std::ifstream & file, T * object ) ;
		
		///
		/// \brief Save an object
		/// \param folder Directory where the file is going to be saved
		/// \param object Pointer to the object
		///
		void save( const std::string & folder, const IOOF_OBJECT * object ) ;
		
		///
		/// \brief Write the dependencies in a file
		/// \param file Stream which point the location where writing the dependencies
		///
		void write_dependencies( std::ofstream & file ) ;
		
		// could work without override
		
		///
		/// \brief Read the header of the file
		/// \param file Stream which point the header of the file
		/// \return Pointer to a new object created thanks to the info
		///
		virtual T * read_info( std::ifstream & file ) const ;
		
		///
		/// \brief Write header of the file
		/// \param file Stream which point the location where writing info
		/// \param object Pointer ot the object
		///
		virtual void write_info( std::ofstream & file, const T * object ) const ;
		
		// defined by user
		
		///
		/// \brief Recreate the dependency
		/// \param to Pointer on the object which will receive the dependency
		/// \param where Name of the variable
		/// \param from Pointer to the dependency's target
		///
		virtual void link_dependency( T * to, std::string where, IOOF_OBJECT * from ) const ;
		
		///
		/// \brief Read data of a file
		/// \param file Stream which point the position of data
		/// \param object Pointer on the object
		///
		virtual void read_data( std::ifstream & file, T * object ) const ;
		
		///
		/// \brief Write attribute of the object
		/// \param file Stream which point the position where writing the data
		/// \param object Pointer on the object
		///
		virtual void write_data( std::ofstream & file, const T * object ) ;
		
		// --- ATTRIBUTES ---
		
		InstanceManager * im_ ; ///< Pointer on the InstanceManager
		LogDevice * ld_ ; ///< Pointer on the LogDevice
} ;

// --- CONSTRUCTORS ---

template < class T >
ObjectStorage< T >::ObjectStorage
()
{
	ProjectStorage::get_instance()->add_map( Type( T::_extension_, T::_typename_ ), this ) ;
	
	// get pointers to InstanceManager and LogDevice
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
	// create a dependency without using to because it's useless
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
	
	// find the object with the right code
	cit = std::find_if( objects.cbegin(), objects.cend(),
						[&code](IOOF_OBJECT * o) -> bool
													{
														return o->get_code() == code ;
													} ) ;
	
	IOOF_OBJECT * dependency = nullptr ;
	
	if( cit == objects.cend() )
	{
		// if the object doesn't exist		
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
		/*
		 * maybe a mistake, if the object is already loaded, we are going to
		 * have two objects with the same code but with different name.
		 * 
		 * Maybe we must forbid the possibility to have two objects with
		 * the same code loaded.
		 */
		
		// read header of the file with name and code
		T * object = read_info( file ) ;
		// read attributes of the object
		read_data( file, object ) ;
		//read dependencies, find them and link them
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
	// if there are dependencies
	if( !( dependencies_.empty() ) )
	{
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
		// create the dependency thanks to the line
		pos = line.find( ' ' ) ;
		
		StorageDependency sd ;
		sd.to = object ;
		sd.where = line.substr( 0, pos ) ;
		sd.from = line.substr( pos + 1 ) ;
		
		// save the dependency
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
		// save header (name, code, ...)
		write_info( file, object ) ;
		// save every attributes which are not pointers
		write_data( file, object ) ;
		// save pointers into dependencies
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
