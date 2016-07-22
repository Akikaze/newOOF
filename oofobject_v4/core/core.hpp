#ifndef CORE_HPP
#define CORE_HPP

#include "config.hpp"
#include "ioof_object.hpp"
#include "command_parser.hpp"
#include "project_storage.hpp"

// ===== Core =====

class Core
: public OOF_SINGLETON< Core >
{
	friend class OOF_SINGLETON< Core > ;
	
	public :
		
		// --- DESTRUCTORS ---
		~Core() ;
		
		// --- METHODS ---
		void display_logs() const ;
		void load() const ;
		void save() const ;
		
		// --- ATTRIBUTES ---
		CommandParser * cp_ ;
		InstanceManager * im_ ;
		LogDevice * ld_ ;
		ProjectStorage * ps_ ;
		
	protected :
	
		// --- CONSTRUCTORS ---
		Core() ;
		
		// --- METHODS ---
		template < class T > void prepare( T * ) const ;
} ;

#endif // CORE_HPP
