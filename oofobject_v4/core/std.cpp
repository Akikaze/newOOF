#include "std.hpp"

std::string
display
(
	time_t date
)
{
	char buffer[ 100 ] ;
	strftime( buffer, 100, "%F-%T", localtime( &date ) ) ;
	return std::string( buffer ) ;
}
