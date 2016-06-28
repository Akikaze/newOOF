#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	Coord< unsigned int > Cui( 2, 3, 4 ) ;
	
	unsigned int pui[ 3 ] ;
	pui[ 0 ] = 8 ;
	pui[ 1 ] = 7 ;
	pui[ 2 ] = 6 ;
	
	BoolVector_3D bv1() ;
	BoolVector_3D bv2( Cui ) ;
	BoolVector_3D bv3( pui ) ;
	
	std::cout << bv1 << std::endl ;
	std::cout << bv2 << std::endl ;
	std::cout << bv3 << std::endl ;
	
	return 0 ;
}
