#ifndef INCEPTION_HPP
#define INCEPTION_HPP

#include "../basis/std.hpp"

namespace Inc
{
	// ===== DATA =====
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	class Container ;

	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	class Data
	: public STL< T >
	{
		friend Container< T, STL > ;
		
		protected :
			
			// --- CONSTRUCTORS ---
			
			Data( Container< T, STL > * main_ref, unsigned short size = 0 ) ;
			
			// --- DESTRUCTORS ---
			
			~Data() ;
			
			// --- METHODS ---
			
			void add_reference( Container< T, STL > * reference ) ;
			void del_reference( Container< T, STL > * reference ) ;
			
			// --- ATTRIBUTES ---
			
			Container< T, STL > * main_ref_ ;
			std::deque< Container< T, STL > * > references_ ;
	} ;
	
	// --- CONSTRUCTORS ---
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	Data< T, STL >::Data
	(
		Container< T, STL > * main_ref,
		unsigned short size
	)
	{
		// define the main reference
		main_ref_ = main_ref ;
		
		// add the reference on top of the deque
		references_.push_back( main_ref ) ;
		
		// create the dynamic array
		this->resize( size ) ;
	}
	
	// --- DESTRUCTORS ---
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	Data< T, STL >::~Data
	()
	{
		// remove the reference without deleting it
		// * Because the destruction of the Data could only be called by
		// * the destruction of the reference. So deleting the reference at
		// * that point means destroy the caller of this destruction
		
		main_ref_ = nullptr ;
		references_.erase( references_.begin() ) ;
		
		for( unsigned int i = 0 ; i < references_.size() ; ++i )
		{
			// delete the pointer is going to call del_reference and erase the position
			delete references_.front() ;
		}
	}
	
	// --- METHODS ---
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	void
	Data< T, STL >::add_reference
	(
		Container< T, STL > * reference
	)
	{
		// add the reference in the deque
		references_.push_back( reference ) ;
	}
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	void
	Data< T, STL >::del_reference
	(
		Container< T, STL > * reference
	)
	{
		typename std::deque< Container< T, STL > * >::iterator it = references_.begin() ;
	
		// find the right position in the deque
		while( it != references_.end() && ( *it ) != reference )
		{
			++it ;
		}
		
		// delete the reference
		references_.erase( it ) ;
	}

	// ====== CONTAINER =====

	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	class Container
	{
		public :
		
			// --- CONSTRUCTORS ---
			
			Container( unsigned short size = 0 ) ;
			Container( Data< T, STL > * data, unsigned short position, unsigned short size ) ;
			
			// --- DESTRUCTORS ---
			
			~Container() ;
			
			// --- METHODS ---
			
			Container< T, STL > * subarray( unsigned short position, unsigned short size ) ;
			
		
		protected :
		
			// --- ATTRIBUTES ---
			
			Data< T, STL > * data_ ;
			unsigned short position_ ;
			unsigned short size_ ;
	} ;
	
	// --- CONSTRUCTORS ---
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	Container< T, STL >::Container
	(
		unsigned short size
	)
	{		
		// create the dynamic array by passing this as the main reference
		data_ = new Data< T, STL >( this, size ) ;
		
		// fulfill attributes
		position_ = 0 ;
		size_ = size ;
	}
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	Container< T, STL >::Container
	(
		Data< T, STL > * data,
		unsigned short position,
		unsigned short size
	)
	{
		// new reference
		data->add_reference( this ) ;
		
		// fulfill attributes
		data_ = data ;
		position_ = position ;
		size_ = size ;
	}
	
	// --- DESTRUCTORS ---
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	Container< T, STL >::~Container
	()
	{
		// if it's the main reference
		if( data_->main_ref_ == this )
		{
			// destroy the dynamic array entirely
			delete data_ ;
			data_ = nullptr ;
		}
		else
		{
			// just remove the reference from the deque
			data_->del_reference( this ) ;
			data_ = nullptr ;
		}
	}
	
	// --- METHODS ---
	
	template< typename T, template< typename, typename = std::allocator< T > > class STL >
	Container< T, STL > *
	Container< T, STL >::subarray
	(
		unsigned short position,
		unsigned short size
	)
	{
		// by default
		Container< T, STL > * result = nullptr ;
		
		// if it's the same position and the same size
		if( position_ == position && size_ == size )
		{
			// return the same pointer
			result = this ;
		}
		else if( size > 0 && position + size <= size_ )
		{
			// create a new reference on the same dynamic array
			result = new Container< T, STL >( data_, position, size ) ;
		}
		
		return result ;
	}
}

#endif // INCEPTION_HPP
