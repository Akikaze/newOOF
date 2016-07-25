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
		
		///
		/// \brief Constructor
		///
		~Core() ;
		
		// --- METHODS ---
		
		///
		/// \brief Display logs
		/// \note for test
		///
		void display_logs() const ;
		
		///
		/// \brief Load objects
		/// \note for test
		///
		void load() const ;
		
		///
		/// \brief Save objects
		/// \note for test
		///
		void save() const ;
		
		// --- ATTRIBUTES ---
		CommandParser * cp_ ; ///< Pointer to the CommandParser
		InstanceManager * im_ ; ///< Pointer to the InstanceManager
		LogDevice * ld_ ; ///< Pointer to the LogDevice
		ProjectStorage * ps_ ; ///< Pointer to the ProjectStorage
		
	protected :
	
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		Core() ;
		
		// --- METHODS ---
		
		///
		/// \brief Prepare the system for specific object
		/// \param useless Empty pointer unused in the method, only the type is important
		///
		template < class T > void prepare( T * useless ) const ;
} ;

#endif // CORE_HPP
