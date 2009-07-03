/**
 * This header file intend to define an abstraction layer
 * to allow the use of diverse matrix libraries.
 * This is supposed to solve the dependency to a particular
 * matrix library.
 *
 * This specific file implements a wrapping around the
 * Boost matrices. This is Version 2.0, using inline function
 * instead of \#define.
 *
 * (c) 2006 , Nicolas Mansard, Olivier Stasse JRL-Japan, CNRS-AIST, ISRI.
 */


/** \file boost.h
 * Include this file for the maal::boost namespace.
 *
 */


#ifndef __MAAL_BOOST__
#define __MAAL_BOOST__

#warning "deprecated header file. Please consider using boost instead."

#include <iostream>


#include <MatrixAbstractLayer/boostMacros.h>
#include <MatrixAbstractLayer/boostVector.h>
#include <MatrixAbstractLayer/boostMatrix.h>




#endif /* #ifndef __MAAL_BOOST__ */


