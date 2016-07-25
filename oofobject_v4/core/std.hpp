#ifndef STD_HPP
#define STD_HPP

#include <algorithm>
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

///
/// \brief Display time in the right format
/// \param date time_t structure which contains the date
/// \return String which contains the date in the right format
///
std::string display( time_t date ) ;

///
/// \brief Display an array
/// \param os Stream for the display
/// \param array Array
/// \return Stream with the display in it
///
template < typename T, size_t N >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::array< T, N > & array
)
{
	typename std::array< T, N >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	os << *( array.cbegin() ) ;
	for( cit = array.cbegin() + 1 ; cit != array.cend() ; ++cit )
	{
		// display single value
		os << " - " << *cit ;
	}
	os << std::endl ;
	
	os << "---------" ;
	return os ;
}

///
/// \brief Display a map
/// \param os Stream for the display
/// \param map Map
/// \return Stream with the display in it
///
template < typename T1, typename T2 >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::map< T1, T2 > & map
)
{
	typename std::map< T1, T2 >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = map.cbegin() ; cit != map.cend() ; ++cit )
	{
		// display single value
		os << ( *cit ).first << " - " << ( *cit ).second << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

///
/// \brief Extract a vector from a map
/// \param map Map
/// \param key Key 
/// \return Vector which contains only values with the right key
///
template < typename T >
std::vector< T >
extract
(
	const std::map< std::string, T > & map,
	const std::string & key = ""
)
{
	typename std::vector< T > result ;
	
	typename std::map< std::string, T >::const_iterator cit ;
	typename std::map< std::string, T >::const_iterator cit_begin = map.cbegin() ;
	typename std::map< std::string, T >::const_iterator cit_end = map.cend() ;
	
	if( !( key.empty() ) )
	{
		cit_begin = map.lower_bound( key ) ;
		cit_end = map.upper_bound( key ) ;
	}
	
	for( cit = cit_begin ; cit != cit_end ; ++cit )
	{
		result.push_back( ( *cit ).second ) ;
	}

	return result ;
}

///
/// \brief Display a multimap
/// \param os Stream for the display
/// \param multimap Multimap
/// \return Stream with the display in it
///
template < typename T1, typename T2 >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::multimap< T1, T2 > & multimap
)
{
	typename std::multimap< T1, T2 >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = multimap.cbegin() ; cit != multimap.cend() ; ++cit )
	{
		// display single value
		os << ( *cit ).first << " - " << ( *cit ).second << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

///
/// \brief Display a vector
/// \param os Stream for the display
/// \param vector Vector
/// \return Stream with the display in it
///
template < typename T >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::vector< T > & vector
)
{
	typename std::vector< T >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = vector.cbegin() ; cit != vector.cend() ; ++cit )
	{
		// display single value
		os << *cit << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

#endif // STD_HPP
