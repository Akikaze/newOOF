#ifndef LOG_DEVICE_HPP
#define LOG_DEVICE_HPP

#include "oof_object.hpp"
#include "std.hpp"

class LogDevice
: public OOF_SINGLETON< LogDevice >
{
	friend class OOF_SINGLETON< LogDevice > ; // constructor
	friend class Core ; // destructor
	
	public :
		
	protected :
	
		// --- CONSTRUCTORS ---
		LogDevice() ;
		
		// --- DESTRUCTORS ---
		~LogDevice() ;
		
} ;

#endif // LOG_DEVICE_HPP
