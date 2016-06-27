#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	Coord_D c1( 3, 3, 3 ) ;
	Coord_I c2( 2, 2, 2 ) ;
	
	std::cout << c1.component_multiplication( c2.invert() ) << std::endl ;
	std::cout << c1.component_division( c2 ) << std::endl ;
	
	return 0 ;
}
