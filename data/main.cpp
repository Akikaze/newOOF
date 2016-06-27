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
	
	Coord_D c3( c2 ) ;
	Coord< unsigned short > c4 = c2 ;
	
	std::cout << sizeof( c1 ) << " " << c1 << std::endl ;
	std::cout << sizeof( c2 ) << " " << c2 << std::endl ;
	std::cout << sizeof( c3 ) << " " << c3 << std::endl ;
	std::cout << sizeof( c4 ) << " " << c4 << std::endl ;
	
	std::cout << c1.component_multiplication( c2.invert() ) << std::endl ;
	std::cout << c1.component_division( c2 ) << std::endl ;
	
	return 0 ;
}
