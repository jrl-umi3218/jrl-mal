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
 */

 /**
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 *
 * This specific file implements a wrapping around the
 * Eigen matrices.
 *
 * (c) 2011 , Maxime Reis LAAS-CNRS.
 */

#ifndef MATRIXABSTRACTLAYER_EIGEN_H
# define MATRIXABSTRACTLAYER_EIGEN_H

/*!
 * @defgroup Eigen Eigen
 * @ingroup linearalgebra
 *
 */
#include "Eigen/Dense"

#define VRAWDATA(x) x.data()
#define MRAWDATA(x) x.data()

typedef Eigen::Matrix<double, Eigen::Dynamic, 1> vectorN;

extern "C"
{
  void dgesvd_(char const* jobu, char const* jobvt,
	       int const* m, int const* n, double* a, int const* lda,
	       double* s, double* u, int const* ldu,
	       double* vt, int const* ldvt,
	       double* work, int const* lwork, int* info);
}

#define MAL_VECTOR_TYPE(type)	\
  Eigen::Matrix<type, Eigen::Dynamic, 1>


#define MAL_VECTOR(name, type)	\
  Eigen::Matrix<type, Eigen::Dynamic, 1> name

#define MAL_VECTOR_DIM(name, type, nb_rows)	\
  Eigen::Matrix<type, Eigen::Dynamic, 1> name(nb_rows)

#define MAL_VECTOR_SIZE(name) \
  (unsigned)name.size()

#define MAL_VECTOR_RESIZE(name, nb_rows) \
  name.resize(nb_rows)

#define MAL_VECTOR_FILL(name, value) \
  { for(unsigned int i=0;i<name.size();name[i++]=value);}

#define MAL_VECTOR_NORM(name) \
  name.cast<double>().norm()

#define MAL_VECTOR_3D_CROSS_PRODUCT(res,v1,v2)	\
  if ((v1.size()==3) && (v2.size()==3))		\
    { \
      res[0] = v1[1] * v2[2] - v2[1] * v1[2]; \
      res[1] = v1[2] * v2[0] - v2[2] * v1[0]; \
      res[2] = v1[0] * v2[1] - v2[0] * v1[1]; \
    }

#define MAL_RET_VECTOR_DATABLOCK(name)\
  VRAWDATA(name)

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrixNxP;

#define MAL_MATRIX_TYPE(type)			\
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic>

#define MAL_MATRIX(name, type)			\
  Eigen::matrix<type, Eigen::Dynamic, Eigen::Dynamic> name

#define MAL_MATRIX_(type) \
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic>

#define MAL_MATRIX_DIM(name, type, nb_rows, nb_cols) \
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> name(nb_rows,nb_cols)

#define MAL_MATRIX_RESIZE(name,nb_rows,nb_cols) \
  name.resize(nb_rows,nb_cols)

#define MAL_MATRIX_NB_ROWS(name)  \
  (unsigned)name.rows()

#define MAL_MATRIX_NB_COLS(name)  \
  (unsigned)name.cols()

#define MAL_MATRIX_CLEAR(name) \
  { for(unsigned int i=0;i<name.size();name[i++]=0);}


#define MAL_INVERSE(name, inv_matrix, type)		\
  {	                                                \
    inv_matrix = name.inverse();                        \
/*    return;                                             \
    bool totranspose=false;                             \
    if (name.rows()<name.cols())                        \
       { name=name.transpose().eval();totranspose=true;} \
    const unsigned int NR=name.rows();                  \
    const unsigned int NC=name.cols();                  \
    const double  threshold = 1e-6;                     \
    Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> I = name;     \
    Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> U(NR,NR);     \
    Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> VT(NC,NC);    \
    Eigen::Matrix<type, Eigen::Dynamic, 1> s(std::min(NR,NC));  \
    char Jobu='A'; // Compute complete U Matrix 	\
    char Jobvt='A'; // Compute complete VT Matrix 	\
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
    Eigen::Matrix<double, Eigen::Dynamic, 1> w(lw);		\
    int lu = U.rows();                                  \
    int lvt = VT.rows();                                \
    dgesvd_(&Jobu, &Jobvt,&m,&n,                        \
	      MRAWDATA(I),                              \
	      &lda,                                     \
	      VRAWDATA(s),                              \
	      MRAWDATA(U),                              \
	      &lu,                                      \
	      MRAWDATA(VT),                             \
	      &lvt,                                     \
	      VRAWDATA(w),&lw,&linfo);	                \
    Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> S(name.cols(),name.rows()); \
    for(unsigned int i=0;i<name.cols();i++)		\
      for(unsigned int j=0;j<name.rows();j++)		\
        if ((i==j) && (fabs(s(i))>threshold))           \
           S(i,i)=1/s(i);                               \
        else S(i,j)=0;		                        \
    Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> tmp1;	        \
    tmp1 = S*(U.transpose().eval());			\
    inv_matrix = (VT.transpose().eval())*tmp1;	\
    if (totranspose) inv_matrix = inv_matrix.transpose().eval();*/ \
  }

#define MAL_PSEUDOINVERSE(matrix, pinv_matrix, type)

#define MAL_RET_TRANSPOSE(matrix) \
  matrix.transpose().eval()

#define MAL_TRANSPOSE_A_in_At(A,At)			\
  At = A.transpose().eval()

#define MAL_RET_A_by_B(A,B) \
  A*B

#define MAL_C_eq_A_by_B(C,A,B) \
  C = A*B \

#define MAL_MATRIX_SET_IDENTITY(matrix) \
  matrix.setIdentity(matrix.rows(),matrix.cols())

#define MAL_MATRIX_FILL(matrix, value) \
  matrix = matrix.Constant(matrix.rows(),matrix.cols(),value)

#define MAL_RET_MATRIX_DATABLOCK(matrix)\
  MRAWDATA(matrix)

#define MAL_MATRIX_C_eq_EXTRACT_A(C,A,type, top,left, nbrows, nbcols) \
  C = A.block(top,left,nbrows,nbcols)

template<class type> inline double __ret_mal_matrix_ret_determinant(Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> const & m)
{
  if (m.rows()!=m.cols())
    return -1;
  else return m.determinant();
}

#define MAL_MATRIX_RET_DETERMINANT(name,type)	\
  __ret_mal_matrix_ret_determinant<type>(name)


#define _MAL_VERSION_ 1

#endif /* MATRIXABSTRACTLAYER_EIGEN_H */
