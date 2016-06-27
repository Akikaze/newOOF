#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>

class Coord
{
	public :
		
		// --- CONSTRUCTORS ---
		Coord( const double x = 0.0,
			   const double y = 0.0,
			   const double z = 0.0 ) ;
		Coord( const double * ) ;
		Coord( const Coord & ) ;		
		
		// --- DESTRUCTORS ---
		~Coord() ;
		
		// --- GETTERS / SETTERS ---
		inline double * get_coord()
			{ return coord_ ; }
		
		// --- OPERATORS ---
		
		// - arithmetic operators -
		inline Coord operator + ( const Coord & c ) const
			{ return Coord( coord_[ 0 ] + c[ 0 ], coord_[ 1 ] + c[ 1 ], coord_[ 2 ] + c[ 2 ] ) ; }
		
		inline Coord operator - ( const Coord & c ) const
			{ return Coord( coord_[ 0 ] - c[ 0 ], coord_[ 1 ] - c[ 1 ], coord_[ 2 ] - c[ 2 ] ) ; }
		
		inline Coord operator * ( const double & d ) const
			{ return Coord( coord_[ 0 ] * d, coord_[ 1 ] * d, coord_[ 2 ] * d ) ; }
		
		inline Coord operator / ( const double & d) const
			{ return Coord( coord_[ 0 ] / d, coord_[ 1 ] / d, coord_[ 2 ] / d ) ; }
		
		inline Coord operator - () const
			{ return ( *this ) * -1.0 ; }
			
		// - comparison operators -
		inline bool operator < ( const Coord & c ) const
			{ return ( coord_[ 0 ] < c[ 0 ] || coord_[ 1 ] < c[ 1 ] || coord_[ 2 ] < c[ 2 ] ) ; }
		
		inline bool operator > ( const Coord & c ) const
			{ return ( coord_[ 0 ] > c[ 0 ] || coord_[ 1 ] > c[ 1 ] || coord_[ 2 ] > c[ 2 ] ) ; }
			
		inline bool operator == ( const Coord & c ) const
			{ return ( coord_[ 0 ] == c[ 0 ] && coord_[ 1 ] == c[ 1 ] && coord_[ 2 ] == c[ 2 ] ) ; }
			
		inline bool operator != ( const Coord & c ) const
			{ return !( this->operator == ( c ) ) ; }
		
		inline bool operator <= ( const Coord & c ) const
			{ return !( this->operator > ( c ) ) ; }
		
		inline bool operator >= ( const Coord & c ) const
			{ return !( this->operator < ( c ) ) ; }
		
		// - compound assignment operators -
		Coord & operator += ( const Coord & ) ;
		Coord & operator -= ( const Coord & ) ;
		Coord & operator *= ( const double & ) ;
		Coord & operator /= ( const double & ) ;
		
		// - member and pointer operators -
		inline 		 double * operator * ()
			{ return coord_ ; }
		inline const double * operator * () const
			{ return coord_ ; }
		inline 		 double & operator [] ( int i )
			{ return coord_[ i ] ; }
		inline const double & operator [] ( int i ) const
			{ return coord_[ i ] ; }
		
		// - stream operators -
		friend std::ostream & operator << ( std::ostream &, const Coord & ) ;
		
		// --- METHODS ---
		
		double dot( const Coord & ) const ;
		Coord cross( const Coord & ) const ;
		double norm2() const ; 
		
		// --- ATTRIBUTES ---
		
		// - static -
		static const Coord _origin_ ;
		
	protected :
		
		
	private :
		
		// --- ATTRIBUTES ---
		double coord_[ 3 ] ;
		
	
} ;

#endif // COORD_HPP
