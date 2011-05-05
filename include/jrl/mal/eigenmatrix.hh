/*
 * Copyright 2011,
 *
 * Maxime Reis
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
 *
 */

#ifndef __MAAL_EIGEN_MATRIX_
# define __MAAL_EIGEN_MATRIX_
# include <cstdio>
# include <jrl/mal/eigenmacros.hh>
# include <jrl/mal/eigensvd.hh>

/**
 * \file eigenMatrix.h Define maal::eigen::Matrix
 */

namespace maal
{
  namespace eigen
    {


      /* --- MATRIX --------------------------------------------------------- */
      /* --- MATRIX --------------------------------------------------------- */
      /* --- MATRIX --------------------------------------------------------- */

      /** \brief Matrix class that include the Eigen::Matrix.
       *
       * The class encapsulates the Eigen::Matrix object, and implement
       * a set of standard functions.
       * When the maal::eigen::Matrix object is constructed, it automatically
       * builds the internal Eigen::Matrix object. The internal object can be
       * access through accessToMotherLib. Finally, it is possible to
       * build the capsule around an existing eigen Eigen::Matrix through the
       * appropriate constructor.
       *
       */

      class Matrix
	{

	public://protected:
	  typedef ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic> InternalMatrix;
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
	   * eigen matrix object.
	   */
	Matrix( InternalMatrix* clone,const bool proprio=false )
	  : staticMatrix(0,0),dynamicMatrix( clone ),matrix(*dynamicMatrix)
	    ,proprio(proprio)
	  {}

	  /** \brief Build a new internal matrix from existing
	   * eigen matrix object by copying the data.
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

	  /** \brief Access to the eigen internal matrix. */
	  InternalMatrix& accessToMotherLib( void ) { return matrix; }
	  /** \brief Access to the eigen internal matrix. */
	  const InternalMatrix& accessToMotherLib( void ) const { return matrix; }
	  /** \brief Copy the values and data of an existing
	   * eigen matrix. */
	  Matrix & initFromMotherLib( const InternalMatrix& bv )
	    { matrix = bv; return *this;}
	  //@}

	public:

	  /** @name Modifiors */
	  //@{

	  inline Matrix& resize( const unsigned int nbRows,
				 const unsigned int nbCols,const bool setZero=true )
	  {
	    setZero?matrix.resize(nbRows,nbCols):matrix.conservativeResize(nbRows,nbCols);
            return *this;
	  }

	  /** \brief Get the number of rows. */
	  inline unsigned int nbRows( void ) const { return (unsigned)matrix.rows();}
	  /** \brief Get the number of columns. */
	  inline unsigned int nbCols( void ) const { return (unsigned)matrix.cols();}

	  inline Matrix& setZero( void )
          {
            FloatType* rawMatrix = MRAWDATA(matrix);
            for(int i=0; i<matrix.cols()*matrix.rows(); i++){ rawMatrix[i] = 0; }
            return *this;
          }
	  inline Matrix& setIdentity( void  )
	  {
            //matrix.setIdentity(matrix.rows(), matrix.cols()); /* slower than what follows */
            FloatType* rawMatrix = MRAWDATA(matrix);
            for(int i=0; i<matrix.cols()*matrix.rows(); i++){ rawMatrix[i] = 0; }
            for(int i=0; i<std::min(matrix.cols(), matrix.rows()); i++){ matrix(i,i) = 1; }
	    return *this;
	  }

	  inline Matrix& fill( const FloatType value )
	  {
            FloatType* rawMatrix = MRAWDATA(matrix);
            for(int i=0; i<matrix.cols()*matrix.rows(); i++){ rawMatrix[i] = value; }
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
	    if(! _checksizeSquareVerb( matrix ) )
              return -1;
            return matrix.determinant();
	  }


	  inline FloatType
	    trace( void ) const
	  {
            return matrix.trace();
	  }

