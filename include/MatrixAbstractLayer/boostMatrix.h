/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      boostMatrix.h
 * Project:   Maal
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef __MAAL_BOOST_MATRIX_
#define __MAAL_BOOST_MATRIX_

#include <cstdio>
#include <MatrixAbstractLayer/boostMacros.h>
#include <MatrixAbstractLayer/boostSvd.h>

/**
 * \file boostMatrix.h Define maal::boost::Matrix
 */

namespace maal
{
  namespace boost 
    {


      /* --- MATRIX --------------------------------------------------------- */
      /* --- MATRIX --------------------------------------------------------- */
      /* --- MATRIX --------------------------------------------------------- */
      
      /** \brief Matrix class that include the boost::ublas::matrix.
       *
       * The class encapsulates the ublas::matrix object, and implement 
       * a set of standard functions.
       * When the maal::boost::Matrix object is constructed, it automatically 
       * builds the internal ublas::matrix object. The internal object can be
       * access through accessToMotherLib. Finally, it is possible to
       * build the capsule around an existing boost ublas::matrix through the
       * appropriate constructor. 
       * 
       */
  
      class Matrix
	{
      
	public://protected:
	  typedef ::boost::numeric::ublas::matrix<FloatType> InternalMatrix;
	  InternalMatrix staticMatrix; 
	  InternalMatrix* dynamicMatrix; 
	  InternalMatrix & matrix;
	  bool proprio; 
	  static const bool AUTORESIZE = true;
	  static const bool CHECKRESIZE = true;
	  
	public: /* Constructors */
	  
	  /** @name Constructors */
	  //@{
	  
	  /** \brief Classical constructor. 
	   *
	   * Build the internal matrix from the demanded size.
	   */
	Matrix( const unsigned int rows=0, const unsigned int cols=0 )
	  : staticMatrix( rows,cols ),dynamicMatrix( NULL ),matrix(staticMatrix)
	  {}
	  
	  /** \brief Build only the capsule around a already existing
	   * boost vector object. 
	   */
	Matrix( InternalMatrix* clone,const bool proprio=false )
	  : staticMatrix(0,0),dynamicMatrix( clone ),matrix(*dynamicMatrix)
	    ,proprio(proprio)
	  {}
	  
	  /** \brief Build a new internal vector from existing
	   * boost vector object by copying the data. 
	   */
	Matrix( const Matrix& copy )
	  : staticMatrix( copy.matrix ),dynamicMatrix( NULL ),matrix(staticMatrix)
	    ,proprio(false)
	    {}
	  
	  
	  virtual ~Matrix( void )
	    {
	      if( (NULL!=dynamicMatrix)&&(proprio) )
		{    delete dynamicMatrix;   }
	    }
	  
	  /** \brief Access to the boost internal vector. */
	  InternalMatrix& accessToMotherLib( void ) { return matrix; }
	  /** \brief Access to the boost internal vector. */
	  const InternalMatrix& accessToMotherLib( void ) const { return matrix; }
	  /** \brief Copy the values and data of an existing 
	   * boost vector. */
	  Matrix & initFromMotherLib( const InternalMatrix& bv ) 
	    { matrix = bv; return *this;}
	  //@}
	  
	public:
	  
	  /** @name Modifiors */
	  //@{
	  
	  inline Matrix& resize( const unsigned int nbRows,
				 const unsigned int nbCols,const bool setZero=true ) 
	  {
	    matrix.resize(nbRows,nbCols,!setZero); return *this;
	  }
	  
	  /** \brief Get the number of rows. */
	  inline unsigned int nbRows( void ) const { return matrix.size1();}
	  /** \brief Get the number of columns. */
	  inline unsigned int nbCols( void ) const { return matrix.size2();}
	  
	  inline Matrix& setZero( void ) { matrix.clear(); return *this; }
	  inline Matrix& setIdentity( void  ) 
	  { 
	    for(unsigned int i=0;i<matrix.size1();i++) 
	      {for(unsigned int j=0;j<matrix.size2();j++)
		  if (i==j) matrix(i,j) = 1; else matrix(i,j) = 0;
	      }
	    return *this;
	  } 
 
	  inline Matrix& fill( const FloatType value ) 
	  {
	    for(unsigned int i=0;i<matrix.size1();i++) 
	      for(unsigned int j=0;j<matrix.size2();j++)
		matrix(i,j) = value;
	    return *this;
	  }
	  //@}

