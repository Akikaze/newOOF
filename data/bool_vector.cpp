#include "bool_vector.hpp"

// ===== BOOL_VECTOR =====

// --- CONSTRUCTORS ---

BoolVector::BoolVector
(
	const unsigned int & size
)
: std::vector< bool >( size )
{
}

// --- METHODS ---

void
BoolVector::toggle
(
	const unsigned int & i
)
{
	( *this )[ i ] = ( *this )[ i ] ^ true ;
	//( *this )[ i ] ^= true ;
}

// ===== BOOL_VECTOR_3D =====

// --- CONSTRUCTORS ---

BoolVector_3D::BoolVector_3D
(
	const unsigned int & x,
	const unsigned int & y,
	const unsigned int & z
)
{	
	( *this )[ 0 ] = BoolVector( x ) ;
	( *this )[ 1 ] = BoolVector( y ) ;
	( *this )[ 2 ] = BoolVector( z ) ;
}

BoolVector_3D::BoolVector_3D
(
	unsigned int * coord
)
: BoolVector_3D( coord[ 0 ], coord[ 1 ], coord[ 2 ] )
{
}

BoolVector_3D::BoolVector_3D
(
	const Coord< unsigned int > & coord
)
: BoolVector_3D( coord[ 0 ], coord[ 1 ], coord[ 2 ] )
{
}
