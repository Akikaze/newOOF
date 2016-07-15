#ifndef CORE_HPP
#define CORE_HPP

#include "ioof_object.hpp"

class Core
: public OOF_SINGLETON< Core >
{
	friend class OOF_SINGLETON< Core > ;
	
	public :
		
		// --- DESTRUCTORS ---
		~Core() ;
		
		// --- METHODS ---
		void display_logs() const ;
		
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