	  /* -------------- */
	  /* --- SCALAR --- */
	  /* -------------- */
      
	  /** @name Scalar Operator E->R */
	  //@{
      
	  inline FloatType 
	    determinant( void ) const
	  {
	    if(! _checksizeSquareVerb( matrix ) )	    return -1;
 
	    InternalMatrix mLu(matrix);
	    ::boost::numeric::ublas::permutation_matrix<std::size_t> pivots(matrix.size1());

	    lu_factorize(mLu,pivots);
	    double det=1.0;
	    for( std::size_t i=0;i<pivots.size();++i )
	      {
		if (pivots(i)!=i)
		  det*=-1.0;
 
		det *= mLu(i,i);
	      }
	    return det;
	  } 


	  /** \brief Not implemented yet. */
	  inline FloatType
	    trace( void ) const  
	  {
	    fprintf(stderr,"Not implemented yet!!\n");
	    return 0;
	  }

	  /** \brief Not implemented yet. */
	  inline FloatType norm( void ) const {  ML_NOT_IMPLEMENTED(0) }
	  /** \brief Norm 1 sum( |xi| )  */
	  inline FloatType norm1( void ) const { return ::boost::numeric::ublas::norm_1(matrix); }
	  inline FloatType normInfty( void ) const { return norm_inf(matrix); }
	  /** \brief Not implemented yet. */
	  inline FloatType max( void ) const { ML_NOT_IMPLEMENTED(0) }
	  /** \brief Not implemented yet. */
	  inline FloatType min( void ) const { ML_NOT_IMPLEMENTED(0) }
	  /** \brief Not implemented yet. */
	  inline FloatType sumSquare( void ) const { ML_NOT_IMPLEMENTED(0) }

	  //@}
      
	  /* --------------- */
	  /* --- INVERSE --- */
	  /* --------------- */

	  //@{
	  /** @name Inverse */

	  inline Matrix& 
	    transpose( Matrix& At ) const 
	  {
	    //_resizeInv(At.matrix,matrix);
	    //trans(matrix,At.matrix);
	    At.matrix=trans(matrix); return At; // SO STUPID ...  
	  }
	  inline Matrix transpose( void )  const 
	  { 
	    Matrix At(matrix.size2(),matrix.size1()); return transpose(At); 
	  } 

	  /** \brief Compute the inverse of the matrix. 
	   *  
	   * The matrix has to be invertible. 
	   * By default, the function uses the dgesvd_ fortran routine. 
	   * It should be provided by the host software (i.e. lapack). 
	   */
	  inline Matrix&
	    inverse( Matrix& invMatrix ) const 
	  {							
	    _resizeInv(invMatrix.matrix,matrix);

	    /* Create a working copy of the input. */
	    ::boost::numeric::ublas::matrix<FloatType> A( matrix );
	    ::boost::numeric::ublas::permutation_matrix<std::size_t>  pm(A.size1());

	    /* Perform LU-factorization. */
	    int res = lu_factorize(A,pm);
	    if( res!=0 ) 
	      {
		fprintf( stderr,"!! %s(#%d)\tError while LU: not invertible.\n", 
			 __FUNCTION__,__LINE__); fflush(stderr);  
		invMatrix.matrix =  trans(matrix); 
		return invMatrix;
	      }

     
	    /* Create identity matrix of "inverse". */
	    invMatrix.matrix.assign( ::boost::numeric::ublas::identity_matrix<FloatType>(matrix.size1()) );
     
	    /* Backsubstitute to get the inverse. */
	    lu_substitute( (const InternalMatrix&)A,pm,invMatrix.matrix );
     
	    return invMatrix;
	  }	

	  inline Matrix inverse( void )  const 
	  { Matrix Ainv(matrix.size2(),matrix.size1()); return inverse(Ainv); }





