#ifndef STD_HPP
#define STD_HPP

#include <array>
#include <ctime>
#include <iostream>
#include <vector>

template < typename T >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::vector< T > & list
)
{
	typename std::vector< T >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = list.cbegin() ; cit != list.cend() ; ++cit )
	{
		os << *cit << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

template < typename T, size_t N >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::array< T, N > & list
)
{
	typename std::array< T, N >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = list.cbegin() ; cit != list.cend() ; ++cit )
	{
		os << *cit << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

/*
bool
operator^=
(
	std::vector< bool >::reference ref,
	bool b
)
{
	return bool( ref ) ^ b ;
}
*/

#endif // STD_HPP
