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

#define MAL_VECTOR_TYPE(type)                        \
  Eigen::Matrix<type, Eigen::Dynamic, 1>


#define MAL_VECTOR(name, type)                       \
  Eigen::Matrix<type, Eigen::Dynamic, 1> name

#define MAL_VECTOR_DIM(name, type, nb_rows)          \
  Eigen::Matrix<type, Eigen::Dynamic, 1> name(nb_rows)

#define MAL_VECTOR_SIZE(name)                        \
  (unsigned)name.size()

#define MAL_VECTOR_RESIZE(name, nb_rows)             \
  name.conservativeResize(nb_rows)

#define MAL_VECTOR_FILL(name, value)                 \
{                                                    \
  int size = name.size();                            \
  for(int i=0;i<size;name[i++]=value);               \
}

#define MAL_VECTOR_NORM(name)                        \
  name.cast<double>().norm()

#define MAL_VECTOR_3D_CROSS_PRODUCT(res,v1,v2)       \
  if ((v1.size()==3) && (v2.size()==3))              \
    {                                                \
      res[0] = v1[1] * v2[2] - v2[1] * v1[2];        \
      res[1] = v1[2] * v2[0] - v2[2] * v1[0];        \
      res[2] = v1[0] * v2[1] - v2[0] * v1[1];        \
    }

#define MAL_RET_VECTOR_DATABLOCK(name)               \
  VRAWDATA(name)

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> matrixNxP;

#define MAL_MATRIX_TYPE(type)                        \
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>

#define MAL_MATRIX(name, type)                       \
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> name

#define MAL_MATRIX_(type)                            \
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>

#define MAL_MATRIX_DIM(name, type, nb_rows, nb_cols) \
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> name(nb_rows,nb_cols)

#define MAL_MATRIX_RESIZE(name,nb_rows,nb_cols)      \
  name.conservativeResize(nb_rows,nb_cols)

#define MAL_MATRIX_NB_ROWS(name)                     \
  (unsigned)name.rows()

#define MAL_MATRIX_NB_COLS(name)                     \
  (unsigned)name.cols()

#define MAL_MATRIX_CLEAR(name)                       \
{                                                    \
  double* rawMatrix = MRAWDATA(name);                \
  int size = name.rows()*name.cols();                \
  for(int i=0; i<size; i++){ rawMatrix[i] = 0; }     \
}

#define MAL_INVERSE(name, inv_matrix, type)          \
    inv_matrix = name.inverse();

#define MAL_PSEUDOINVERSE(matrix, pinv_matrix, type)

#define MAL_RET_TRANSPOSE(matrix)                    \
  matrix.transpose()
  
#define MAL_RET_TRANSPOSE_IN_PLACE(matrix)           \
  matrix.transposeInPlace()

#define MAL_TRANSPOSE_A_in_At(A,At)                  \
  At.noalias() = A.transpose()

#define MAL_RET_A_by_B(A,B)                          \
  A*B

#define MAL_C_eq_A_by_B(C,A,B)                       \
  C.noalias() = A*B

#define MAL_MATRIX_SET_IDENTITY(matrix)              \
{                                                    \
  double* rawMatrix = MRAWDATA(matrix);              \
  int rows = matrix.rows(), cols = matrix.cols();    \
  for(int i=0; i<rows*cols; i++)                     \
    { rawMatrix[i] = 0; }                            \
  for(int i=0; i<std::min(rows, cols); i++)          \
    { matrix(i,i) = 1; }                             \
}

#define MAL_MATRIX_FILL(matrix, value)               \
{                                                    \
  double* rawMatrix = MRAWDATA(matrix);              \
  int size = matrix.rows()*matrix.cols();            \
  for(int i=0; i<size; i++){ rawMatrix[i] = value; } \
}

#define MAL_RET_MATRIX_DATABLOCK(matrix)             \
  MRAWDATA(matrix)

#define MAL_MATRIX_C_eq_EXTRACT_A(C,A,type, top,left, nbrows, nbcols) \
  C.noalias() = A.block(top,left,nbrows,nbcols)

template<class type> inline double __ret_mal_matrix_ret_determinant(Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> const & m)
{
  return (m.rows()==m.cols())?m.determinant():-1;
}

#define MAL_MATRIX_RET_DETERMINANT(name,type)        \
  __ret_mal_matrix_ret_determinant<type>(name)


#define _MAL_VERSION_ 1

#endif /* MATRIXABSTRACTLAYER_EIGEN_H */
