#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstdlib> // getenv
#include "oof_singleton.hpp"
#include "std.hpp"

class Config
: public OOF_SINGLETON< Config >
{
	friend class OOF_SINGLETON< Config > ; // constructor
	
	public :
		
		// --- ATTRIBUTES ---
		static bool __DEBUG__ ; ///< Debug mode
		static bool __OPENMP__ ; ///< Parallelization mode
		static std::string __DIR__ ; ///< Path to the main directory
		static std::string __LOG__ ; ///< Name of the directory for logs
		static std::string __PROJECT__ ; ///< Name of the directory for the project
		static std::string __SESSION__ ; ///< Time code for the session
		
		///
		/// \brief Change the value of the debug mode
		///
		inline void toggle_DEBUG()
			{ __DEBUG__ = !( __DEBUG__ ) ; }	
		
	protected :
		
		// --- CONSTRUCTORS ---
		
		///
		/// \brief Constructor
		///
		Config() ;
		
		// --- DESTRUCTORS ---
		
		///
		/// \brief Destructor
		///
		~Config() ;
		
		// --- METHODS ---
		
		///
		/// \brief Load the default configuration
		///
		void default_config() ;
		
		///
		/// \brief Read the config file
		/// \return true if the config file was valid, false otherwise
		///
		bool read_config() ;
} ;

#endif // CONFIG_HPP