	  /** \brief Compute the pseudo-inverse of the matrix. 
	   *  
	   * By default, the function uses the dgesvd_ fortran routine. 
	   * It should be provided by the host software. 
	   */
	  virtual Matrix& 
	    pseudoInverse( Matrix& invMatrix,
			   const FloatType threshold = 1e-6,
			   Matrix* Uref = NULL,
			   Vector* Sref = NULL,
			   Matrix* Vref = NULL)  const 
	  {	
	    unsigned int NR,NC;
	    bool toTranspose;
	    ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> I;
	    if( matrix.size1()>matrix.size2() )
	      { 
		toTranspose=false ;  NR=matrix.size1(); NC=matrix.size2();
		I=matrix; 
		_resizeInv(invMatrix.matrix,I);
	      }
	    else 
	      {
		toTranspose=true; NR=matrix.size2(); NC=matrix.size1();
		I = trans(matrix); 
		_resizeInv(invMatrix.matrix,I); // Resize the inv of the transpose.
	      }

	    ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> U(NR,NR); 
	    ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> VT(NC,NC);	
	    ::boost::numeric::ublas::vector<FloatType> s(std::min(NR,NC));		
	    char Jobu='A'; /* Compute complete U Matrix */	
	    char Jobvt='A'; /* Compute complete VT Matrix */	
	    char Lw; Lw='O'; /* Compute the optimal size for the working vector */ 


	    {
	      double vw;                                       
	      int lw=-1;

	      int linfo; const int n=NR,m=NC;
	      int lda = std::max(m,n);
	      int lu = traits::leading_dimension(U); // NR
	      int lvt = traits::leading_dimension(VT); // NC

	      dgesvd_(&Jobu, &Jobvt, &m, &n,                 
		      MRAWDATA(I), &lda,       
		      0, 0, &m, 0, &n, &vw, &lw, &linfo);    
	      lw = int(vw)+5;                                 
       
	      ::boost::numeric::ublas::vector<double> w(lw);		 
	      dgesvd_(&Jobu, &Jobvt,&n,&m,
		      MRAWDATA(I),
		      &lda,
		      VRAWDATA(s),
		      MRAWDATA(U),
		      &lu,
		      MRAWDATA(VT),
		      &lvt,
		      VRAWDATA(w),&lw,&linfo);
       
	    }


	    const unsigned int nsv = s.size();
	    unsigned int rankJ = 0;
	    ::boost::numeric::ublas::vector<FloatType> sp(nsv);
	    for( unsigned int i=0;i<nsv;++i )		
	      if( fabs(s(i))>threshold ) { sp(i)=1/s(i); rankJ++; }
	      else sp(i)=0.;		
	    invMatrix.matrix.clear();
	    {
	      double * pinv = MRAWDATA(invMatrix.matrix);
	      double * uptr;
	      double * uptrRow;
	      double * vptr;
	      double * vptrRow = MRAWDATA(VT);
       
	      double * spptr;
       
	      for( unsigned int i=0;i<NC;++i )
		{
		  uptrRow = MRAWDATA(U);
		  for( unsigned int j=0;j<NR;++j )
		    {
		      uptr = uptrRow;  vptr = vptrRow; 
		      spptr = VRAWDATA( sp );
		      for( unsigned int k=0;k<rankJ;++k )
			{
			  (*pinv) += (*vptr) * (*spptr) * (*uptr);
			  uptr+=NR; vptr++; spptr++;
			}
		      pinv++; uptrRow++; 
		    }
		  vptrRow += NC;
		}
	    }
	    if( toTranspose )
	      {
		invMatrix.matrix = trans(invMatrix.matrix);  
		if( Uref ) Uref->matrix = VT;
		if( Vref ) Vref->matrix = trans(U);
		if( Sref ) Sref->vector=s; 
	      }
	    else
	      {
		if( Uref ) Uref->matrix = U;
		if( Vref ) Vref->matrix = trans(VT);
		if( Sref )  Sref->vector=s; 
	      }
	    return invMatrix;
	  }


	  inline Matrix pseudoInverse( const FloatType threshold = 1e-6,
				       Matrix* U = NULL,
				       Vector* S = NULL,
				       Matrix* V = NULL)  const 
	  { Matrix Ainv(matrix.size2(),matrix.size1()); return pseudoInverse(Ainv,threshold,U,S,V); }

      





