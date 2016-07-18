#ifndef NEW_OBJECT_HPP
#define NEW_OBJECT_HPP

#include "../core/oof_object.hpp"

class NewObject
: public OOF_OBJECT< NewObject >
{
	public :
		
		NewObject( const std::string & name = "" ) ;
		~NewObject() ;
		static std::string _typename_ ;
} ;

#endif // NEW_OBJECT_HPP
