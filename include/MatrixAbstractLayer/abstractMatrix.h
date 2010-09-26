/*
 * Copyright 2008, 2009, 2010, 
 *
 * Francois Keith,
 * Florent Lamiraux,
 * Nicolas Mansard
 *
 * CNRS/AIST
 *
 * This file is part of MatrixAbstractLayer.
 * MatrixAbstractLayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MatrixAbstractLayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with MatrixAbstractLayer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MAAL_ABSTRACT_MATRIX_
#define __MAAL_ABSTRACT_MATRIX_

namespace maal{  

  /*! \brief Abstract (purely virtual) version of the Maal2.
   *
   * Define an abstract version of the Matrix and Vector classes,
   * with all the generic function definitions.
   * The specific Matrix and Vector classes could be defined as
   * children of the abstract class.
   */
  namespace abstract {


    /* --- MATRIX --------------------------------------------------------- */
    /* --- MATRIX --------------------------------------------------------- */
    /* --- MATRIX --------------------------------------------------------- */

    /** \brief Abstract Matrix class. 
     */
    
    class Matrix
      {
      public: /* Constructors */
	
	Matrix( const unsigned int rows=0, const unsigned int cols=0 );
	Matrix( InternalMatrix* clone,const bool proprio=false );
	Matrix( const Matrix& copy );
	virtual ~Matrix( void );

	InternalMatrix& accessToMotherLib( void ) ;
	const InternalMatrix& accessToMotherLib( void ) const ;
	Matrix & initFromMotherLib( const InternalMatrix& bv ) ;

      public:

	inline Matrix& resize( const unsigned int nbRows,
			       const unsigned int nbCols,const bool setZero=true ) ;
       
	inline unsigned int nbRows( void ) const; 
	inline unsigned int nbCols( void ) const; 

	inline Matrix& setZero( void ) ;
	inline Matrix& setIdentity( void  ) ;
	inline Matrix& fill( const FloatType value ) ;
	
	/* -------------- */
	/* --- SCALAR --- */
	/* -------------- */
	inline FloatType determinant( void ) const;
	inline FloatType trace( void ) const  ;
	inline FloatType norm( void ) const ;
	inline FloatType norm1( void ) const ;
	inline FloatType normInfty( void ) const ;
	inline FloatType max( void ) const ;
	inline FloatType min( void ) const ;
	inline FloatType sumSquare( void ) const ;

	/* --------------- */
	/* --- INVERSE --- */
	/* --------------- */
	inline Matrix& 	transpose( Matrix& At ) const ;
	inline Matrix transpose( void )  const ;
       
	inline Matrix& inverse( Matrix& invMatrix ) const ;
	inline Matrix inverse( void )  const ;
	
	Matrix& pseudoInverse( Matrix& invMatrix,
			       const FloatType threshold = 1e-6,
			       Matrix* Uref = NULL,
			       Matrix* Sref = NULL,
			       Matrix* Vref = NULL)  const ;
	inline Matrix pseudoInverse( const FloatType threshold = 1e-6,
				     Matrix* U = NULL,
				     Matrix* S = NULL,
				     Matrix* V = NULL)  const ;
	inline Matrix& dampedInverse( Matrix& invMatrix,
				      const FloatType threshold = 1e-6,
				      Matrix* U = NULL,
				      Matrix* S = NULL,
				      Matrix* V = NULL)  const ;
	inline Matrix dampedInverse( const FloatType threshold = 1e-6,
				     Matrix* U = NULL,
				     Matrix* S = NULL,
				     Matrix* V = NULL)  const ;
	
	inline Matrix& opposite( Matrix& res ) const ; 
	inline Matrix opposite( void ) const  ;

	/* ----------------------- */
	/* --- OPERATOR ExE->E --- */
	/* ----------------------- */
	// Multiplication <Matrix> x <Matrix>
	inline friend Matrix& multiply( const Matrix& A,const Matrix& B,Matrix& C );
	inline Matrix multiply( const Matrix& B ) const ;
	inline Matrix& multiply( const Matrix& B,Matrix& C ) const ;

	// Multiplication <Matrix> x <Vector>
	friend inline Vector& multiply( const Matrix& M, const Vector& v, Vector& res ); 
	inline Vector multiply( const Vector& v ) const ;
	inline Vector& multiply(  const Vector& v, Vector& res ) const ;
      
	// Addition 
	inline friend Matrix& addition( const Matrix& A,const Matrix& B,Matrix& C );
	inline Matrix addition( const Matrix& B ) const; 
	inline Matrix&	addition( const Matrix& B,Matrix& C ) const ;

	// Substraction 
	inline friend Matrix& substraction( const Matrix& A,const Matrix& B,Matrix& C );
	inline Matrix substraction( const Matrix& B ) const ;
	inline Matrix& substraction( const Matrix& B,Matrix& C ) const ;
     
	// ---> With real
	// Multiplication <Matrix> x <Float>
	inline friend Matrix& multiply( const Matrix& A,const FloatType x,Matrix& C );
	inline Matrix multiply( const FloatType x ) const ;
	inline Matrix& multiply( const FloatType x,Matrix& C ) const ;
	
	// Addition <Matrix> x <Float>
	inline friend Matrix& addition( const Matrix& A,const FloatType x,Matrix& C );
	inline Matrix addition( const FloatType x ) const ;
	inline Matrix& addition( const FloatType x,Matrix& C ) const ;

	// Substraction <Matrix> x <Float>
	inline friend Matrix& substraction( const Matrix& A,const FloatType x,Matrix& C );
	inline Matrix substraction( const FloatType x ) const ;
	inline Matrix& substraction( const FloatType x,Matrix& C ) const ;

	// Division <Matrix> x <Float>
	inline friend Matrix& division( const Matrix& A,const FloatType x,Matrix& C ) ;
	inline Matrix division( const FloatType x ) const ;
	inline Matrix& division( const FloatType x,Matrix& C ) const ;

	/* ------------------- */
	/* --- DATA ACCESS --- */
	/* ------------------- */
	inline FloatType* datablock( void );
	inline const FloatType* datablock( void ) const;
	
	inline Matrix& extract( const int top,const int left, 
				const int nbrows, const int nbcols,
				Matrix& C ) const; 
	inline Matrix extract( const int top,const int left, 
			       const int nbrows, const int nbcols ) const;
	
	inline const FloatType& elementAt( const int row,const int col ) const;
	inline FloatType& elementAt( const int row,const int col );
	inline const FloatType& elementAt( const int elmt ) const;
	inline FloatType& elementAt( const int elmt ) ;
      
	/* ------------- */
	/* --- BONUS --- */
	/* ------------- */
	inline Vector getDiagonal( void ) const  ;
	inline Vector& getDiagonal( Vector& vector ) const  ;
	inline Matrix& setDiagonal( const Vector& vector );
	inline Matrix& stackMatrix( const Matrix& B,Matrix& C )  const ;
	inline Matrix stackMatrix( const Matrix& B ) const ;
	inline Matrix& juxtaposeMatrix( const Matrix& B,Matrix& C ) const ;
	inline Matrix juxtaposeMatrix( const Matrix& B ) const ;
	
	/* ----------------- */
	/* --- OPERATORS --- */
	/* ----------------- */
	inline friend Matrix operator+ ( const Matrix&m1,const Matrix&m2 );
	inline friend Matrix operator- ( const Matrix&m1,const Matrix&m2 );
	inline friend Matrix operator* ( const Matrix&m1,const Matrix&m2 );
      
	inline Matrix& operator+= ( const Matrix&m1 );
	inline Matrix& operator-= ( const Matrix&m1 );
	inline Matrix& operator*= ( const Matrix&m1 );
	inline Matrix& operator*= ( const FloatType x );

	inline friend Matrix operator- ( const Matrix& m );
      
	inline const FloatType& operator()( const int i,const int j )const; 
	inline FloatType& operator()( const int i,const int j );
	inline const FloatType& operator()( const int n )const ;
	inline FloatType& operator()( const int n ) ;
      
	inline Matrix& operator= ( const Matrix&m1 );
 
	inline friend Vector operator * ( const Matrix& M,const Vector& v1 );    
	inline friend Vector operator * ( const Vector& v1,const Matrix& M );
      
	inline friend Matrix operator+ ( const FloatType x,const Matrix&m1 );
	inline friend Matrix operator- ( const FloatType x,const Matrix&m1 );
	inline friend Matrix operator* ( const FloatType x,const Matrix&m1 );
	inline friend Matrix operator/ ( const FloatType x,const Matrix&m1 );

	inline friend Matrix operator+ ( const Matrix&m1,const FloatType x );
	inline friend Matrix operator- ( const Matrix&m1,const FloatType x );
	inline friend Matrix operator* ( const Matrix&m1,const FloatType x );
	inline friend Matrix operator/ ( const Matrix&m1,const FloatType x );

	inline friend std::ostream& operator<< ( std::ostream& os,const Matrix& m1 );
	inline friend std::istream& operator>> ( std::istream& is,Matrix& v1 );
      };
  }}

#endif // #ifndef __MAAL_ABSTRACT_MATRIX_

