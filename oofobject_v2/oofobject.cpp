#include "oofobject.hpp"

// ===== IOOF_LIST =====

// --- static ---

std::vector< IOOF_LIST * > IOOF_LIST::_object_ = std::vector< IOOF_LIST * >() ;

// --- CONSTRUCTORS ---

IOOF_LIST::IOOF_LIST
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_LIST construction" << std::endl ;
#endif

	_object_.push_back( this ) ;
}

// --- DESTRUCTORS ---

IOOF_LIST::~IOOF_LIST
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_LIST destruction" << std::endl ;
#endif

	std::vector< IOOF_LIST * >::const_iterator cit = _object_.cbegin() ;
	
	while( *cit != this )
	{
		++cit ;
	}
	
	_object_.erase( cit ) ;
}

// ===== IOOF_SINGLETON =====

// --- static ---

std::vector< IOOF_SINGLETON * > IOOF_SINGLETON::_object_ = std::vector< IOOF_SINGLETON * >() ;

// --- CONSTRUCTORS ---

IOOF_SINGLETON::IOOF_SINGLETON
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_SINGLETON construction" << std::endl ;
#endif

	_object_.push_back( this ) ;
}

// --- DESTRUCTORS ---

IOOF_SINGLETON::~IOOF_SINGLETON
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_SINGLETON destruction" << std::endl ;
#endif

	std::vector< IOOF_SINGLETON * >::const_iterator cit = _object_.cbegin() ;
	
	while( *cit != this )
	{
		++cit ;
	}
	
	_object_.erase( cit ) ;
}
