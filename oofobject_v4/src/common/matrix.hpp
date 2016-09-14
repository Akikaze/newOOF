#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../basis/config.hpp"
#include "../basis/std.hpp"

// ===== MATRIXDATA_2D =====

template< typename T >
class Matrix_2D ;

template< typename T >
class MatrixData_2D
: public std::vector< std::vector< T > >
{
	friend Matrix_2D< T > ;
	
	protected :
		
		// --- CONSTRUCTORS ---
		
		MatrixData_2D( unsigned short rows = 0,
					   unsigned short cols = 0,
					   Matrix_2D< T > * reference = nullptr ) ;
		
		// --- DESTRUCTORS ---
		
		~MatrixData_2D() ;
		
		// --- METHODS ---
		
		void add_reference( Matrix_2D< T > * reference ) ;
		void del_reference( Matrix_2D< T > * reference ) ;
		
		// --- ATTRIBUTES ---
		
		Matrix_2D< T > * reference_ ;
		std::list< Matrix_2D< T > * > list_references_ ;
} ;

// --- CONSTRUCTORS ---

template< typename T >
MatrixData_2D< T >::MatrixData_2D
(
	unsigned short rows,
	unsigned short cols,
	Matrix_2D< T > * reference
)
{
	// define the main reference
	reference_ = reference ;
	
	// add the reference on top of the list
	list_references_.push_back( reference ) ;
	
	// create the matrix
	this->resize( rows ) ;
	for( int i = 0 ; i < rows ; ++i )
	{
		this->at( i ).resize( cols ) ;
	}
}

// --- DESTRUCTORS ---

template< typename T >
MatrixData_2D< T >::~MatrixData_2D
()
{
	// remove the reference without deleting it
	// * Because the destruction of MatrixData_2D could only be called by
	// * the destruction of the reference. So deleting the reference at
	// * that point means destroy the caller of this destruction
	list_references_.erase( list_references_.begin() ) ;
	
	for( unsigned int i = 0 ; i < list_references_.size() ; ++i )
	{
		delete list_references_.front() ;
	}
}

// --- METHODS ---

template< typename T >
void
MatrixData_2D< T >::add_reference
(
	Matrix_2D< T > * reference
)
{
	// add the reference in the list
	list_references_.push_back( reference ) ;
}

template< typename T >
void
MatrixData_2D< T >::del_reference
(
	Matrix_2D< T > * reference
)
{
	typename std::list< Matrix_2D< T > * >::iterator it = list_references_.begin() ;
	
	// find the right position in the list
	while( it != list_references_.end() && ( *it ) != reference )
	{
		++it ;
	}
	
	// delete the reference
	list_references_.erase( it ) ;
}

// ===== MATRIX_2D =====

template< typename T >
class Matrix_2D
{
	public :
	
		// --- CONSTRUCTORS ---
		
		Matrix_2D( unsigned short rows = 0,
				   unsigned short cols = 0 ) ;
		
		// --- DESTRUCTORS ---
		
		~Matrix_2D() ;
		
		// --- METHODS ---
		
		Matrix_2D * sub_matrix( unsigned short pos_x, 
								unsigned short pos_y,
								unsigned short rows,
								unsigned short cols ) ;
	
	protected :
	
		// --- CONSTRUCTORS ---
		
		Matrix_2D( MatrixData_2D< T > * data,
				   unsigned short rows,
				   unsigned short cols,
				   unsigned short pos_x,
				   unsigned short pos_y ) ;
	
		// --- ATTRIBUTES ---
		
		MatrixData_2D< T > * data_ ;
		
		unsigned short rows_ ;
		unsigned short cols_ ;
		
		unsigned short pos_x_ ;
		unsigned short pos_y_ ;	
} ;

// --- CONSTRUCTORS ---

template< typename T >
Matrix_2D< T >::Matrix_2D
(
	unsigned short rows,
	unsigned short cols
)
{
	// create a new matrix by passing this as the main reference
	data_ = new MatrixData_2D< T >( rows, cols, this ) ;
	
	// fulfill attributes
	rows_ = rows ;
	cols_ = cols ;
	
	pos_x_ = 0 ;
	pos_y_ = 0 ;
}

template< typename T >
Matrix_2D< T >::Matrix_2D
(
	MatrixData_2D< T > * data,
	unsigned short rows,
	unsigned short cols,
	unsigned short pos_x,
	unsigned short pos_y
)
{
	// use the same data to create a sub-matrix
	data_ = data ;
	
	// fulfill attributes
	rows_ = rows ;
	cols_ = cols ;
	
	pos_x_ = pos_x ;
	pos_y_ = pos_y ;
	
	// add the reference of this sub-matrix
	data_->add_reference( this ) ;
}

// --- DESTRUCTORS ---

template< typename T >
Matrix_2D< T >::~Matrix_2D
()
{
	// if it's the main reference
	if( this == data_->reference_ )
	{
		// destroy the MatrixData entirely
		delete data_ ;
		data_ = nullptr ;
	}
	else
	{
		// just remove the reference from the MatrixData list
		data_->del_reference( this ) ;
		data_ = nullptr ;
	}
}

// --- METHODS ---

template< typename T >
Matrix_2D< T > *
Matrix_2D< T >::sub_matrix
(
	unsigned short pos_x,
	unsigned short pos_y,
	unsigned short rows,
	unsigned short cols
)
{
	// by default, it's the same pointer
	Matrix_2D< T > * pointer = this ;
	
	if( pos_x_ != pos_x ||
		pos_y_ != pos_y ||
		rows_ != rows ||
		cols_ != cols )
	{
		// create a sub-matrix
		pointer = new Matrix_2D< T >( data_, rows, cols, pos_x, pos_y ) ;
	}
	
	return pointer ;
}


#endif // MATRIX_HPP
