/*
 * Copyright 2008, 2009, 2010,
 *
 * Luis Delgado
 * Francois Keith
 * Anthony Mallet
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
 */

 /**
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 *
 * This specific file implements a wrapping around the
 * Boost matrices.
 *
 * (c) 2006 , Olivier Stasse JRL-Japan, CNRS-AIST, ISRI.
 */

#ifndef MATRIXABSTRACTLAYER_BOOST_H
# define MATRIXABSTRACTLAYER_BOOST_H

/*!
 * @defgroup Boost Boost
 * @ingroup linearalgebra
 *
 */
#include "boost/version.hpp"
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if BOOST_VERSION < 104000
# include "boost/numeric/bindings/traits/ublas_matrix.hpp"
# include "boost/numeric/bindings/traits/std_vector.hpp"
#endif

#include "boost/numeric/ublas/matrix_proxy.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"
#include "boost/numeric/ublas/operation.hpp"
#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/vector_proxy.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include "boost/numeric/ublas/lu.hpp"

namespace boost_ublas = boost::numeric::ublas;


#if BOOST_VERSION >= 104000
# include "boost/numeric/ublas/detail/raw.hpp"
namespace traits=boost_ublas::raw;
# define MRAWDATA(x) x.data().begin()
# define VRAWDATA(x) x.data().begin()
#else
# include "boost/numeric/bindings/lapack/gesvd.hpp"
namespace traits = boost::numeric::bindings::traits;
namespace lapack = boost::numeric::bindings::lapack;
# define MRAWDATA(x) traits::matrix_storage(x)
# define VRAWDATA(x) traits::vector_storage(x)
#endif


typedef boost_ublas::vector<double> vectorN;

extern "C"
{
  void dgesvd_(char const* jobu, char const* jobvt,
	       int const* m, int const* n, double* a, int const* lda,
	       double* s, double* u, int const* ldu,
	       double* vt, int const* ldvt,
	       double* work, int const* lwork, int* info);
}

#define MAL_VECTOR(name, type)	\
  boost_ublas::vector<type> name

#define MAL_VECTOR_DIM(name, type, nb_rows)	\
  boost_ublas::vector<type> name(nb_rows)

#define MAL_VECTOR_SIZE(name) \
  name.size()

#define MAL_VECTOR_RESIZE(name, nb_rows) \
  name.resize(nb_rows)

#define MAL_VECTOR_FILL(name, value) \
  { for(unsigned int i=0;i<name.size();name[i++]=value);}

#define MAL_VECTOR_NORM(name) \
  boost_ublas::norm_2(name)

#define MAL_VECTOR_3D_CROSS_PRODUCT(res,v1,v2)	\
  if ((v1.size()==3) && (v2.size()==3))		\
    { \
      res[0] = v1[1] * v2[2] - v2[1] * v1[2]; \
      res[1] = v1[2] * v2[0] - v2[2] * v1[0]; \
      res[2] = v1[0] * v2[1] - v2[0] * v1[1]; \
    }

#define MAL_RET_VECTOR_DATABLOCK(name)\
  VRAWDATA(name)

typedef boost_ublas::matrix<double> matrixNxP;

#define MAL_MATRIX(name, type)			\
  boost_ublas::matrix<type> name

#define MAL_MATRIX_(type) boost_ublas::matrix<type>

#define MAL_MATRIX_DIM(name, type, nb_rows, nb_cols) \
  boost_ublas::matrix<type> name(nb_rows,nb_cols)

#define MAL_MATRIX_RESIZE(name,nb_rows,nb_cols) \
  name.resize(nb_rows,nb_cols)

#define MAL_MATRIX_NB_ROWS(name)  \
  name.size1()

#define MAL_MATRIX_NB_COLS(name)  \
  name.size2()

#define MAL_MATRIX_CLEAR(name) \
  name.clear()

