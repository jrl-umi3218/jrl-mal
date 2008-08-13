/*! This is a very fast and simple implementation
 * of a 4D vector class of double.
 * 
 * 01/02/2007
 *
 * (c) Olivier Stasse and Florent Lamiraux, JRL, CNRS-AIST, ISRI, 2007 
 */

#ifndef MATRIXABSTRACTLAYER_JRLMATH_VECTOR4_H
#define MATRIXABSTRACTLAYER_JRLMATH_VECTOR4_H

#include "jrlMathTools/vector4.h"

typedef jrlMathTools::Vector4D<double> vector4d;

#define MAL_S4_VECTOR(name,type)		\
  jrlMathTools::Vector4D<type> name

#define MAL_S4_VECTOR_SIZE(name)		\
  3 

#define MAL_S4_VECTOR_FILL(name,value)		\
  { name.m_x = value;				\
    name.m_y = value;				\
    name.m_z = value;                           \
    name.m_w = value; }

#define MAL_S4_VECTOR_NORM(name)		\
  name.norm()

#define MAL_S4_RET_VECTOR_DATABLOCK(name)	\
  &name

#define MAL_S4_VECTOR_ACCESS(name, i)  		\
  name[i]

#endif /* MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H */
