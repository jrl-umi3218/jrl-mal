 /*
 * Copyright 2011
 * Maxime REIS
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
 * \file MatrixAbstractLayer.h
 *
 * @ingroup linearalgebra
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 * If you do not like the current two solutions:
 *  - Eigen
 *  - uBLAS + LAPACK
 *
 * you can implement your own.
 *
 *
 * For small matrices it is sometimes more efficient
 * to use specific data structure.
 * For this reason an abstract interface for
 * small 3x3 and 4x4 matrices as well as vectors
 * is also provided. MatrixAbstractLayerT3D defines a
 * specific implementation for small 3x3, 4x4 and
 * small vectors.
 *
 * We however assume that the library used
 * is based on C++ classes and has a sensible implementation
 * of matrix operators.
 *
 * (c) 2006 , Olivier Stasse and Florent Lamiraux JRL-Japan, CNRS-AIST, ISRI.
 */


#ifndef _MAL_V2_H_
#  define _MAL_V2_H_
#  include <jrl/mal/configmal.hh>
#  if _EIGEN_MATRIX_ == 1
#    include <jrl/mal/eigen.hh>
#    define DECLARE_MAL_NAMESPACE(name) \
       namespace name = maal::eigen
#  elif _BOOST_MATRIX_ == 1
#   include <jrl/mal/boost.hh>
#    define DECLARE_MAL_NAMESPACE(name) \
       namespace name = maal::boost
#  endif
#endif /* _MAL_V2_H_ */
