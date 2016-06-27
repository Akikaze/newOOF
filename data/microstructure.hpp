#ifndef MICROSTRUCTURE_HPP
#define MICROSTRUCTURE_HPP

#include "oofobject.hpp"

class Microstructure
: public OOFOBJECT< Microstructure >
{
	public :
		Microstructure( std::string &, const Coord< int > , const Coord< double > ) ;
	
	protected :
		
	
	private :
		std::string name_ ;
		Coord< int > size_pixel_ ;
		Coord< double > size_real_ ;
		Coord< double > pixel_dimension_ ;		
	
} ;

#endif // MICROSTRUCTURE_HPP
