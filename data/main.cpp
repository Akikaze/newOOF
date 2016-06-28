#include "main.hpp"

int
main
(
	int argc,
	char ** argv
)
{	
	PixelSet pst1 ;
	pst1.push_back( Coord_D( 1.0, 1.0, 1.0 ) ) ;
	pst1.push_back( Coord_D( 2.0, 1.0, 0.0 ) ) ;
	std::cout << pst1 << std::endl ;
	
	PixelSet pst2( pst1 ) ;
	std::cout << pst2 << std::endl ;
	
	std::cout << PixelSet::_index_ << std::endl ;
	
	PixelSelection psl1( pst1 ) ;
	std::cout << psl1 << std::endl ;
	psl1.push_back( Coord_D( -1.0, -2.0, -3.0 ) ) ;
	
	PixelSelection psl2( psl1 ) ;
	std::cout << psl2 << std::endl ;
	
	std::cout << PixelSet::_index_ << std::endl ;
	
	return 0 ;
}