	  /** \brief Compute the pseudo-inverse of the matrix. 
	   *  
	   * By default, the function uses the dgesvd_ fortran routine. 
	   * It should be provided by the host software. 
	   */
	  virtual Matrix& 
	    dampedInverse( Matrix& invMatrix,
			   const FloatType threshold = 1e-6,
			   Matrix* Uref = NULL,
			   Vector* Sref = NULL,
			   Matrix* Vref = NULL)  const 
	  {	
	    unsigned int NR,NC;
	    bool toTranspose;
	    ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> I;
	    if( matrix.size1()>matrix.size2() )
	      { 
		toTranspose=false ;  NR=matrix.size1(); NC=matrix.size2();
		I=matrix; 
		_resizeInv(invMatrix.matrix,matrix);
	      }
	    else 
	      {
		toTranspose=true; NR=matrix.size2(); NC=matrix.size1();
		I = trans(matrix); 
		_resize(invMatrix.matrix,matrix); // Resize the inv of the transpose.
	      }
	    ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> U(NR,NR); 
	    ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> VT(NC,NC);	
	    ::boost::numeric::ublas::vector<FloatType> s(std::min(NR,NC));		
	    char Jobu='A'; /* Compute complete U Matrix */	
	    char Jobvt='A'; /* Compute complete VT Matrix */	
	    char Lw; Lw='O'; /* Compute the optimal size for the working vector */ 

	    /* Get workspace size for svd. */
	    {
	      int lw=-1;
	      {
		double vw;                                       
	 
		int linfo; const int n=NR,m=NC;
		int lda = std::max(m,n);
		int lu = traits::leading_dimension(U); // NR
		int lvt = traits::leading_dimension(VT); // NC
		
		dgesvd_(&Jobu, &Jobvt, &m, &n,                 
			MRAWDATA(I), &lda,       
			0, 0, &m, 0, &n, &vw, &lw, &linfo);    
		lw = int(vw)+5;                                 
	 
		::boost::numeric::ublas::vector<double> w(lw);		 
		dgesvd_(&Jobu, &Jobvt,&n,&m,
			MRAWDATA(I),
			&lda,
			VRAWDATA(s),
			MRAWDATA(U),
			&lu,
			MRAWDATA(VT),
			&lvt,
			VRAWDATA(w),&lw,&linfo);
	      }

	    }

	    const unsigned int nsv = s.size();
	    unsigned int rankJ = 0;
	    ::boost::numeric::ublas::vector<FloatType> sp(nsv);
	    for( unsigned int i=0;i<nsv;++i )		
	      {
		if( fabs(s(i))>threshold*.1 )   rankJ++; 
		sp(i)=s(i)/(s(i)*s(i)+threshold*threshold);
	      }
	    invMatrix.matrix.clear();
	    {
	      double * pinv = MRAWDATA(invMatrix.matrix);
	      double * uptr;
	      double * uptrRow;
	      double * vptr;
	      double * vptrRow = MRAWDATA(VT);
       
	      double * spptr;
       
	      for( unsigned int i=0;i<NC;++i )
		{
		  uptrRow = MRAWDATA(U);
		  for( unsigned int j=0;j<NR;++j )
		    {
		      uptr = uptrRow;  vptr = vptrRow; 
		      spptr = VRAWDATA( sp );
		      for( unsigned int k=0;k<rankJ;++k )
			{
			  (*pinv) += (*vptr) * (*spptr) * (*uptr);
			  uptr+=NR; vptr++; spptr++;
			}
		      pinv++; uptrRow++; 
		    }
		  vptrRow += NC;
		}
	    }
	    if( toTranspose )
	      {
		invMatrix.matrix = trans(invMatrix.matrix);  
		if( Uref ) Uref->matrix = VT;
		if( Vref ) Vref->matrix = trans(U);
		if( Sref ) Sref->vector=s; 
	      }
	    else
	      {
		if( Uref ) Uref->matrix = U;
		if( Vref ) Vref->matrix = trans(VT);
		if( Sref )  Sref->vector=s; 
	      }
	    return invMatrix;
	  }


	  inline Matrix dampedInverse( const FloatType threshold = 1e-6,
				       Matrix* U = NULL,
				       Vector* S = NULL,
				       Matrix* V = NULL)  const 
	  { Matrix Ainv(matrix.size2(),matrix.size1()); return dampedInverse(Ainv,threshold,U,S,V); }

      



	  /** \brief Compute the opposite of the matrix -M. */
	  inline Matrix& opposite( Matrix& res ) const  
	  { res.matrix=matrix; res.matrix *=-1; return res; }
	  /** \brief Compute the opposite of the matrix -M. */
	  inline Matrix opposite( void ) const  
	  { Matrix res;  opposite(res); return res; }

