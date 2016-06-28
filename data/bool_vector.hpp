#ifndef BOOL_VECTOR_HPP
#define BOOL_VECTOR_HPP

#include "coord.hpp"
#include "std.hpp"

/*
 * Theoricaly, the term "array" is associated with static container with
 * a size defined before the compilation. In this case, the size will be
 * known during the call. This is why it is called "vector".
 */

class BoolVector
: public std::vector< bool >
{
	public :
	
		// --- CONSTRUCTORS ---
		BoolVector( const unsigned int & size = 0 ) ;
		
		// --- METHODS ---
		void toggle( const unsigned int & ) ;
	
	protected :
		
	
	private :
		
	
} ;

class BoolVector_3D
: public std::array< BoolVector, 3 >
{
	public :
	
		// --- CONSTRUCTORS ---
		BoolVector_3D( const unsigned int & x = 0,
					   const unsigned int & y = 0,
					   const unsigned int & z = 0 ) ;
		BoolVector_3D( unsigned int * coord ) ;
		BoolVector_3D( const Coord< unsigned int > &  ) ;
	
	protected :
		
	
	private :
		
	
} ;

#endif // BOOL_VECTOR_HPP
