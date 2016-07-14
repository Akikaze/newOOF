#include "new_object.hpp"

// ===== NewObject =====

// --- ATTRIBUTES ---

std::string NewObject::_typename_ = "NewObject" ;

// --- CONSTRUCTORS ---

NewObject::NewObject
( const std::string & name )
: OOF_OBJECT< NewObject >( name )
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
ObjectStorage< NewObject >::load
(
	const std::string & filename
)
{
	
}

template <>
void
ObjectStorage< NewObject >::load_dependencies
()
{
	
}

template <>
void
ObjectStorage< NewObject >::save
(
	const std::string & folder,
	const IOOF_OBJECT * object
)
const
{
	
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
