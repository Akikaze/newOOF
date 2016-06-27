#include "microstructure.hpp"

// --- CONSTRUCTORS ---

Microstructure::Microstructure
(
	const std::string & name,
	const Coord< int > & size_pixel,
	const Coord< double > & size_real
)
: name_( name )
, size_pixel_( size_pixel )
, size_real_( size_real )
{
	pixel_dimension_ = size_real_ / size_pixel_ ;
}
