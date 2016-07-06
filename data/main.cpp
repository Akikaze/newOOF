#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	/*Coord< unsigned int > Cui( 2, 3, 4 ) ;
	
	unsigned int pui[ 3 ] ;
	pui[ 0 ] = 8 ;
	pui[ 1 ] = 7 ;
	pui[ 2 ] = 6 ;
	
	BoolVector_3D bv1() ;
	BoolVector_3D bv2( Cui ) ;
	BoolVector_3D bv3( pui ) ;
	
	std::cout << bv1 << std::endl ;
	std::cout << bv2 << std::endl ;
	std::cout << bv3 << std::endl ;*/
	
	Microstructure * m1 = new Microstructure() ;
	Microstructure * m2 = new Microstructure( "test" ) ;
	Microstructure * m3 = new Microstructure() ;
	std::cout << m1->get_name() << std::endl ;
	std::cout << m2->get_name() << std::endl ;
	std::cout << m3->get_name() << std::endl ;
	delete m1 ;
	delete m2 ;
	delete m3 ;
	
	// These destructions need to be done at the end of the program
	delete CommandParser::get_instance() ;
	delete ProjectStorage::get_instance() ;
	
	return 0 ;
}