	  //@}

	  /* ----------------------- */
	  /* --- OPERATOR ExE->E --- */
	  /* ----------------------- */

	  /** @name Operator Functions ExE->E 
	   *
	   * Each C-style function is implemented as a C++ operator.
	   */
	  //@{
      
	  // Multiplication <Matrix> x <Matrix>
	  inline friend Matrix& multiply( const Matrix& A,const Matrix& B,Matrix& C )
	  { return A.multiply(B,C);    }
	  inline Matrix multiply( const Matrix& B ) const 
	  {  Matrix C(matrix.size1(),B.matrix.size2()); return this->multiply(B,C); }
	  inline Matrix& multiply( const Matrix& B,Matrix& C ) const 
	  { 
	    MAAL_CHECKVERBOSE(_checksizeProd(matrix,B.matrix)); 
	    _resizeProd(C.matrix,matrix,B.matrix);
	    prod(matrix,B.matrix,C.matrix); return C; 
	  }


	  // Multiplication <Matrix> x <Vector>
	  friend inline Vector& multiply( const Matrix& M, const Vector& v, Vector& res ) 
	  {  return M.multiply(v,res); }
	  inline Vector multiply( const Vector& v ) const 
	  {  Vector res(matrix.size1()); return this->multiply(v,res); }
	  inline Vector& multiply(  const Vector& v, Vector& res ) const 
	  {
	    MAAL_CHECKVERBOSE(_checksizeProd(matrix,v.vector));
	    //_resizeProd(matrix,res.vector); prod(matrix,v.vector,res.vector);
	    res.vector=prod(matrix,v.vector); // So stupid ...
	    return res;
	  }

    
	  // Addition 
	  inline friend Matrix& addition( const Matrix& A,const Matrix& B,Matrix& C )
	  { return A.addition(B,C);     }
	  inline Matrix addition( const Matrix& B ) const 
	  {  Matrix C(matrix.size1(),matrix.size2()); return addition(B,C);}
	  inline Matrix&	addition( const Matrix& B,Matrix& C ) const 
	  { 
	    MAAL_CHECKVERBOSE(_checksize(matrix,B.matrix));
	    //_resize(matrix,C.matrix); sum(matrix,v.vector,res.vector);
	    C.matrix=matrix; C.matrix+=B.matrix; return C; 
	  }

	  // Substraction 
	  inline friend Matrix& substraction( const Matrix& A,const Matrix& B,Matrix& C )
	  { return A.substraction(B,C); }
	  inline Matrix substraction( const Matrix& B ) const 
	  { Matrix C(matrix.size1(),matrix.size2()); return substraction(B,C); }
	  inline Matrix& substraction( const Matrix& B,Matrix& C ) const 
	  { 
	    MAAL_CHECKVERBOSE(_checksize(matrix,B.matrix));
	    //_resize(matrix,C.matrix); diff(matrix,v.vector,res.vector);
	    C.matrix=matrix; C.matrix-=B.matrix; return C; 
	  }
     
	  // With real

	  // Multiplication <Matrix> x <Float>
	  inline friend Matrix& multiply( const Matrix& A,const FloatType x,Matrix& C )
	  { return A.multiply(x,C); }
	  inline Matrix multiply( const FloatType x ) const 
	  { Matrix C(matrix.size1(),matrix.size2()); this->multiply(x,C); return C;}
	  inline Matrix& multiply( const FloatType x,Matrix& C ) const 
	  { 
	    //_resize(matrix,C.matrix); multiply(matrix,x,C.matrix);
	    C.matrix = matrix; C.matrix*=x; return C; 
	  }

	  // Addition <Matrix> x <Float>
	  inline friend Matrix& addition( const Matrix& A,const FloatType x,Matrix& C )
	  { return A.addition(x,C);}
	  inline Matrix addition( const FloatType x ) const 
	  {  Matrix C(matrix.size1(),matrix.size2()); return this->addition(x,C); }
	  inline Matrix& addition( const FloatType x,Matrix& C ) const 
	  { 
	    //_resize(C.matrix,matrix); 
	    C.matrix=matrix;
	    for(unsigned int i=0;i<matrix.size1();i++) 
	      {for(unsigned int j=0;j<matrix.size2();j++)
		  C.matrix(i,j) += x;
	      }
	    return C; 
	  }

