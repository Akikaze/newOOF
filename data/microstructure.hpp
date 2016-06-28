#ifndef MICROSTRUCTURE_HPP
#define MICROSTRUCTURE_HPP

#include "oofobject.hpp"

class Microstructure
: public OOFOBJECT< Microstructure >
{
	public :
		Microstructure( std::string &, const Coord< unsigned int > , const Coord< unsigned double > ) ;
	
	protected :
		
	
	private :
		std::string name_ ;
		Coord< unsigned int > size_pixel_ ;
		Coord< unsigned double > size_real_ ;
		Coord< unsigned double > pixel_dimension_ ;		
	
} ;

#endif // MICROSTRUCTURE_HPP
