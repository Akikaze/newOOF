#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>

template < typename T >
class Coord
{
	public :
		
		// --- CONSTRUCTORS ---
		Coord( const T x = 0,
			   const T y = 0,
			   const T z = 0 ) ;
		Coord( const T * ) ;
		Coord( const Coord & ) ;		
		
		// --- DESTRUCTORS ---
		~Coord() ;
		
		// --- GETTERS / SETTERS ---
		inline T * get_coord()
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
		Coord & operator *= ( const T & ) ;
		Coord & operator /= ( const T & ) ;
		
		// - member and pointer operators -
		inline 		 T * operator * ()
			{ return coord_ ; }
		inline const T * operator * () const
			{ return coord_ ; }
		inline 		 T & operator [] ( int i )
			{ return coord_[ i ] ; }
		inline const T & operator [] ( int i ) const
			{ return coord_[ i ] ; }
			
		// - cast operators -
		template < typename U > operator const Coord< U >() const ;
		
		// --- METHODS ---
		
		Coord component_division( const Coord< double > & ) const ;
		Coord component_multiplication( const Coord & ) const ;
		Coord cross( const Coord & ) const ;
		T dot( const Coord & ) const ;
		Coord< double > invert() const ;
		T norm2() const ; 
		
		// --- ATTRIBUTES ---
		
		// - static -
		static const Coord _origin_ ;
		
	protected :
		
		
	private :
		
		// --- ATTRIBUTES ---
		T coord_[ 3 ] ;
	
} ;

// --- CONSTRUCTORS ---

template < typename T >
Coord< T >::Coord
(
	const T x,
	const T y,
	const T z
)
{
	coord_[ 0 ] = x ;
	coord_[ 1 ] = y ;
	coord_[ 2 ] = z ;
}

template < typename T >
Coord< T >::Coord
(
	const T * t
)
: Coord( t[ 0 ], t[ 1 ], t[ 2 ] )
{
}

template < typename T >
Coord< T >::Coord
(
	const Coord & c
)
// : Coord( c[ 0 ], c[ 1 ], c[ 2 ] )
{
	std::cout << "copy constructor" << std::endl ;
	coord_[ 0 ] = c[ 0 ] ;
	coord_[ 1 ] = c[ 1 ] ;
	coord_[ 2 ] = c[ 2 ] ;
}

// --- DESTRUCTORS ---

template < typename T >
Coord< T >::~Coord
()
{
}

// --- OPERATORS ---

template < typename T >
Coord< T > &
Coord< T >::operator +=
(
	const Coord & c
)
{
	coord_[ 0 ] += c[ 0 ] ;
	coord_[ 1 ] += c[ 1 ] ;
	coord_[ 2 ] += c[ 2 ] ;
	
	return *this ;
}

template < typename T >
Coord< T > &
Coord< T >::operator -=
(
	const Coord & c
)
{
	coord_[ 0 ] -= c[ 0 ] ;
	coord_[ 1 ] -= c[ 1 ] ;
	coord_[ 2 ] -= c[ 2 ] ;
	
	return *this ;
}

template < typename T >
Coord< T > &
Coord< T >::operator *=
(
	const T & t
)
{
	coord_[ 0 ] *= t ;
	coord_[ 1 ] *= t ;
	coord_[ 2 ] *= t ;
	
	return *this ;
}

template < typename T >
Coord< T > &
Coord< T >::operator /=
(
	const T & t
)
{
	coord_[ 0 ] /= t ;
	coord_[ 1 ] /= t ;
	coord_[ 2 ] /= t ;
	
	return *this ;
}

template < typename T >
template < typename U >
Coord< T >::operator const Coord< U >
()
const
{	
	Coord< U > tmp ;
	
	if( sizeof( *this ) != sizeof( Coord< U > ) )
	{
		tmp[ 0 ] = U( coord_[ 0 ] ) ;
		tmp[ 1 ] = U( coord_[ 1 ] ) ;
		tmp[ 2 ] = U( coord_[ 2 ] ) ;
	}
	else
	{
		tmp = *this ;
	}
	
	return tmp ;
}

// - stream operators -
template < typename T >
std::ostream &
operator <<
(
	std::ostream & o,
	const Coord< T > & c
)
{
	return o << "( " << c[ 0 ] << " ; " << c[ 1 ] << " ; " << c[ 2 ] << " )" ;
}

// --- METHODS ---

template < typename T >
Coord< T >
Coord< T >::component_division
(
	const Coord< double > & c
)
const
{
	Coord tmp ;
	
	tmp[ 0 ] = coord_[ 0 ] / c[ 0 ] ;
	tmp[ 1 ] = coord_[ 1 ] / c[ 1 ] ;
	tmp[ 2 ] = coord_[ 2 ] / c[ 2 ] ;
	
	return tmp ;
}

template < typename T >
Coord< T >
Coord< T >::component_multiplication
(
	const Coord & c
)
const
{
	Coord tmp ;
	
	tmp[ 0 ] = coord_[ 0 ] * c[ 0 ] ;
	tmp[ 1 ] = coord_[ 1 ] * c[ 1 ] ;
	tmp[ 2 ] = coord_[ 2 ] * c[ 2 ] ;
	
	return tmp ;
}

template < typename T >
Coord< T >
Coord< T >::cross
(
	const Coord & c
)
const
{
	Coord tmp ;
	
	tmp[ 0 ] = coord_[ 1 ] * c[ 2 ] - coord_[ 2 ] * c[ 1 ] ;
	tmp[ 1 ] = coord_[ 2 ] * c[ 0 ] - coord_[ 0 ] * c[ 2 ] ;
	tmp[ 2 ] = coord_[ 0 ] * c[ 1 ] - coord_[ 1 ] * c[ 0 ] ;
		
	return tmp ;
}

template < typename T >
T
Coord< T >::dot
(
	const Coord & c
)
const
{
	return coord_[ 0 ] * c[ 0 ] + coord_[ 1 ] * c[ 1 ] + coord_[ 2 ] * c[ 2 ] ;
}

template < typename T >
Coord< double >
Coord< T >::invert
()
const
{
	Coord< double > tmp ;
	
	tmp[ 0 ] = 1 / double( coord_[ 0 ] ) ;
	tmp[ 1 ] = 1 / double( coord_[ 1 ] ) ;
	tmp[ 2 ] = 1 / double( coord_[ 2 ] ) ;
	
	return tmp ;
}

template < typename T >
T
Coord< T >::norm2
()
const
{
	dot( *this ) ;
}

// Typedefs
typedef Coord< double > Coord_D ;
typedef Coord< int > Coord_I ;



#endif // COORD_HPP