	  // Substraction <Matrix> x <Float>
	  inline friend Matrix& substraction( const Matrix& A,const FloatType x,Matrix& C ) 
	  { return A.substraction(x,C);  }
	  inline Matrix substraction( const FloatType x ) const 
	  {  Matrix C(matrix.size1(),matrix.size2()); return substraction(x,C); }
	  inline Matrix& substraction( const FloatType x,Matrix& C ) const 
	  { 
	    //_resize(C.matrix,matrix);
	    C.matrix = matrix;
	    for(unsigned int i=0;i<matrix.size1();i++) 
	      {for(unsigned int j=0;j<matrix.size2();j++)
		  C.matrix(i,j) -= x;
	      }
	    return C; 
	  }

	  // Division <Matrix> x <Float>
	  inline friend Matrix& division( const Matrix& A,const FloatType x,Matrix& C ) 
	  { return A.division(x,C);}
	  inline Matrix division( const FloatType x ) const 
	  {  Matrix C(matrix.size1(),matrix.size2()); return division(x,C);}
	  inline Matrix& division( const FloatType x,Matrix& C ) const 
	  { 
	    //_resize(C.matrix,matrix);
	    C.matrix = matrix;
	    for(unsigned int i=0;i<matrix.size1();i++) 
	      {for(unsigned int j=0;j<matrix.size2();j++)
		  //C.matrix(i,j) = matrix(i,j) / x;
		  C.matrix(i,j) /= x;
	      }
	    return C; 
	  }

	  //@}

	  /* ------------------- */
	  /* --- DATA ACCESS --- */
	  /* ------------------- */
      
	  /** @name Accessors
	   *
	   * Access to an element, a block of element or the hidden double-array matrix.
	   */
	  //@{

	  inline FloatType* 
	    datablock( void )
	  {
	    return MRAWDATA(matrix);
	  }
	  inline const FloatType* 
	    datablock( void ) const
	  {
	    return MRAWDATA(matrix);
	  }

	  inline Matrix& 
	    extract( const int top,const int left, 
		     const int nbrows, const int nbcols,
		     Matrix& C ) //const 
	  { 
	    MAAL_CHECKVERBOSE(_checksize(matrix,top+nbrows,left+nbcols));
	    ::boost::numeric::ublas::matrix_slice< ::boost::numeric::ublas::matrix<FloatType> >
		amatrix(matrix,::boost::numeric::ublas::slice(top,1,nbrows),
			::boost::numeric::ublas::slice(left,1,nbcols)); 
	    C.matrix = amatrix;
	    return C;
	  }
	  inline Matrix
	    extract( const int top,const int left, 
		     const int nbrows, const int nbcols ) //const
	  { Matrix C(nbrows,nbcols); return extract(top,left,nbrows,nbcols,C); }



	  inline const FloatType& elementAt( const int row,const int col ) const
	  {
	    MAAL_CHECKVERBOSE(_checksize( matrix,row,col ));
	    return matrix(row,col);
	  }
	  inline FloatType& elementAt( const int row,const int col )
	  {
	    MAAL_CHECKVERBOSE(_checksize( matrix,row,col ));
	    return matrix(row,col);
	  }
	  inline const FloatType& elementAt( const int elmt ) const
	  {
	    const int l =  matrix.size1();
	    const div_t q = div(elmt,l); 
	    const int r = q.quot;
	    const int c = q.rem; 
	    return elementAt(r,c);
	  }
	  inline FloatType& elementAt( const int elmt ) 
	  {
	    const int l =  matrix.size1();
	    const div_t q = div(elmt,l); 
	    const int r = q.quot;
	    const int c = q.rem; 
	    return elementAt(r,c);
	  }
      
	  //@}

	  /* ------------- */
	  /* --- BONUS --- */
	  /* ------------- */

	  /** @name Bonus 
	   *
	   * Additional functions, not implemented yet.
	   */
	  //@{
 
	  inline Vector getDiagonal( void ) const  
	  { Vector res; getDiagonal(res); return res; }
	  inline Vector& getDiagonal( Vector& vector ) const  
	  {
	    const unsigned int MIN = std::min(  matrix.size1(),matrix.size2() );
	    vector.resize( MIN );
	    for( unsigned int i=0;i<MIN;++i )
	      vector(i) = matrix(i,i);
	    return vector;
	  }
 
