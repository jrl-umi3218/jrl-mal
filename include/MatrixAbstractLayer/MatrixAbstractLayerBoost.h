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


/*!
 * @defgroup Boost Boost
 * @ingroup linearalgebra
 * 
 */

#include "boost/numeric/bindings/traits/ublas_matrix.hpp"
#include "boost/numeric/bindings/traits/std_vector.hpp"
#include "boost/numeric/bindings/traits/std_vector.hpp"

#include "boost/numeric/ublas/matrix_proxy.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"
#include "boost/numeric/bindings/lapack/gesvd.hpp"
#include "boost/numeric/ublas/operation.hpp"
#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/vector_proxy.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include "boost/numeric/ublas/lu.hpp"

namespace boost_ublas = boost::numeric::ublas;
namespace traits = boost::numeric::bindings::traits;
namespace lapack = boost::numeric::bindings::lapack;

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
  traits::vector_storage(name)

typedef boost_ublas::matrix<double> matrixNxP;

#define MAL_MATRIX(name, type)			\
  boost_ublas::matrix<type> name

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
    char Lw='O'; /* Compute the optimal size for the working vector */ \
    int lw = lapack::gesvd_work(Lw,Jobu,Jobvt,I);    \
    boost_ublas::vector<double> w(lw);		        \
    lapack::gesvd(Jobu, Jobvt,I,s,U,VT,w);		\
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
  traits::matrix_storage(matrix)

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




