#include "coord.hpp"

// - static -

const Coord Coord::_origin_ = Coord( 0.0, 0.0, 0.0 ) ;

// --- CONSTRUCTORS ---

Coord::Coord
(
	const double x,
	const double y,
	const double z
)
{
	coord_[ 0 ] = x ;
	coord_[ 1 ] = y ;
	coord_[ 2 ] = z ;
}

Coord::Coord
(
	const double * c
)
: Coord( c[ 0 ], c[ 1 ], c[ 2 ] )
{
}

Coord::Coord
(
	const Coord & c
)
: Coord( c[ 0 ], c[ 1 ], c[ 2 ] )
{
}

// --- DESTRUCTORS ---

Coord::~Coord
()
{
}

// --- OPERATORS ---

Coord &
Coord::operator+=
(
	const Coord & c
)
{
	coord_[ 0 ] += c[ 0 ] ;
	coord_[ 1 ] += c[ 1 ] ;
	coord_[ 2 ] += c[ 2 ] ;
	
	return *this ;
}

Coord &
Coord::operator-=
(
	const Coord & c
)
{
	coord_[ 0 ] -= c[ 0 ] ;
	coord_[ 1 ] -= c[ 1 ] ;
	coord_[ 2 ] -= c[ 2 ] ;
	
	return *this ;
}
Coord &
Coord::operator*=
(
	const double & d
)
{
	coord_[ 0 ] *= d ;
	coord_[ 1 ] *= d ;
	coord_[ 2 ] *= d ;
	
	return *this ;
}
Coord &
Coord::operator/=
(
	const double & d
)
{
	coord_[ 0 ] /= d ;
	coord_[ 1 ] /= d ;
	coord_[ 2 ] /= d ;
	
	return *this ;
}

std::ostream &
operator <<
(
	std::ostream & o,
	const Coord & c
)
{
	return o << "( " << c[ 0 ] << " ; " << c[ 1 ] << " ; " << c[ 2 ] << " )" ;
}

// --- METHODS ---

double
Coord::dot
(
	const Coord & c
)
const
{
	return coord_[ 0 ] * c[ 0 ] + coord_[ 1 ] * c[ 1 ] + coord_[ 2 ] * c[ 2 ] ;
}

Coord
Coord::cross
(
	const Coord & c
)
const
{
	Coord tmp ;
	
	tmp[ 0 ] = coord_[ 1 ] * c[ 2 ] - coord_[ 2 ] * c[ 1 ] ;
	tmp[ 1 ] = coord_[ 2 ] * c[ 0 ] - coord_[ 0 ] * c[ 2 ] ;
	tmp[ 2 ] = coord_[ 0 ] * c[ 1 ] - coord_[ 1 ] * c[ 0 ] ;
		
	return tmp ;
}

double
Coord::norm2
()
const
{
	dot( *this ) ;
} ;
