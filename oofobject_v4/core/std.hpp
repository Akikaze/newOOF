#ifndef STD_HPP
#define STD_HPP

#include <algorithm>
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

// display any time
std::string display( time_t ) ;

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
		// display single value
		os << " - " << *cit ;
	}
	os << std::endl ;
	
	os << "---------" ;
	return os ;
}

// display any map
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

// extract vector from map
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

// display any multimap
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
		// display single value
		os << *cit << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

#endif // STD_HPP
