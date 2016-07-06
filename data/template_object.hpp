#ifndef TEMPLATE_OBJECT_HPP
#define TEMPLATE_OBJECT_HPP

#include "oofobject.hpp"
#include "command_parser.hpp"
#include "project_storage.hpp"

class NewObject
: public OOF_OBJ< NewObject >
{
	public :
		// --- CONSTRUCTORS ---
		NewObject( const std::string & ) ;
		
		// --- DESTRUCTORS ---
		~NewObject() ;
		
		// --- GETTERS ---
		virtual inline std::string get_typename() const
			{ return _typename_ ; }
		
		// --- ATTRIBUTES ---
		
		// --- static ---
		static const std::string _typename_ ;
	
	protected :
		
	
	private :
		
} ;

#endif // TEMPLATE_OBJECT_HPP