	  /** \brief Not implemented yet. */
	  inline FloatType norm( void ) const {  ML_NOT_IMPLEMENTED(0) }
	  /** \brief Norm 1 sum( |xi| )  */
	  inline FloatType norm1( void ) const
          {
            FloatType* rawMatrix = MRAWDATA(matrix);
            FloatType norm1_ = 0;
            for(int i=0; i<matrix.rows()*matrix.cols(); i++){ norm1_+=fabs(rawMatrix[i]); }
            return norm1_;
          }
	  inline FloatType normInfty( void ) const { return matrix.lpNorm<Eigen::Infinity>(); }
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
            At.matrix = matrix.transpose();
            return At;
	  }
	  inline Matrix transpose( void )  const
	  {
	    Matrix At(matrix.cols(),matrix.rows()); return transpose(At);
	  }

	  /** \brief Compute the inverse of the matrix.
	   *
	   * The matrix has to be invertible.
	   */
	  inline Matrix&
	    inverse( Matrix& invMatrix ) const
	  {
	    _resizeInv(invMatrix.matrix,matrix);
            invMatrix.matrix = matrix.inverse();
            return invMatrix;
	  }

	  inline Matrix inverse( void )  const
	  { Matrix Ainv(matrix.cols(),matrix.rows()); return inverse(Ainv); }


	  /** \brief Compute the pseudo-inverse of the matrix.
	   *
	   * By default, the function uses the dgesvd_ fortran routine.
	   * It should be provided by the host software.
           * The SVD provided by Eigen is waaaaaay to slow to be used here
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
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> I;
	    if( matrix.rows()>matrix.cols() )
	      {
		toTranspose=false ;  NR=matrix.rows(); NC=matrix.cols();
		I=matrix;
		_resizeInv(invMatrix.matrix,I);
	      }
	    else
	      {
		toTranspose=true; NR=matrix.cols(); NC=matrix.rows();
		I = matrix.transpose();
		_resizeInv(invMatrix.matrix,I); // Resize the inv of the transpose.
	      }

            ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> U(NR,NR);
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> VT(NC,NC);
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, 1, Eigen::ColMajor> s(std::min(NR,NC));
	    char Jobu='A'; // Compute complete U Matrix
	    char Jobvt='A'; // Compute complete VT Matrix
	    char Lw; Lw='O'; // Compute the optimal size for the working vector


	    {
	      double vw;
	      int lw=-1;

	      int linfo; const int n=NR,m=NC;
	      int lda = std::max(n,m);;
	      int lu = NR;
	      int lvt = NC;

	      dgesvd_(&Jobu, &Jobvt, &m, &n,
		      MRAWDATA(I), &lda,
		      0, 0, &m, 0, &n, &vw, &lw, &linfo);
	      lw = int(vw)+5;

              ::Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::ColMajor> w(lw);
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
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, 1> sp(nsv);
	    for( unsigned int i=0;i<nsv;++i )
	      if( fabs(s(i))>threshold ) { sp(i)=1/s(i); rankJ++; }
	      else sp(i)=0.;
	    invMatrix.setZero();
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
		invMatrix.matrix.transposeInPlace();
		if( Uref ) Uref->matrix = VT;
		if( Vref ) Vref->matrix = U.transpose();
		if( Sref ) Sref->vector=s;
	      }
	    else
	      {
		if( Uref ) Uref->matrix = U;
		if( Vref ) Vref->matrix = VT.transpose();
		if( Sref ) Sref->vector=s;
	      }
	    return invMatrix;
	  }

	  inline Matrix pseudoInverse( const FloatType threshold = 1e-6,
				       Matrix* U = NULL,
				       Vector* S = NULL,
				       Matrix* V = NULL)  const
	  { Matrix Ainv(matrix.cols(),matrix.rows()); return pseudoInverse(Ainv,threshold,U,S,V); }




	  /* \brief Compute the pseudo-inverse of the matrix.
           *
           * Uses Eigen SVD decomposition, which is slower than an old tetraplegic snail. Use the dgesvd_ method above instead.
           */
	  virtual Matrix&
	    pseudoInverseEigenSVD( Matrix& invMatrix,
			   const FloatType threshold = 1e-6,
			   Matrix* Uref = NULL,
			   Vector* Sref = NULL,
			   Matrix* Vref = NULL)  const 
	  {
	    unsigned int NR, NC;
	    bool toTranspose;
            Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic> I;
	    if( matrix.rows()>matrix.cols() )
	      {
		toTranspose=false ;  NR=matrix.rows(); NC=matrix.cols();
		I = matrix;
	      }
	    else
	      {
		toTranspose=true; NR=matrix.cols(); NC=matrix.rows();
		I = matrix.transpose();
	      }

            _resizeInv(invMatrix.matrix,I);
            Eigen::JacobiSVD< Eigen::Matrix< FloatType, Eigen::Dynamic, Eigen::Dynamic > > svd(I, Eigen::ComputeThinU | Eigen::ComputeThinV);
            Eigen::Matrix< FloatType, Eigen::Dynamic, Eigen::Dynamic > U(svd.matrixU()),
                                                                       V(svd.matrixV());
            Eigen::Matrix< FloatType, Eigen::Dynamic, 1 > S(svd.singularValues()),
                                                          invS(S.size());
            for(int i=0; i<S.size(); i++) { invS(i) = (fabs(S(i))>threshold?1/S(i):0); }
            invMatrix.matrix = V * invS.asDiagonal() * U.transpose();       
	    if( toTranspose )
	      {
		invMatrix.matrix.transposeInPlace();
		if( Uref ) Uref->matrix = V.transpose();
		if( Vref ) Vref->matrix = U.transpose();
	      }
	    else
	      {
		if( Uref ) Uref->matrix = U;
		if( Vref ) Vref->matrix = V;
	      }
		if( Sref ) Sref->vector = S;
	    return invMatrix;
	  }


