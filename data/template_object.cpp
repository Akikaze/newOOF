#include "template_object.hpp"

// ===== NEWOBJECT =====

// --- static ---

std::string NewObject::_typename_ = "NewObject" ;

// --- CONSTRUCTORS ---

NewObject::NewObject
(
	const std::string & name
)
: name_( name )
{
#ifdef __DEBUG__
	std::cout << _typename_ << " construction" << std::endl ;
#endif

	// need to wait after the construction of OOF_OBJ to call give_name()
	give_name( name ) ;
}

// --- DESTRUCTORS ---

NewObject::~NewObject
()
{
#ifdef __DEBUG__
	std::cout << _typename_ << " destruction" << std::endl ;
#endif
}

// --- ObjectStorage ---

template <>
void
ObjectStorage< NewObject >::load
(
	const std::string & filename
)
{
}

template <>
void
ObjectStorage< NewObject >::save
(
	const std::string & folder,
	const IOOF_OBJ * object
)
const
{
}

// --- CommandParser ---

template <>
void
SubCommandParser< NewObject >::parse
(
	const std::string & command
)
const
{
}
