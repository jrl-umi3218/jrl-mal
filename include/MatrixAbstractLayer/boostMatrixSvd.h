/*
 * Copyright 2008, 2009, 2010,
 *
 * Paul Evrard,
 * Francois Keith,
 * Florent Lamiraux,
 * Nicolas Mansard
 * Olivier Stasse
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

#ifndef __MAAL_BOOST_MATRIX_SVD_
# define __MAAL_BOOST_MATRIX_SVD_

# include <MatrixAbstractLayer/boostMatrix.h>

/**
 * \file boostMatrixSvd.h Define maal::boost::MatrixSvd,
 * heritance from maal::boost:Matrix.
 */

namespace maal
{
  namespace boost
  {

    class MatrixSvd
      : public Matrix
    {

    protected:
      /* SVD memory. */
      mutable unsigned int nbrows,nbcols,nmajor,nminor;
      mutable bool toTranspose;

      mutable ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> McolMajor;
      mutable ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> U; //(NR,NR);
      mutable ::boost::numeric::ublas::matrix<FloatType,::boost::numeric::ublas::column_major> VT; //(NC,NC);
      mutable ::boost::numeric::ublas::vector<FloatType> s; //(std::min(NR,NC));
      mutable ::boost::numeric::ublas::vector<double> w;
      mutable ::boost::numeric::ublas::vector<FloatType> sp; //(nsv);
      mutable int lw; // = -1;
      mutable int lda,lu,lvt;
      mutable unsigned int rankJ;


    public: /* ---  Construction --- */
    MatrixSvd( const unsigned int rows=0, const unsigned int cols=0 )
      : Matrix( rows,cols ),nbrows(-1),nbcols(-1),toTranspose(false) {}

    MatrixSvd( InternalMatrix* clone,const bool proprio=false )
      : Matrix( clone,false  ),nbrows(-1),nbcols(-1),toTranspose(false)  {}

    MatrixSvd( const MatrixSvd& copy )
      : Matrix( copy ),nbrows(-1),nbcols(-1),toTranspose(false) {}


    protected: /* --- SVD --- */

      /* ---------------------------------------------------------------- */
      /* --- REVISE MEMORY ---------------------------------------------- */
      /* ---------------------------------------------------------------- */
      bool reviseMemory( void ) const
      {
	if( matrix.size1()>matrix.size2() )
	  { return (!( (toTranspose==false)&&(nbrows==matrix.size1())
		       &&(nbcols==matrix.size2()) )); }
	else
	  { return !( (toTranspose==true)&&(nbcols==matrix.size1())
		      &&(nbrows==matrix.size2()) ); }
      }

      /* ---------------------------------------------------------------- */
      /* --- INIT MEMORY ------------------------------------------------ */
      /* ---------------------------------------------------------------- */
      void initSvdMemory( void ) const
      {
	if(! reviseMemory() ) return; // Nothing to do

	if( matrix.size1()>matrix.size2() )
	  {
	    toTranspose=false ;  nbrows=matrix.size1(); nbcols=matrix.size2();
	    nmajor=nbrows; nminor=nbcols;
	    McolMajor=matrix;
	  }
	else
	  {
	    toTranspose=true; nbrows=matrix.size2(); nbcols=matrix.size1();
	    nmajor=nbrows; nminor=nbcols;
	    McolMajor=trans(matrix);
	  }
	U.resize(nbrows,nbrows);
	VT.resize(nbcols,nbcols);
	s.resize(nminor);

	char Jobu='A'; /* Compute complete U Matrix */
	char Jobvt='A'; /* Compute complete VT Matrix */

	/* Get workspace size for svd. */
	{
	  double vw;
	  int linfo;
	  const int n=nbrows,m=nbcols;
	  lda = std::max(m,n);
	  lw =-1;
	  dgesvd_(&Jobu, &Jobvt, &m, &n,
		  MRAWDATA(McolMajor), &lda,
		  0, 0, &m, 0, &n, &vw, &lw, &linfo);
	  lw = int(vw)+5;
	  w.resize(lw);
	}
	sp.resize(nminor);
      }


    public: /* --- SVD --- */

      /* ---------------------------------------------------------------- */
      /* ---------------------------------------------------------------- */
      /* ---------------------------------------------------------------- */
      using Matrix::pseudoInverse;
      using Matrix::dampedInverse;

      virtual Matrix&
	pseudoInverse( Matrix& invMatrix,
		       const FloatType threshold = 1e-6,
		       Matrix* Uref = NULL,
		       Vector* Sref = NULL,
		       Matrix* Vref = NULL)  const
      {
	initSvdMemory();
	_resizeInv(invMatrix.matrix,McolMajor);
	char Jobu='A'; /* Compute complete U Matrix */
	char Jobvt='A'; /* Compute complete VT Matrix */

	if( toTranspose ){ McolMajor = trans(matrix); }else{ McolMajor = matrix; }

	/* Compute the SVD. */

	{
	  int linfo; const int n=nbrows,
		       m=nbcols;
	  lda = std::max(m,n);
	  lu = traits::leading_dimension(U); // NR
	  lvt = traits::leading_dimension(VT); // NC
	  dgesvd_(&Jobu, &Jobvt,&n,&m,
		  MRAWDATA(McolMajor),
		  &lda,
		  VRAWDATA(s),
		  MRAWDATA(U),
		  &lu,
		  MRAWDATA(VT),
		  &lvt,
		  VRAWDATA(w),&lw,&linfo);

	}


	rankJ = 0;
	for( unsigned int i=0;i<nminor;++i )
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

	  for( unsigned int i=0;i<nbcols;++i )
	    {
	      uptrRow = MRAWDATA(U);
	      for( unsigned int j=0;j<nbrows;++j )
		{
		  uptr = uptrRow;  vptr = vptrRow;
		  spptr = VRAWDATA( sp );
		  for( unsigned int k=0;k<rankJ;++k )
		    {
		      (*pinv) += (*vptr) * (*spptr) * (*uptr);
		      uptr+=nbrows; vptr++; spptr++;
		    }
		  pinv++; uptrRow++;
		}
	      vptrRow += nbcols;
	    }
	}

	if( toTranspose )
	  {
	    invMatrix.matrix = trans(invMatrix.matrix);
	    if( Uref ) Uref->matrix = VT;
	    if( Vref ) Vref->matrix = trans(U);
	    if( Sref ) Sref->accessToMotherLib() = s;
	  }
	else
	  {
	    if( Uref ) Uref->matrix = U;
	    if( Vref ) Vref->matrix = trans(VT);
	    if( Sref ) Sref->accessToMotherLib() = s;
	  }
	return invMatrix;
      }

