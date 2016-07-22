#include "new_object.hpp"

// ===== NewObject =====

// --- ATTRIBUTES ---

std::string NewObject::_extension_ = ".oof_nObj" ;
std::string NewObject::_typename_ = "NewObject" ;

// --- CONSTRUCTORS ---

NewObject::NewObject
(
	const std::string & name,
	const std::string & code
)
: OOF_OBJECT< NewObject >( name, code )
{
}

// --- DESTRUCTORS ---

NewObject::~NewObject
()
{
}

// --- ObjectStorage ---

template <>
void
ObjectStorage< NewObject >::link_dependency
(
	NewObject * to,
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
}

template <>
void
ObjectStorage< NewObject >::read_data
(
	std::ifstream & file,
	NewObject * object
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
	
	std::getline( file, line ) ; // empty line (before ===== DEPENDENCIES =====)
}

template <>
void
ObjectStorage< NewObject >::write_data
(
	std::ofstream & file,
	const NewObject * object
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
}

// --- SubCommandParser ---

template <>
void
SubCommandParser< NewObject >::parse
(
	const std::string & command
)
const
{
	
}