#define MAL_INVERSE(name, inv_matrix, type)		\
  {							\
    bool totranspose=false;                             \
    if (name.size1()<name.size2())                      \
       { name=trans(name);totranspose=true;}            \
    const unsigned int NR=name.size1();                 \
    const unsigned int NC=name.size2();                 \
    const double  threshold = 1e-6;                     \
    boost_ublas::matrix<type,boost_ublas::column_major> I = name;	\
    boost_ublas::matrix<type,boost_ublas::column_major> U(NR,NR);   \
    boost_ublas::matrix<type,boost_ublas::column_major> VT(NC,NC);	\
    boost_ublas::vector<type> s(std::min(NR,NC));		\
    char Jobu='A'; /* Compute complete U Matrix */	\
    char Jobvt='A'; /* Compute complete VT Matrix */	\
    const int m = NR;  const int n = NC;                \
    int linfo;                                          \
    int lda = std::max(m,n);                            \
    int lw=-1;                                          \
     {                                                  \
       double vw;                                       \
       dgesvd_(&Jobu, &Jobvt, &m, &n,                   \
		 MRAWDATA(I), &lda,                     \
		 0, 0, &m, 0, &n, &vw, &lw, &linfo);    \
       lw = int(vw)+5;                                  \
     }                                                  \
    boost_ublas::vector<double> w(lw);		        \
    int lu = traits::leading_dimension(U);              \
    int lvt = traits::leading_dimension(VT);            \
    dgesvd_(&Jobu, &Jobvt,&m,&n,                        \
	      MRAWDATA(I),                              \
	      &lda,                                     \
	      VRAWDATA(s),                              \
	      MRAWDATA(U),                              \
	      &lu,                                      \
	      MRAWDATA(VT),                             \
	      &lvt,                                     \
	      VRAWDATA(w),&lw,&linfo);	\
    boost_ublas::matrix<type> S(name.size2(),name.size1());	\
    for(unsigned int i=0;i<name.size2();i++)		\
      for(unsigned int j=0;j<name.size1();j++)		\
        if ((i==j) && (fabs(s(i))>threshold))           \
           S(i,i)=1/s(i);                               \
        else S(i,j)=0;		                        \
    boost_ublas::matrix<type> tmp1;				\
    tmp1 = prod(S,trans(U));				\
    inv_matrix = prod(trans(VT),tmp1);			\
    if (totranspose) inv_matrix = trans(inv_matrix);    \
  }

#define MAL_PSEUDOINVERSE(matrix, pinv_matrix, type)

#define MAL_RET_TRANSPOSE(matrix) \
  trans(matrix)

#define MAL_TRANSPOSE_A_in_At(A,At)			\
  At=trans(A)

#define MAL_RET_A_by_B(A,B) \
  prod(A,B)

#define MAL_C_eq_A_by_B(C,A,B) \
  { \
    C = prod(A,B); \
  }

#define MAL_MATRIX_SET_IDENTITY(matrix) \
  { \
    for(unsigned int i=0;i<matrix.size1();i++) \
      for(unsigned  int j=0;j<matrix.size2();j++)\
        if (i==j) \
           matrix(i,j) = 1; \
        else  \
	  matrix(i,j) = 0;\
   }

#define MAL_MATRIX_FILL(matrix, value) \
  {\
    for(unsigned int i=0;i<matrix.size1();i++) \
      for(unsigned int j=0;j<matrix.size2();j++)\
  	  matrix(i,j) = value;\
  }

#define MAL_RET_MATRIX_DATABLOCK(matrix)\
  MRAWDATA(matrix)

#define MAL_MATRIX_C_eq_EXTRACT_A(C,A,type, top,left, nbrows, nbcols) \
  { \
    boost_ublas::matrix_slice< boost_ublas::matrix<type> > amatrix(A,boost_ublas::slice(top,1,nbrows),boost_ublas::slice(left,1,nbcols)); \
    C = amatrix;\
  }


template<class type> inline double __ret_mal_matrix_ret_determinant(boost_ublas::matrix<type> const & m)
{
  if (m.size1()!=m.size2())
    return -1;

  boost_ublas::matrix<type> mLu(m);
  boost_ublas::permutation_matrix<std::size_t> pivots(m.size1());

  lu_factorize(mLu,pivots);
  double det=1.0;
  for(std::size_t i=0;
      i< pivots.size();
      i++)
    {
      if (pivots(i)!=i)
	det*=-1.0;

      det *= mLu(i,i);
    }
  return det;
}

#define MAL_MATRIX_RET_DETERMINANT(name,type)	\
  __ret_mal_matrix_ret_determinant<type>(name)


#define _MAL_VERSION_ 1

#endif /* MATRIXABSTRACTLAYER_BOOST_H */