	  inline Matrix pseudoInverseEigenSVD( const FloatType threshold = 1e-6,
				       Matrix* U = NULL,
				       Vector* S = NULL,
				       Matrix* V = NULL)  const
	  { Matrix Ainv(matrix.cols(),matrix.rows()); return pseudoInverseEigenSVD(Ainv,threshold,U,S,V); }





	  /** \brief Compute the pseudo-inverse of the matrix.
	   *
	   * By default, the function uses the dgesvd_ fortran routine.
	   * It should be provided by the host software.
           * The SVD provided by Eigen is still to slow to be used here
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
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> I;
	    if( matrix.rows()>matrix.cols() )
	      {
		toTranspose=false ;  NR=matrix.rows(); NC=matrix.cols();
		I=matrix;
		_resizeInv(invMatrix.matrix,I);
	      }
	    else
	      {
		toTranspose=true; NR=matrix.cols(); NC=matrix.rows();
		I = matrix.transpose();
		_resizeInv(invMatrix.matrix,I); // Resize the inv of the transpose.
	      }

            ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> U(NR,NR);
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> VT(NC,NC);
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, 1, Eigen::ColMajor> s(std::min(NR,NC));
	    char Jobu='A'; // Compute complete U Matrix
	    char Jobvt='A'; // Compute complete VT Matrix
	    char Lw; Lw='O'; // Compute the optimal size for the working vector


	    {
	      double vw;
	      int lw=-1;

	      int linfo; const int n=NR,m=NC;
	      int lda = std::max(n,m);;
	      int lu = NR;
	      int lvt = NC;

	      dgesvd_(&Jobu, &Jobvt, &m, &n,
		      MRAWDATA(I), &lda,
		      0, 0, &m, 0, &n, &vw, &lw, &linfo);
	      lw = int(vw)+5;

              ::Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::ColMajor> w(lw);
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
            ::Eigen::Matrix<FloatType, Eigen::Dynamic, 1> sp(nsv);
	    for( unsigned int i=0;i<nsv;++i )
	      if( fabs(s(i))>threshold ) { sp(i)=1/(s(i)*s(i)+threshold*threshold); rankJ++; }
	      else sp(i)=0.;
	    invMatrix.setZero();
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
		invMatrix.matrix.transposeInPlace();
		if( Uref ) Uref->matrix = VT;
		if( Vref ) Vref->matrix = U.transpose();
		if( Sref ) Sref->vector=s;
	      }
	    else
	      {
		if( Uref ) Uref->matrix = U;
		if( Vref ) Vref->matrix = VT.transpose();
		if( Sref ) Sref->vector=s;
	      }
	    return invMatrix;
	  }

	  inline Matrix dampedInverse( const FloatType threshold = 1e-6,
				       Matrix* U = NULL,
				       Vector* S = NULL,
				       Matrix* V = NULL)  const
	  { Matrix Ainv(matrix.cols(),matrix.rows()); return dampedInverse(Ainv,threshold,U,S,V); }






	  /* \brief Compute the damped pseudo-inverse of the matrix.
           *
           * Also uses Eigen SVD decomposition, which is still not good at all.
           */
	  virtual Matrix&
	    dampedInverseEigenSVD( Matrix& invMatrix,
			   const FloatType threshold = 1e-6,
			   Matrix* Uref = NULL,
			   Vector* Sref = NULL,
			   Matrix* Vref = NULL)  const 
	  {
	    unsigned int NR, NC;
	    bool toTranspose;
            Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic> I;
	    if( matrix.rows()>matrix.cols() )
	      {
		toTranspose=false ;  NR=matrix.rows(); NC=matrix.cols();
		I = matrix;
	      }
	    else
	      {
		toTranspose=true; NR=matrix.cols(); NC=matrix.rows();
		I = matrix.transpose();
	      }

            _resizeInv(invMatrix.matrix,I);
            Eigen::JacobiSVD< Eigen::Matrix< FloatType, Eigen::Dynamic, Eigen::Dynamic > > svd(I, Eigen::ComputeFullU | Eigen::ComputeFullV);
            Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic> U(svd.matrixU()),
                                                                     V(svd.matrixV());
            Eigen::Matrix<FloatType, Eigen::Dynamic, 1> S(svd.singularValues()),
                                                        invS(S.size());
            for(int i=0; i<S.size(); i++) { invS(i) = (fabs(S(i))>threshold?(S(i)/(S(i)*S(i)+threshold*threshold)):0); }
            invMatrix.matrix = V * invS.asDiagonal() * U.transpose();       
	    if( toTranspose )
	      {
		invMatrix.matrix.transposeInPlace();
		if( Uref ) Uref->matrix = V.transpose();
		if( Vref ) Vref->matrix = U.transpose();
	      }
	    else
	      {
		if( Uref ) Uref->matrix = U;
		if( Vref ) Vref->matrix = V;
	      }
		if( Sref ) Sref->vector = S;
	    return invMatrix;
	  }