	  inline Matrix& setDiagonal( const Vector& vector )
	  { 
	    const unsigned int SIZE = vector.size() ;
	    matrix.resize( SIZE,SIZE ); fill(0.);
	    for( unsigned int i=0;i<SIZE;++i )
	      {
		matrix(i,i)=vector(i);
	      }
	    return *this;
	  }
 
	  inline Matrix& stackMatrix( const Matrix& B,Matrix& C )  const 
	  { ML_NOT_IMPLEMENTED(C) }
	  inline Matrix stackMatrix( const Matrix& B ) const 
	  { Matrix res; return stackMatrix(B,res); }

	  inline Matrix& juxtaposeMatrix( const Matrix& B,Matrix& C ) const 
	  { ML_NOT_IMPLEMENTED(C) }
	  inline Matrix juxtaposeMatrix( const Matrix& B ) const 
	  { Matrix res; return juxtaposeMatrix(B,res); }
      
	  //@}

	  /* ----------------- */
	  /* --- OPERATORS --- */
	  /* ----------------- */
   
	  /** @name Operators 
	   *
	   * Classical operators: use v1 + v2 for addition, v1(i) for i-th element...
	   */
	  //@{

	  inline friend Matrix operator+ ( const Matrix&m1,const Matrix&m2 ){ return m1.addition(m2); }
	  inline friend Matrix operator- ( const Matrix&m1,const Matrix&m2 ){ return m1.substraction(m2);}
	  inline friend Matrix operator* ( const Matrix&m1,const Matrix&m2 ){ return m1.multiply(m2);}
      
	  inline Matrix& operator+= ( const Matrix&m1 ){ matrix+=m1.matrix;return *this; }
	  inline Matrix& operator-= ( const Matrix&m1 ){ matrix-=m1.matrix;return *this; }
	  inline Matrix& operator*= ( const Matrix&m1 ){ return this->multiply(m1,*this); }
	  //{ matrix*=m1.matrix;return *this; }
	  inline Matrix& operator*= ( const FloatType x ){ matrix*=x;return *this; }

	  inline friend Matrix operator- ( const Matrix& m ){ return m.opposite(); }
	  //{ return multiply(*this,x,*this); }
      
	  inline const FloatType& operator()( const int i,const int j )const { return matrix(i,j); }
	  inline FloatType& operator()( const int i,const int j ){ return matrix(i,j); }
	  inline const FloatType& operator()( const int n )const { return elementAt(n); }
	  inline FloatType& operator()( const int n ) { return elementAt(n); }
      
	  inline Matrix& operator= ( const Matrix&m1 ){ matrix=m1.matrix; return *this;}
 
	  inline friend Vector operator* ( const Matrix& M,const Vector& v1 ){ return M.multiply(v1); }    
	  inline friend Vector operator* ( const Vector& v1,const Matrix& M ){ return M.multiply(v1); }
      
	  inline friend Matrix operator+ ( const FloatType x,const Matrix&m1 ){ return m1.addition(x); }
	  inline friend Matrix operator- ( const FloatType x,const Matrix&m1 ){ return m1.substraction(x); }
	  inline friend Matrix operator* ( const FloatType x,const Matrix&m1 ){ return m1.multiply(x); }
	  inline friend Matrix operator/ ( const FloatType x,const Matrix&m1 ){ return m1.division(x); }

	  inline friend Matrix operator+ ( const Matrix&m1,const FloatType x ){ return m1.addition(x); }
	  inline friend Matrix operator- ( const Matrix&m1,const FloatType x ){ return m1.substraction(x); }
	  inline friend Matrix operator* ( const Matrix&m1,const FloatType x ){ return m1.multiply(x); }
	  inline friend Matrix operator/ ( const Matrix&m1,const FloatType x ){ return m1.division(x); }


