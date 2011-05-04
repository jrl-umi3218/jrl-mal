/*
 * Copyright 2011,
 *
 * Maxime Reis
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
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 *
 * This specific file implements a wrapping around the
 * Eigen matrices.
 *
 */


/** \file eigen.h
 * Include this file for the maal::eigen namespace.
 *
 */


#ifndef __MAAL_EIGEN__
# define __MAAL_EIGEN__
# define EIGEN_DEFAULT_TO_ROW_MAJOR

# include <iostream>

# include <jrl/mal/eigenmacros.hh>
# include <jrl/mal/eigenvector.hh>
# include <jrl/mal/eigenmatrix.hh>

#endif /* #ifndef __MAAL_EIGEN__ */