	  inline Matrix dampedInverseEigenSVD( const FloatType threshold = 1e-6,
				       Matrix* U = NULL,
				       Vector* S = NULL,
				       Matrix* V = NULL)  const
	  { Matrix Ainv(matrix.cols(),matrix.rows()); return dampedInverseEigenSVD(Ainv,threshold,U,S,V); }



	  /** \brief Compute the opposite of the matrix -M. */
	  inline Matrix& opposite( Matrix& res ) const
	  { res.matrix = -1*matrix; return res; }
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
	  {  Matrix C(matrix.rows(),B.matrix.cols()); return this->multiply(B,C); }
	  inline Matrix& multiply( const Matrix& B,Matrix& C ) const
	  {
	    MAAL_CHECKVERBOSE(_checksizeProd(matrix,B.matrix));
//	    _resizeProd(C.matrix,matrix,B.matrix);
            C.matrix = matrix*B.matrix;
            return C;
	  }


	  // Multiplication <Matrix> x <Vector>
	  friend inline Vector& multiply( const Matrix& M, const Vector& v, Vector& res )
	  {  return M.multiply(v,res); }
	  inline Vector multiply( const Vector& v ) const
	  {  Vector res(matrix.rows()); return this->multiply(v,res); }
	  inline Vector& multiply(  const Vector& v, Vector& res ) const
	  {
	    MAAL_CHECKVERBOSE(_checksizeProd(matrix,v.vector));
            res.vector = matrix*v.vector;
	    return res;
	  }


	  // Addition
	  inline friend Matrix& addition( const Matrix& A,const Matrix& B,Matrix& C )
	  { return A.addition(B,C);     }
	  inline Matrix addition( const Matrix& B ) const
	  {  Matrix C(matrix.rows(),matrix.cols()); return addition(B,C);}
	  inline Matrix&	addition( const Matrix& B,Matrix& C ) const
	  {
	    MAAL_CHECKVERBOSE(_checksize(matrix,B.matrix));
	    C.matrix = matrix + B.matrix;
            return C;
	  }

