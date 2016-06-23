#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

#include "test.hpp"

template < typename T >
std::ostream &
operator<<
(
	std::ostream & os,
	const std::vector< T * > & list
)
{
	typename std::vector< T * >::const_iterator cit ;
	
	os << "---------" << std::endl ;
	
	for( cit = list.cbegin() ; cit != list.cend() ; ++cit )
	{
		os << *cit << std::endl ;
	}
	
	os << "---------" ;
	return os ;
}

#endif
