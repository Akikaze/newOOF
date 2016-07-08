#ifndef CORE_HPP
#define CORE_HPP

#include "oofobject.hpp"
#include "command_parser.hpp"
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
		CommandParser * command_parser_ ;
		LogDevice * log_device_ ;
		ProjectStorage * project_storage_ ;
		
	protected :
	
		// --- CONSTRUCTORS ---
		Core() ;
} ;

#endif // CORE_HPP
