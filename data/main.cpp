#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	Coord c1( 2, 2, 2 ) ;
	Coord c2( 4, 2, 1 ) ; 
	
	std::cout << c1.norm2() << std::endl ;
	std::cout << c1.dot( c2 ) << std::endl ;
	std::cout << c1.cross( c2 ) << std::endl ;
	
	return 0 ;
}
