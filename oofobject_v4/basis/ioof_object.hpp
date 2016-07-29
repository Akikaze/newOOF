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
		
		///
		/// \brief Destructor
		///
		virtual ~IOOF_OBJECT() ;
		
		// --- GETTERS ---
		
		///
		/// \brief Get the code of the object
		/// \return The code in a string
		///
		inline std::string get_code() const
			{ return code_ ; }
		
		///
		/// \brief Get the name of the object
		/// \return The name in a string
		///
		inline std::string get_name() const
			{ return name_ ; }
		
		///
		/// \brief Get the extension of the object
		/// \return The extension in a string
		///
		virtual std::string get_extension() const = 0 ;
		
		///
		/// \brief Get the type of the object
		/// \return The type in a string
		///
		virtual std::string get_typename() const = 0 ;
		
		// --- COMPARATORS ---
		struct ComparatorCode {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				// compare by code
				return ( l->get_code() < r->get_code() ) ;
			}
		} ;
		struct ComparatorName {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				// compare by name
				return ( l->get_name() < r->get_name() ) ;
			}
		} ;
		struct ComparatorTime {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				// compare by date
				return ( l->last_update_ < r->last_update_ ) ;
			}
		} ;
		struct ComparatorTypename {
			bool operator()( const IOOF_OBJECT * l, const IOOF_OBJECT * r ) {
				// compare by type
				return ( l->get_typename() < r->get_typename() ) ;
			}
		} ;
		
		// --- ATTRIBUTES ---
		time_t last_update_ ; ///< Date of the last update of the object
		static LogDevice * _ld_ ; ///< Pointer to the LogDevice
		static InstanceManager * _im_ ; ///< Pointer to the InstanceManager
		
	protected :
		
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		IOOF_OBJECT() ;
		
		// --- METHODS ---
		
		///
		/// \brief Add an object to the InstanceManager
		/// \param instance Pointer to the object
		///
		void add( IOOF_OBJECT * instance ) const ;
		
		///
		/// \brief Extract instances of a specific type
		/// \param type Type of instance
		/// \return Vector which contains instances
		///
		std::vector< IOOF_OBJECT * > extract( const std::string & type ) const ;
		
		///
		/// \brief Remove an object from the InstanceManager
		/// \param instance Pointer to the object
		///
		void remove( IOOF_OBJECT * instance ) const ;
		
		// --- ATTRIBUTES ---
		bool loaded_ ; ///< True if the object is loaded from a file
		std::string code_ ; ///< Code of the object
		std::string name_ ; ///< Name of the object
} ;

// ----- late includes -----

#include "instance_manager.hpp"
#include "log_device.hpp"

#endif // IOOF_OBJECT_HPP
