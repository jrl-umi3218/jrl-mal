/*! This is a very fast and simple implementation
 * of a 3D matrix class of double.
 * 
 * (c) Olivier Stasse and Florent Lamiraux,  JRL, CNRS-AIST, ISRI, 2007
 */

#ifndef MATRIXABSTRACTLAYER_JRLMATH_MATRIX3X3_H
#define MATRIXABSTRACTLAYER_JRLMATH_MATRIX3X3_H

#include "jrlMathTools/matrix3x3.h"

typedef jrlMathTools::Matrix3x3<double> matrix3d;

#define MAL_S3x3_MATRIX(name,type) \
  jrlMathTools::Matrix3x3<type> name

#define MAL_S3x3_MATRIX_CLEAR(name) \
  name.setZero()

#define MAL_S3x3_MATRIX_SET_IDENTITY(name) \
  name.setIdentity()

#define MAL_S3x3_INVERSE(name,inv_matrix,type)	\
  name.Inversion(inv_matrix);

#define MAL_S3x3_RET_TRANSPOSE(matrix) \
  matrix.Transpose();

#define MAL_S3x3_TRANSPOSE_A_in_At(A,At)		\
  A.Transpose(At);

#define MAL_S3x3_RET_A_by_B(A,B) \
  A*B

#define MAL_S3x3_C_eq_A_by_B(C,A,B) \
  A.CeqthismulB(B,C);

#define MAL_S3x3_MATRIX_ACCESS_I(name, i) \
  name[i]

#define MAL_S3x3_MATRIX_ACCESS_I_J(name, i, j) \
  name(i,j)


#endif /* MATRIXABSTRACTLAYER_JRLMATH_MATRIX3X3_H */
