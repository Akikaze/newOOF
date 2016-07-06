#include "microstructure.hpp"

// ===== MICROSTRUCTURE =====

// --- CONSTRUCTORS ---

Microstructure::Microstructure
(
	const std::string & name
)
{
#ifdef __DEBUG__
	std::cout << get_typename() << " construction" << std::endl ;
#endif

	// need to wait after the construction of OOF_OBJ to call give_name()
	give_name( name ) ;
}

Microstructure::Microstructure
(
	const std::string & name,
	const Coord< unsigned int > & size_in_pixel,
	const Coord< double > & size_real
)
: Microstructure( name )
{
	size_in_pixel_ = size_in_pixel ;
	size_real_ = size_real ;
	pixel_dimension_ = size_real_.component_division( size_in_pixel_ ) ;
}

// --- DESTRUCTORS ---

Microstructure::~Microstructure
()
{
#ifdef __DEBUG__
	std::cout << get_typename() << " destruction" << std::endl ;
#endif
}

// --- ObjectStorage ---

template <>
void
ObjectStorage< Microstructure >::load
(
	const std::string & filename
)
{
}

template <>
void
ObjectStorage< Microstructure >::save
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
SubCommandParser< Microstructure >::parse
(
	const std::string & command
)
const
{
}
