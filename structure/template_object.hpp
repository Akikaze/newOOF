#ifndef TEMPLATE_OBJECT_HPP
#define TEMPLATE_OBJECT_HPP

#include "oofobject.hpp"

class NewObject
: public OOF_OBJ< NewObject >
{
	public :
		// --- CONSTRUCTORS ---
		NewObject( const std::string & ) ;
		
		// --- DESTRUCTORS ---
		virtual ~NewObject() ;
		
		// --- GETTERS ---
		virtual inline std::string get_typename() const
			{ return "NewObject" ; }
		
	
	protected :
		
	
	private :
		
} ;

#endif // TEMPLATE_OBJECT_HPP
