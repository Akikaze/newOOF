#ifndef LOG_DEVICE_HPP
#define LOG_DEVICE_HPP

#include "oofobject.hpp"
#include "std.hpp"

class LogDevice
: public OOF_SINGLETON< LogDevice >
{
	friend class OOF_SINGLETON< LogDevice > ;
	
	public :
		
		// --- DESTRUCTORS ---
		~LogDevice() ;
		
	protected :
	
		// --- CONSTRUCTORS ---
		LogDevice() ;
} ;

#endif // LOG_DEVICE_HPP
