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
 * Produce a warning at compilation step if the MAL::eigen implementation
 * is not used.
 *
 */


/*!
 * \file eigenspecific.h
 * Include this file to mark some part of the code where the
 * eigen internal library is specificaly used. Typically when
 * accessToMotherLib is used, the \#include <eigenspecific.h>
 * will prevent the later modification of the file toward
 * for example maal::t3d.
 */

#ifndef __MAAL_EIGEN__

# ifdef WIN32
#  pragma message ( " -- !!! -- Warning : This part of the code is only valid for the specific <eigen> implementation of the MAL. If you are not using eigen, the following code could produce undefined behaviors at run-time execution, or even not compile at all. Check and correct ..." )
# else
#  warning "This part of the code is only valid for the specific <eigen> implementation of the MAL. If you are not using eigen, the following code could produce undefined behaviors at run-time execution, or even not compile at all. Check and correct ..."
# endif /* WIN32 */

#endif /* #ifndef __MAAL_EIGEN__ */