      virtual Matrix&
	dampedInverse( Matrix& invMatrix,
		       const FloatType threshold = 1e-6,
		       Matrix* Uref = NULL,
		       Vector* Sref = NULL,
		       Matrix* Vref = NULL)  const
      {
	initSvdMemory();
	_resizeInv(invMatrix.matrix,McolMajor);
	char Jobu='A'; /* Compute complete U Matrix */
	char Jobvt='A'; /* Compute complete VT Matrix */

	if( toTranspose ){ McolMajor = trans(matrix); }else{ McolMajor = matrix; }

	/* Compute the SVD. */
	{
	  const int n=nbrows,
	    m=nbcols;
	  lda = std::max(m,n);
	  lu = traits::leading_dimension(U); // NR
	  lvt = traits::leading_dimension(VT); // NC

	  int linfo;
	  dgesvd_(&Jobu, &Jobvt,&n,&m,
		  MRAWDATA(McolMajor),
		  &lda,
		  VRAWDATA(s),
		  MRAWDATA(U),
		  &lu,
		  MRAWDATA(VT),
		  &lvt,
		  VRAWDATA(w),&lw,&linfo);

	}

	rankJ = 0;
	for( unsigned int i=0;i<nminor;++i )
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

	  for( unsigned int i=0;i<nbcols;++i )
	    {
	      uptrRow = MRAWDATA(U);
	      for( unsigned int j=0;j<nbrows;++j )
		{
		  uptr = uptrRow;  vptr = vptrRow;
		  spptr = VRAWDATA( sp );
		  for( unsigned int k=0;k<rankJ;++k )
		    {
		      (*pinv) += (*vptr) * (*spptr) * (*uptr);
		      uptr+=nbrows; vptr++; spptr++;
		    }
		  pinv++; uptrRow++;
		}
	      vptrRow += nbcols;
	    }
	}

	if( toTranspose )
	  {
	    invMatrix.matrix = trans(invMatrix.matrix);
	    if( Uref ) Uref->matrix = VT;
	    if( Vref ) Vref->matrix = trans(U);
	    if( Sref ) Sref->accessToMotherLib() = s;
	  }
	else
	  {
	    if( Uref ) Uref->matrix = U;
	    if( Vref ) Vref->matrix = trans(VT);
	    if( Sref ) Sref->accessToMotherLib() = s;
	  }
	return invMatrix;
      }

    };

  }}

/* --- FUNCTIONS ------------------------------------------------------------ */
/* --- FUNCTIONS ------------------------------------------------------------ */
/* --- FUNCTIONS ------------------------------------------------------------ */



#endif // #ifndef __MAAL_BOOST_MATRIX_SVD_
