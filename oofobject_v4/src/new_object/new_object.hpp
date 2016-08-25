#ifndef NEW_OBJECT_HPP
#define NEW_OBJECT_HPP

#include "../../basis/oof_object.hpp"

class NewObject
: public OOF_OBJECT< NewObject >
{
	public :
		
		// --- CONSTRUCTORS ---
		NewObject( const std::string & name = "", const std::string & code = "" ) ;
		
		// --- DESTRUCTORS ---
		~NewObject() ;
		
		// --- ATTRIBUTES ---
		static std::string _extension_ ;
		static std::string _typename_ ;
} ;

#endif // NEW_OBJECT_HPP