	  // Substraction
	  inline friend Matrix& substraction( const Matrix& A,const Matrix& B,Matrix& C )
	  { return A.substraction(B,C); }
	  inline Matrix substraction( const Matrix& B ) const
	  { Matrix C(matrix.rows(),matrix.cols()); return substraction(B,C); }
	  inline Matrix& substraction( const Matrix& B,Matrix& C ) const
	  {
	    MAAL_CHECKVERBOSE(_checksize(matrix,B.matrix));
	    C.matrix = matrix - B.matrix;
            return C;
	  }

	  // With real

	  // Multiplication <Matrix> x <Float>
	  inline friend Matrix& multiply( const Matrix& A,const FloatType x,Matrix& C )
	  { return A.multiply(x,C); }
	  inline Matrix multiply( const FloatType x ) const
	  { Matrix C(matrix.rows(),matrix.cols()); this->multiply(x,C); return C;}
	  inline Matrix& multiply( const FloatType x,Matrix& C ) const
	  {
	    C.matrix = matrix*x;
            return C;
	  }

	  // Addition <Matrix> x <Float>
	  inline friend Matrix& addition( const Matrix& A,const FloatType x,Matrix& C )
	  { return A.addition(x,C);}
	  inline Matrix addition( const FloatType x ) const
	  {  Matrix C(matrix.rows(),matrix.cols()); return this->addition(x,C); }
	  inline Matrix& addition( const FloatType x,Matrix& C ) const
	  {
	    C.matrix=matrix;
            FloatType* rawMatrix = MRAWDATA(C.matrix);
	    for(int i=0;i<matrix.rows()*matrix.cols();i++){ rawMatrix[i] += x; }
	    return C;
	  }

	  // Substraction <Matrix> x <Float>
	  inline friend Matrix& substraction( const Matrix& A,const FloatType x,Matrix& C )
	  { return A.substraction(x,C);  }
	  inline Matrix substraction( const FloatType x ) const
	  {  Matrix C(matrix.rows(),matrix.cols()); return substraction(x,C); }
	  inline Matrix& substraction( const FloatType x,Matrix& C ) const
	  {
	    C.matrix = matrix;
            FloatType* rawMatrix = MRAWDATA(C.matrix);
	    for(int i=0;i<matrix.rows()*matrix.cols();i++){ rawMatrix[i] -= x; }
	    return C;
	  }

	  // Division <Matrix> x <Float>
	  inline friend Matrix& division( const Matrix& A,const FloatType x,Matrix& C )
	  { return A.division(x,C);}
	  inline Matrix division( const FloatType x ) const
	  {  Matrix C(matrix.rows(),matrix.cols()); return division(x,C);}
	  inline Matrix& division( const FloatType x,Matrix& C ) const
	  {
	    C.matrix = matrix/x;
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
		     Matrix& C ) const
	  {
	    MAAL_CHECKVERBOSE(_checksize(matrix,top+nbrows-1,left+nbcols-1));
            C.matrix = matrix.block(top, left, nbrows, nbcols);
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
            /*
	    const int l =  matrix.rows();
	    const div_t q = div(elmt,l);
	    const int r = q.quot;
	    const int c = q.rem;
	    return elementAt(r,c);
            */
            return MRAWDATA(matrix)[elmt];
	  }
	  inline FloatType& elementAt( const int elmt )
	  {
            /*
	    const int l =  matrix.rows();
	    const div_t q = div(elmt,l);
	    const int r = q.quot;
	    const int c = q.rem;
	    return elementAt(r,c);
            */
            return MRAWDATA(matrix)[elmt];
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
            vector.vector = matrix.diagonal();
	    return vector;
	  }

	  inline Matrix& setDiagonal( const Vector& vector )
	  {
	    const unsigned int SIZE = vector.size() ;
	    matrix.resize( SIZE,SIZE ); setZero();
	    for( unsigned int i=0;i<SIZE;++i )
	      {
		matrix(i,i)=vector(i);
	      }
	    return *this;
	  }

