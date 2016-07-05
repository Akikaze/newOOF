#ifndef TEST_HPP
#define TEST_HPP

// #define __DEBUG__

/*
 * WARNING: oofobject.hpp needs to be include before command_parser.hpp
 * But command_parser.hpp needs to be include even if there is no link
 * between test.hpp and command_parser.hpp
 */
 
#include "oofobject.hpp"
#include "command_parser.hpp"
#include "project_storage.hpp"

class TEST_A
: public OOF_OBJ< TEST_A >
{
	public :
	
		// --- CONSTRUCTORS ---
		TEST_A() ;
		
		// --- DESTRUCTORS ---
		~TEST_A() ;
	
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
		~TEST_B() ;
		
		// --- GETTERS ---
		virtual inline std::string get_typename() const
			{ return "TEST_B" ; }
} ;

#endif // TEST_HPP
