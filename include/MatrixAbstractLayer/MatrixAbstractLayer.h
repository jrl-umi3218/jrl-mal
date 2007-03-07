/**
 *
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
 * (c) 2006 , Olivier Stasse JRL-Japan, CNRS-AIST, ISRI.
 */


#ifndef _MATRIX_ABSTRACT_LAYER_H_
  #define _MATRIX_ABSTRACT_LAYER_H_

  /*Documentation*/
  #include "MatrixAbstractLayerDoc.h"
  #include "MatrixAbstractLayerSmall.h"


  /*Boost or VNL*/
  #ifdef _VNL_MATRIX_
    #include "MatrixAbstractLayerVNL.h"
  #elif defined _BOOST_MATRIX_
    #include "MatrixAbstractLayerBoost.h"
  #endif

  /*Small with T3D, R3D and V3D or by default*/
  #ifdef _T3D_R3D_V3D_
    #include "MatrixAbstractLayerT3D.h"
  #else 
    #include "MatrixAbstractLayerSmallVector3Default.h"
    #include "MatrixAbstractLayerSmallMatrix3x3Default.h"
    #include "MatrixAbstractLayerSmallVector4Default.h"
    #include "MatrixAbstractLayerSmallMatrix4x4Default.h"
  #endif

  #define MATRIX_VERSION 1
#endif


//#include "configMAL.h"
/*
#ifdef _DEFAULT_VECTOR3D_
#ifdef _DEFAULT_MATRIX3x3_
#ifdef _DEFAULT_VECTOR4D_
#ifdef _DEFAULT_MATRIX4x4_
*/