	  inline Matrix& stackMatrix(const Matrix&, Matrix& C) const
	  { ML_NOT_IMPLEMENTED(C) }
	  inline Matrix stackMatrix( const Matrix& B ) const
	  { Matrix res; return stackMatrix(B,res); }

	  inline Matrix& juxtaposeMatrix(const Matrix&, Matrix& C) const
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
		  for(unsigned int i=0;i<m1.nbRows();++i )
		    {
		      for(unsigned int j=0;j<m1.nbCols();++j )
			{ if(fabs(m1(i,j))>1e-6) os << m1(i,j) << "\t"; else os<<0.00<<"\t"; }
		      os<<std::endl;
		    }
		  return os;
		case MATLAB:
		  os << "[ ";
		  for(unsigned int i=0;i<m1.nbRows();++i )
		    {
		      for(unsigned int j=0;j<m1.nbCols();++j )
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
	    // inline friend std::istream& operator>> ( std::istream& is,Matrix& v1 ){ return is>>v1.matrix; }


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
	  { if(AUTORESIZE) { mat1.resize( mat2.rows(),mat2.cols() ); } }

	  static inline bool _checksize( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.rows()==mat2.rows()) && (mat1.cols()==mat2.cols()) ) ); }
	  static inline bool _checksizeVerb( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.rows()==mat2.rows()) && (mat1.cols()==mat2.cols()) ) )
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
		     ||( ((unsigned)mat1.rows()>s1)&&((unsigned)mat1.cols()>s2) ) ); }
	  static inline bool _checksizeVerb( const InternalMatrix& mat1,
					     const unsigned int s1,const unsigned int s2)
	  {
	    if ( (!CHECKRESIZE)
		 ||( ((unsigned)mat1.rows()>s1)&&((unsigned)mat1.cols()>s2) ) )
	      return true;
	    else {
	      fprintf(stderr,"!!\tmaal::Matrix: error in matrix size for access.\n"); fflush(stderr);
	      return false;
	    }
	  }
	  static inline bool _checksizeProd( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.cols()==mat2.rows()) ) ); }
	  static inline bool _checksizeProdVerb( const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.cols()==mat2.rows())  ) )
	      return true;
	    else
	      {
		fprintf(stderr,"!!\tmaal::Matrix: error in matrix size for product [%dx%d] x [%dx%d].\n",
			mat1.rows(),mat1.cols(),mat2.rows(),mat2.cols()); fflush(stderr);
		return false;
	      }
	  }
	  static inline void _resizeProd( InternalMatrix& res,const InternalMatrix& mat1,const InternalMatrix& mat2 )
	  { if(AUTORESIZE) { res.resize( mat1.rows(),mat2.cols() ); } }

	  static inline bool _checksizeProd( const InternalMatrix& mat1,const Vector::InternalVector& vct )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.cols()==vct.size()) ) ); }
	  static inline bool _checksizeProdVerb( const InternalMatrix& mat1,const Vector::InternalVector& vct )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.cols()==vct.size())  ) )
	      return true;
	    else
	      {
		fprintf(stderr,"!!\tmaal::Matrix: error in matrix size for product.\n"); fflush(stderr);
		return false;
	      }
	  }
	  static inline void _resizeProd( Vector::InternalVector& res,const InternalMatrix& mat1 )
	  { if(AUTORESIZE) { res.resize( mat1.rows() ); } }


	  static inline void _resizeInv( InternalMatrix& res,const InternalMatrix& mat2 )
	  { if(AUTORESIZE) { res.resize( mat2.cols(),mat2.rows() ); } }

	  static inline bool _checksizeSquare( const InternalMatrix& mat1 )
	  { return ( (!CHECKRESIZE)
		     || ( (mat1.rows()==mat1.cols()) ) ); }
	  static inline bool _checksizeSquareVerb( const InternalMatrix& mat1 )
	  {
	    if ( (!CHECKRESIZE)
		 || ( (mat1.cols()==mat1.rows())  ) )
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

#endif // #ifndef __MAAL_EIGEN_MATRIX_
