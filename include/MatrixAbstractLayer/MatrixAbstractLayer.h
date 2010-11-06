/*
 * Copyright 2007, 2008, 2009, 2010,
 * Luis Degaldo,
 * Francois Keith,
 * Florent Lamiraux,
 * Anthony Mallet,
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

/**
 * \file MatrixAbstractLayer.h
 *
 * @ingroup linearalgebra
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 * If you do not like the current two solutions:
 *  - Oxford VNL
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


#ifndef _MATRIX_ABSTRACT_LAYER_H_
#  define _MATRIX_ABSTRACT_LAYER_H_

// Define which type of linear algebra package and which type of small matrix and vector package.
# include <MatrixAbstractLayer/configMAL.h>

  /*Documentation*/
# include <MatrixAbstractLayer/MatrixAbstractLayerDoc.h>
# include <MatrixAbstractLayer/MatrixAbstractLayerSmall.h>


  /*Boost or VNL*/
# if _VNL_MATRIX_ == 1
#  include <MatrixAbstractLayer/MatrixAbstractLayerVNL.h>
# elif _BOOST_MATRIX_ == 1
#  include <MatrixAbstractLayer/MatrixAbstractLayerBoost.h>
# endif

  /*Small with T3D, R3D and V3D or by default*/
# if _T3D_R3D_V3D_ == 1
#  include <MatrixAbstractLayer/MatrixAbstractLayerT3D.h>
# else
#  include "jrlMathTools/jrlConstants.h"
#  include <MatrixAbstractLayer/MatrixAbstractLayerVector3JrlMath.h>
#  include <MatrixAbstractLayer/MatrixAbstractLayerVector4JrlMath.h>
#  include <MatrixAbstractLayer/MatrixAbstractLayerMatrix3x3JrlMath.h>
#  include <MatrixAbstractLayer/MatrixAbstractLayerMatrix4x4JrlMath.h>
# endif

# define MATRIX_VERSION 1

# include <MatrixAbstractLayer/MatrixAbstractLayerCheck.h>

#endif /* _MATRIX_ABSTRACT_LAYER_H_ */
