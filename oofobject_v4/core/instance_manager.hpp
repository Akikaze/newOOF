#ifndef INSTANCE_MANAGER_HPP
#define INSTANCE_MANAGER_HPP

#include "oof_singleton.hpp"
#include "ioof_object.hpp"

class InstanceManager
: public OOF_SINGLETON< InstanceManager >
, public std::multimap< std::string, IOOF_OBJECT * >
{
	friend OOF_SINGLETON< InstanceManager > ; // constructor
	friend class Core ; // destructor
	
	public :
		
		// --- METHODS ---
		void add( IOOF_OBJECT * instance ) ;
		std::vector< IOOF_OBJECT * > extract() const ;
		std::vector< IOOF_OBJECT * > extract( const std::string & type ) const ;
		std::vector< IOOF_OBJECT * > extract( const time_t & date ) const ;
		void remove( IOOF_OBJECT * instance ) ;
	
	protected :
	
		// --- DESTRUCTORS ---
		~InstanceManager() ;
		
		// --- CONSTRUCTORS ---
		InstanceManager() ;
} ;

#endif // INSTANCE_MANAGER_HPP
