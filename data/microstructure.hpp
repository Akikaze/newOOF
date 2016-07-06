#ifndef MICROSTRUCTURE_HPP
#define MICROSTRUCTURE_HPP

#include "coord.hpp"
#include "oofobject.hpp"
#include "command_parser.hpp"
#include "project_storage.hpp"

class Microstructure
: public OOF_OBJ< Microstructure >
{
	public :
		// --- CONSTRUCTORS ---
		Microstructure( const std::string & name = "" ) ;
		Microstructure( const std::string &, const Coord< unsigned int > & , const Coord< double > & ) ;
		
		// --- DESTRUCTORS ---
		~Microstructure() ;
		
		// --- GETTERS ---
		virtual inline std::string get_typename() const
			{ return _typename_ ; }
		
		// --- ATTRIBUTES ---
		
		// --- static ---
		static const std::string _typename_ ;
	
	protected :
		
	
	private :
		// --- ATTRIBUTES ---
		Coord< unsigned int > size_in_pixel_ ;
		Coord< double > size_real_ ;
		Coord< double > pixel_dimension_ ;
		
} ;

#endif // MICROSTRUCTURE_HPP
