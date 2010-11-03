/*
 * Copyright 2007, 2008, 2009, 2010,
 *
 * Francois Keith,
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
 * of a 3D vector class of double.
 *
 */

#ifndef MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H
# define MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H
# include <cmath>
# include <jrl/mathtools/vector3.hh>

typedef jrlMathTools::Vector3D<double> vector3d;

# define MAL_S3_VECTOR(name,type)		\
  jrlMathTools::Vector3D<type> name

# define MAL_S3_VECTOR_SIZE(name)		\
  3

# define MAL_S3_VECTOR_FILL(name,value)		\
  { name.m_x = value;				\
    name.m_y = value;				\
    name.m_z = value; }

# define MAL_S3_VECTOR_CLEAR(name)		\
{ name.m_x = 0.0;				\
	name.m_y = 0.0;				\
	name.m_z = 0.0; }

# define MAL_S3_VECTOR_NORM(name)		\
  name.norm()

# define MAL_S3_VECTOR_CROSS_PRODUCT(res,v1,v2)	\
  res = v1 ^ v2;

# define MAL_S3_RET_VECTOR_DATABLOCK(name)	\
  &name

# define MAL_S3_VECTOR_ACCESS(name, i)  	\
  name[i]

#endif /* MATRIXABSTRACTLAYER_JRLMATH_VECTOR3_H*/
