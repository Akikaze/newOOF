#ifndef CORE_HPP
#define CORE_HPP

#include "oof_object.hpp"
#include "command_parser.hpp"
#include "instance_manager.hpp"
#include "log_device.hpp"
#include "project_storage.hpp"

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
