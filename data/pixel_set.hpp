#ifndef PIXEL_SET_HPP
#define PIXEL_SET_HPP

#include "oofobject.hpp"
#include "coord.hpp"

class PixelSet
: public OOFOBJECT< PixelSet >
, public std::vector< Coord< double > >
{
	public :
	
		// --- CONSTRUCTORS ---
		PixelSet() ;
		PixelSet( const PixelSet & ) ;
		
		// --- DESTRUCTORS ---
		~PixelSet() ;
	
		// --- ATTRIBUTES ---
		const unsigned int id_ ;
		
		// - static -
		static unsigned int _index_ ;
		
	protected :
		
	
	private :
		
	
} ;

#endif // PIXEL_SET_HPP
