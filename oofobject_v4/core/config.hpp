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
		static bool __DEBUG__ ;
		static bool __OPENMP__ ;
		static std::string __DIR__ ;
		static std::string __LOG__ ;
		static std::string __PROJECT__ ;
		static std::string __SESSION__ ;
		
		inline void toggle_DEBUG()
			{ __DEBUG__ = !( __DEBUG__ ) ; }	
		
	protected :
		
		// --- CONSTRUCTORS ---
		Config() ;
		
		// --- DESTRUCTORS ---
		~Config() ;
		
		// --- METHODS ---
		void default_config() ;
		bool read_config() ;
} ;

#endif // CONFIG_HPP
