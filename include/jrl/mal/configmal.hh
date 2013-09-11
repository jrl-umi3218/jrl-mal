/*
 * Copyright 2008, 2009, 2010,
 *
 * Olivier Stasse
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
#ifndef _CONFIG_MAL_H_
#define _CONFIG_MAL_H_

/*! Use eigen for generic NxP matrix implementation. */
#define _EIGEN_MATRIX_ 1

//#ifndef EIGEN_INITIALIZE_MATRICES_BY_NAN
//#define EIGEN_INITIALIZE_MATRICES_BY_NAN
//#endif

/*! Use VNL for generic NxP matrix implementation. */
#define _VNL_MATRIX_ 0

/*! use t3d for rigid body transformations. */
#define _T3D_R3D_V3D_ 0

/*! Uses the default implementation for the small 4x4 matrices */
#define _DEFAULT_MATRIX4x4_ 1

/*! Uses the default implementation for the small 3x3 matrices */
#define _DEFAULT_MATRIX3x3_ 1

/*! Uses the default implementation for the small 3d vector */
#define _DEFAULT_VECTOR3D_ 1

/*! Uses the default implementation for the small 3d vector */
#define _DEFAULT_VECTOR4D_ 1

#endif /* _CONFIG_MAL_H_ */
