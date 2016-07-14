#ifndef STD_HPP
#define STD_HPP

#include <algorithm>
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

// display any array
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
	
	os << *( list.cbegin() ) ;
	for( cit = list.cbegin() + 1 ; cit != list.cend() ; ++cit )
	{
		os << " - " << *cit ;
	}
	os << std::endl ;
	
	os << "---------" ;
	return os ;
}

// display any map
template < typename V >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::map< std::string, V > & map
)
{
	typename std::map< std::string, V >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = map.cbegin() ; cit != map.cend() ; ++cit )
	{
		os << ( *cit ).first << " - " << ( *cit ).second << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

// display any multimap
template < typename V >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::multimap< std::string, V > & multimap
)
{
	typename std::multimap< std::string, V >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = multimap.cbegin() ; cit != multimap.cend() ; ++cit )
	{
		os << ( *cit ).first << " - " << ( *cit ).second << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

// display any vector
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

#endif // STD_HPP
