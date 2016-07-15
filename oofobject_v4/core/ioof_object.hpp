#ifndef IOOF_OBJECT_HPP
#define IOOF_OBJECT_HPP

#include "global.hpp"
#include "std.hpp"

// ===== IOOF_OBJECT =====

/*
 * 
 */

// ----- prior definition -----

class InstanceManager ;
class LogDevice ;

// ----- class -----

class IOOF_OBJECT
{
	public :
		
		// --- DESTRUCTORS ---
		virtual ~IOOF_OBJECT() ;
		
		// --- GETTERS ---
		std::string get_name() const
			{ return name_ ; }
		virtual std::string get_typename() const = 0 ;
		
		// --- COMPARATORS ---
		struct ComparatorName {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				return ( l->get_name() < r->get_name() ) ;
			}
		} ;
		struct ComparatorTime {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				return ( l->last_update_ < r->last_update_ ) ;
			}
		} ;
		struct ComparatorTypename {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				return ( l->get_typename() < r->get_typename() ) ;
			}
		} ;
		
		// --- ATTRIBUTES ---
		time_t last_update_ ;
		static LogDevice * _ld_ ;
		static InstanceManager * _im_ ;
		
	protected :
		
		// --- CONSTRUCTORS ---
		IOOF_OBJECT() ;
		
		// --- METHODS ---
		void add( IOOF_OBJECT * ) const ;
		std::vector< IOOF_OBJECT * > extract( const std::string & ) const ;
		
		// --- ATTRIBUTES ---
		std::string name_ ;
} ;

// ----- late includes -----

#include "instance_manager.hpp"
#include "log_device.hpp"

#endif // IOOF_OBJECT_HPP
