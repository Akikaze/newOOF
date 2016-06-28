#include "pixel_set.hpp"

// - static -

unsigned int PixelSet::_index_ = 0 ;

// --- CONSTRUCTORS ---

PixelSet::PixelSet
()
: id_( _index_++ )
{
}

PixelSet::PixelSet
(
	const PixelSet & ps
)
: PixelSet()
{
	for( PixelSet::const_iterator cit = ps.cbegin() ;
		 cit != ps.cend() ; ++cit )
	{
		push_back( *cit ) ;
	}
}

// --- DESTRUCTORS ---

PixelSet::~PixelSet
()
{
}
