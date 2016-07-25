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
		
		///
		/// \brief Add an object in the multimap
		/// \param instance Pointer on the new object
		///
		void add( IOOF_OBJECT * instance ) ;
		
		///
		/// \brief Extract all instances as a vector
		/// \return Vector which contains instances
		///
		std::vector< IOOF_OBJECT * > extract() const ;
		
		///
		/// \brief Extract all instance of a specific type
		/// \param type Tpe of the instance which needs to be extracted
		/// \return Vector which contains instances
		///
		std::vector< IOOF_OBJECT * > extract( const std::string & type ) const ;
		
		///
		/// \brief Extract all instance modified after a specific date
		/// \param date Date parameter for the comparison
		/// \return Vector which contains instances
		///
		std::vector< IOOF_OBJECT * > extract( const time_t & date ) const ;
		
		///
		/// \brief Remove an object from the multimap
		/// \param instance Pointer on the object
		///
		void remove( IOOF_OBJECT * instance ) ;
	
	protected :
	
		// --- DESTRUCTORS ---
		
		///
		/// \brief Destructor
		///
		~InstanceManager() ;
		
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		InstanceManager() ;
} ;

#endif // INSTANCE_MANAGER_HPP
