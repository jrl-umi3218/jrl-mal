/*! This is a very fast and simple implementation
 * of a 3D vector class of double.
 * 
 * (c) Olivier Stasse and Florent Lamiraux, JRL, CNRS-AIST, ISRI, 2007
 */

#ifndef MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H
#define MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H

#include <cmath>
#include "jrlMathTools/vector3.h"

typedef jrlMathTools::Vector3D<double> vector3d;

#define MAL_S3_VECTOR(name,type)		\
  jrlMathTools::Vector3D<type> name

#define MAL_S3_VECTOR_SIZE(name)		\
  3 

#define MAL_S3_VECTOR_FILL(name,value)		\
  { name.m_x = value;				\
    name.m_y = value;				\
    name.m_z = value; }

#define MAL_S3_VECTOR_CLEAR(name)		\
{ name.m_x = 0.0;				\
	name.m_y = 0.0;				\
	name.m_z = 0.0; }

#define MAL_S3_VECTOR_NORM(name)		\
  name.norm()

#define MAL_S3_VECTOR_CROSS_PRODUCT(res,v1,v2)	\
  res = v1 ^ v2;

#define MAL_S3_RET_VECTOR_DATABLOCK(name)	\
  &name

#define MAL_S3_VECTOR_ACCESS(name, i)  		\
  name[i]

#endif /* MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H*/
