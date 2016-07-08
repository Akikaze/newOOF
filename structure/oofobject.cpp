#include "oofobject.hpp"

// ===== IOOF_SINGLETON =====

// --- static ---

std::vector< IOOF_SINGLETON * > IOOF_SINGLETON::_list_singleton_ = std::vector< IOOF_SINGLETON * >() ;

// --- CONSTRUCTORS ---

IOOF_SINGLETON::IOOF_SINGLETON
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_SINGLETON construction" << std::endl ;
#endif

	_list_singleton_.push_back( this ) ;
}

// --- DESTRUCTORS ---

IOOF_SINGLETON::~IOOF_SINGLETON
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_SINGLETON destruction" << std::endl ;
#endif

	std::vector< IOOF_SINGLETON * >::const_iterator cit = _list_singleton_.cbegin() ;
	
	while( *cit != this )
	{
		++cit ;
	}
	
	_list_singleton_.erase( cit ) ;
}

// ===== IOOF_OBJ =====

// --- static ---

std::vector< IOOF_OBJ * > IOOF_OBJ::_list_obj_ = std::vector< IOOF_OBJ * >() ;
std::vector< IOOF_OBJ * > IOOF_OBJ::_list_type_ = std::vector< IOOF_OBJ * >() ;
LogDevice * IOOF_OBJ::_log_device_ = NULL ;

// --- CONSTRUCTORS ---

IOOF_OBJ::IOOF_OBJ
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_OBJ construction" << std::endl ;
#endif

	if( _log_device_ == NULL )
	{
		_log_device_ = LogDevice::get_instance() ;
	}

	_list_obj_.push_back( this ) ;
	last_update_ = time( NULL ) ;
}

// --- DESTRUCTORS ---

IOOF_OBJ::~IOOF_OBJ
()
{
#ifdef __DEBUG__
	std::cout << "IOOF_OBJ destruction" << std::endl ;
#endif

	std::vector< IOOF_OBJ * >::const_iterator cit = _list_obj_.cbegin() ;
	
	while( *cit != this )
	{
		++cit ;
	}
	
	_list_obj_.erase( cit ) ;
}
