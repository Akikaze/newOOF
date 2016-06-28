#include "pixel_selection.hpp"

// --- CONSTRUCTORS ---

PixelSelection::PixelSelection
()
: PixelSet()
{
	
}


PixelSelection::PixelSelection
(
	const PixelSet & ps
)
: PixelSelection()
{
	for( PixelSet::const_iterator cit = ps.cbegin() ; cit != ps.cend() ; ++cit )
	{
		push_back( *cit ) ;
	}
}
