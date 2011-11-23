/*
 * Copyright 2008, 2009, 2010,
 *
 * Francois Keith,
 * Florent Lamiraux,
 * Nicolas Mansard
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
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 *
 * This specific file implements a wrapping around the
 * Boost matrices. This is Version 2.0, using inline function
 * instead of \#define.
 *
 */


/** \file boost.h
 * Include this file for the maal::boost namespace.
 *
 */


#ifndef __MAAL_BOOST__
# define __MAAL_BOOST__

# include <iostream>

# include <jrl/mal/boostmacros.hh>
# include <jrl/mal/boostvector.hh>
# include <jrl/mal/boostmatrix.hh>
# include <jrl/mal/boostmatrixsvd.hh>

#endif /* #ifndef __MAAL_BOOST__ */
