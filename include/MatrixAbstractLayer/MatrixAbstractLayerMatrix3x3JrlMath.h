/*
 * Copyright 2007, 2008, 2009, 2010, 
 * Florent Lamiraux,
 * Olivier Stasse,
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

/*! This is a very fast and simple implementation
 * of a 3D matrix class of double.
 * 
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
  name.Inversion(inv_matrix)

#define MAL_S3x3_RET_TRANSPOSE(matrix) \
  matrix.Transpose()

#define MAL_S3x3_TRANSPOSE_A_in_At(A,At)		\
  A.Transpose(At)

#define MAL_S3x3_RET_A_by_B(A,B) \
  A*B

#define MAL_S3x3_C_eq_A_by_B(C,A,B) \
  A.CeqthismulB(B,C);

#define MAL_S3x3_MATRIX_ACCESS_I(name, i) \
  name[i]

#define MAL_S3x3_MATRIX_ACCESS_I_J(name, i, j) \
  name(i,j)


#endif /* MATRIXABSTRACTLAYER_JRLMATH_MATRIX3X3_H */
