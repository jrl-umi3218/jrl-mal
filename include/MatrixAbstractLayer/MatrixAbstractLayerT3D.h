/*
 * Copyright 2007, 2008, 2009, 2010,
 * Luis Degaldo,
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

/*! This is an implementation of MatrixAbstractLayerSmall using
 * T3D, R3D and V3D
 *
 */

#ifndef MATRIXABSTRACTLAYER_T3D_H
# define MATRIXABSTRACTLAYER_T3D_H

/*T3D which implements SmallMatrix4x4*/
#include "t3d/t3d.h"

typedef T3D matrix4d;

#define MAL_S4x4_MATRIX(name,type) \
  T3D name


#define MAL_S4x4_MATRIX_CLEAR(name) \
  /*Clear don't have any sense*/

#define MAL_S4x4_MATRIX_SET_IDENTITY(name) \
  name=t3dMatrixIdentity

#define MAL_S4x4_INVERSE(name,inv_matrix,type)	\
  inv_matrix=~name;

#define MAL_S4x4_RET_TRANSPOSE(matrix) \
  /*Transpose don't have any sense*/

#define MAL_S4x4_TRANSPOSE_A_in_At(A,At)		\
  /*Transpose don't have any sense*/

#define MAL_S4x4_RET_A_by_B(A,B) \
  (A)*(B)

#define MAL_S4x4_C_eq_A_by_B(C,A,B) \
  (C)=(A)*(B)

#define MAL_S4x4_MATRIX_ACCESS_I(name, i) \
  name.matrix[i]

#define MAL_S4x4_MATRIX_ACCESS_I_J(name, i, j) \
  name.matrix(i,j)


#include "t3d/v3d.h"
#include <cmath>

/*V3D which implements SmallVector3*/
typedef V3D vector3d;

#define MAL_S3_VECTOR(name,type)		\
  V3D name

#define MAL_S3_VECTOR_SIZE(name)		\
  3

#define MAL_S3_VECTOR_FILL(name,value)		\
  { name[0] = value;				\
    name[1] = value;				\
    name[2] = value; }

#define MAL_S3_VECTOR_NORM(name)		\
    sqrt(name[0]*name[0]+			\
    name[1]*name[1]+				\
    name[2]*name[2])

#define MAL_S3_VECTOR_CROSS_PRODUCT(res,v1,v2)	\
  { res[0] = v1[1]*v2[2]-v1[2]*v2[1];		\
    res[1] = v1[2]*v2[0]-v1[0]*v2[2];		\
    res[2] = v1[0]*v2[1]-v1[1]*v2[0];}

#define MAL_S3_RET_VECTOR_DATABLOCK(name)	\
  &name

#define MAL_S3_VECTOR_ACCESS(name, i)  		\
  name[i]

#define MAL_S3_VECTOR_CLEAR(name)		\
  { name[0] = 0.;				\
    name[1] = 0.;				\
    name[2] = 0.; }

/*V3D which implements SmallVector4*/
typedef V3D vector4d;

#define MAL_S4_VECTOR(name,type)		\
  V3D name

#define MAL_S4_VECTOR_SIZE(name)		\
  3

#define MAL_S4_VECTOR_FILL(name,value)		\
  { name[0] = value;				\
    name[1] = value;				\
    name[2] = value; 				\
    name[3] = value; }

#define MAL_S4_VECTOR_NORM(name)		\
  { sqrt(name[0]*name[0]+			\
    name[1]*name[1]+				\
    name[2]*name[2]+				\
    name[3]*name[3])}

#define MAL_S4_RET_VECTOR_DATABLOCK(name)	\
  &name

#define MAL_S4_VECTOR_ACCESS(name, i)  		\
  name[i]


#include "jrlMathTools/matrix3x3.h"

typedef jrlMathTools::Matrix3x3 <double> matrix3d;

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
  A.CeqthismulB(B,C)


#define MAL_S3x3_MATRIX_ACCESS_I(name, i) \
  name[i]

#define MAL_S3x3_MATRIX_ACCESS_I_J(name, i, j) \
  name(i,j)

#endif /* MATRIXABSTRACTLAYER_T3D_H */
