#ifndef CORE_HPP
#define CORE_HPP

#include "oof_object.hpp"

class Core
: public OOF_SINGLETON< Core >
{
	friend class OOF_SINGLETON< Core > ;
	
	public :
		
		// --- DESTRUCTORS ---
		~Core() ;
		
		// --- ATTRIBUTES ---
		CommandParser * cp_ ;
		InstanceManager * im_ ;
		LogDevice * ld_ ;
		ProjectStorage * ps_ ;
		
	protected :
	
		// --- CONSTRUCTORS ---
		Core() ;
} ;

#endif // CORE_HPP
