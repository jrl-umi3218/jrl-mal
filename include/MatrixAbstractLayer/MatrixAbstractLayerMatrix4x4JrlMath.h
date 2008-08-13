/*! This is a very fast and simple implementation
 * of a 3D matrix class of double.
 * 
 * (c) Olivier Stasse and Florent Lamiraux, JRL, CNRS-AIST, ISRI, 2007
 */

#ifndef MATRIXABSTRACTLAYER_JRLMATH_MATRIX4X4_H
#define MATRIXABSTRACTLAYER_JRLMATH_MATRIX4X4_H

#include "jrlMathTools/matrix4x4.h"

typedef struct jrlMathTools::Matrix4x4 < double > matrix4d;

#define MAL_S4x4_MATRIX(name,type) \
  jrlMathTools::Matrix4x4<type> name

#define MAL_S4x4_MATRIX_CLEAR(name) \
  name.setZero()

#define MAL_S4x4_MATRIX_SET_IDENTITY(name) \
  name.setIdentity()

#define MAL_S4x4_INVERSE(name,inv_matrix,type)	\
  inv_matrix = name.Inversion();

#define MAL_S4x4_RET_TRANSPOSE(matrix) \
  matrix.Transpose();

#define MAL_S4x4_TRANSPOSE_A_in_At(A,At)	\
  A.Transpose(At);

#define MAL_S4x4_RET_A_by_B(A,B) \
  A*B

#define MAL_S4x4_C_eq_A_by_B(C,A,B) \
  A.CeqthismulB(B,C)

#define MAL_S4x4_MATRIX_ACCESS_I(name, i) \
  name[i]

#define MAL_S4x4_MATRIX_ACCESS_I_J(name, i, j) \
  name(i,j)  
  
#endif /* MATRIXABSTRACTLAYER_JRLMATH_MATRIX4X4 */