	  inline friend std::ostream& operator<< ( std::ostream& os,const Matrix& m1 )
	    {
	      switch( getDisplayType() )
		{
		case SIMPLE:
		  return os<<m1.matrix; 
		case COMPLET:
		  for( unsigned int i=0;i<m1.nbRows();++i ) 
		    {
		      for( unsigned int j=0;j<m1.nbCols();++j )
			{ if(fabs(m1(i,j))>1e-6) os << m1(i,j) << "\t"; else os<<0.00<<"\t"; } 
		      os<<std::endl;
		    }
		  return os;
		case MATLAB:
		  os << "[ ";
		  for( unsigned int i=0;i<m1.nbRows();++i )
		    {
		      for( unsigned int j=0;j<m1.nbCols();++j )
			{
			  os <<  m1(i,j) << ", ";
			}
		      if( m1.nbRows()!=i+1 ) { os << ";" << std::endl; }
		      else { os << "]" << std::endl; }
		    }
		  return os;
		default:
		  ML_NOT_IMPLEMENTED(os);
		}
	    }
	  inline friend std::istream& operator>> ( std::istream& is,Matrix& v1 ){ return is>>v1.matrix; }


	  //@}

	  friend class Vector;

	  /* ------------------------------------------------------------------ */
	  /* ------------------------------------------------------------------ */
	  /* ------------------------------------------------------------------ */

	  /** @name Autoresize internal */
	  //@{

	public: 
	  bool autoresize( void ) { return AUTORESIZE; }
	protected:
	  static inline void _resize( InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { if(AUTORESIZE) { mat1.resize( mat2.size1(),mat2.size2() ); } }

	  static inline bool _checksize( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.size1()==mat2.size1()) && (mat1.size2()==mat2.size2()) ) ); }
	  static inline bool _checksizeVerb( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.size1()==mat2.size1()) && (mat1.size2()==mat2.size2()) ) )
	      return true;
	    else
	      {
		fprintf(stderr,"!!\tmaal::Matrix: error in matrix size.\n"); fflush(stderr);
		return false;
	      }
	  }
	  static inline bool _checksize( const InternalMatrix& mat1,
					 const unsigned int s1,const unsigned int s2 )
	  { return ( (!CHECKRESIZE)
		     ||( (mat1.size1()>s1)&&(mat1.size2()>s2) ) ); }
	  static inline bool _checksizeVerb( const InternalMatrix& mat1,
					     const unsigned int s1,const unsigned int s2)
	  {
	    if ( (!CHECKRESIZE)
		 ||( (mat1.size1()>s1)&&(mat1.size2()>s2) ) )
	      return true;
	    else {
	      fprintf(stderr,"!!\tmaal::Matrix: error in matrix size for access.\n"); fflush(stderr);
	      return false;
	    }
	  }
	  static inline bool _checksizeProd( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.size2()==mat2.size1()) ) ); }
	  static inline bool _checksizeProdVerb( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.size2()==mat2.size1())  ) )
	      return true;
	    else
	      {
		fprintf(stderr,"!!\tmaal::Matrix: error in matrix size for product [%dx%d] x [%dx%d].\n",
			mat1.size1(),mat1.size2(),mat2.size1(),mat2.size2()); fflush(stderr);
		return false;
	      }
	  }
	  static inline void _resizeProd( InternalMatrix& res,const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { if(AUTORESIZE) { res.resize( mat1.size1(),mat2.size2() ); } }

	  static inline bool _checksizeProd( const InternalMatrix& mat1,const Vector::InternalVector& vct )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.size2()==vct.size()) ) ); }
	  static inline bool _checksizeProdVerb( const InternalMatrix& mat1,const Vector::InternalVector& vct )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.size2()==vct.size())  ) )
	      return true;
	    else
	      {
		fprintf(stderr,"!!\tmaal::Matrix: error in matrix size for product.\n"); fflush(stderr);
		return false;
	      }
	  }
	  static inline void _resizeProd( Vector::InternalVector& res,const InternalMatrix& mat1 )
	  { if(AUTORESIZE) { res.resize( mat1.size1() ); } }


	  static inline void _resizeInv( InternalMatrix& res,const InternalMatrix& mat2 )
	  { if(AUTORESIZE) { res.resize( mat2.size2(),mat2.size1() ); } }

	  static inline bool _checksizeSquare( const InternalMatrix& mat1 )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.size1()==mat1.size2()) ) ); }
	  static inline bool _checksizeSquareVerb( const InternalMatrix& mat1 )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.size2()==mat1.size1())  ) )
	      return true;
	    else
	      {
		fprintf(stderr,"!!\tmaal::Matrix: error matrix non square.\n"); fflush(stderr);
		return false;
	      }
	  }

	  //@}

	};

    }}





#endif // #ifndef __MAAL_BOOST_MATRIX_

