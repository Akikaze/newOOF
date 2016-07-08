#ifndef TEST_HPP
#define TEST_HPP

// #define __DEBUG__

#include "oofobject.hpp"

class TEST_A
: public OOF_OBJ< TEST_A >
{
	public :
	
		// --- CONSTRUCTORS ---
		TEST_A() ;
		
		// --- DESTRUCTORS ---
		virtual ~TEST_A() ;
	
		// --- GETTERS ---
		virtual inline std::string get_typename() const
			{ return "TEST_A" ; }
} ;

class TEST_B
: public OOF_OBJ< TEST_B >
{
	public :
	
		// --- CONSTRUCTORS ---
		TEST_B() ;
		
		// --- DESTRUCTORS ---
		virtual ~TEST_B() ;
		
		// --- GETTERS ---
		virtual inline std::string get_typename() const
			{ return "TEST_B" ; }
} ;

#endif // TEST_HPP
