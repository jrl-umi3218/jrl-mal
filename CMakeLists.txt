# Copyright 2008, 2009, 2010, Olivier Stasse, JRL, CNRS/AIST
#
# This file is part of MatrixAbstractLayer.
# MatrixAbstractLayer is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MatrixAbstractLayer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Lesser Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with MatrixAbstractLayer.  If not, see <http://www.gnu.org/licenses/>.
#

# Requires at least CMake 2.6 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/cpack.cmake)

SET(PROJECT_NAME jrl-mal)
SET(PROJECT_VERSION 1.9.0.99)
SET(PROJECT_DESCRIPTION "JRL matrix abstract layer")
SET(PROJECT_URL "http://github.com/jrl-umi3218/jrl-mal")

SETUP_PROJECT()
SETUP_PROJECT_CPACK()

# Requires Fortran support as Lapack needs it.
ENABLE_LANGUAGE(Fortran)

# Search for Boost.
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.40 COMPONENTS unit_test_framework REQUIRED)
SET(SMALLMATRIX "jrl-mathtools")
# Search for LAPACK.
FIND_PACKAGE(LAPACK REQUIRED)
FOREACH(L ${LAPACK_LINKER_FLAGS} ${LAPACK_LIBRARIES})
  SET(PKG_CONFIG_LIBS "${PKG_CONFIG_LIBS} ${L}")
ENDFOREACH(L in ${LAPACK_LIBRARIES})

# Search for the underlying small matrices library.
SET(SMALLMATRIXLIB_FOUND 0)

SET(_BOOST_MATRIX_FOUND_ 1)
SET(_VNL_MATRIX_FOUND_ 0)
SET(_T3D_R3D_V3D_FOUND_ 0)

IF(SMALLMATRIX STREQUAL "jrl-mathtools")
  ADD_REQUIRED_DEPENDENCY("jrlMathTools >= 1.4")

  SET(SMALLMATRIXLIB_CXXFLAGS ${JRLMATHTOOLS_CFLAGS})
  SET(SMALLMATRIXLIB_FOUND 1)
ENDIF(SMALLMATRIX STREQUAL "jrl-mathtools")

IF(SMALLMATRIX STREQUAL "t3d")
  ADD_REQUIRED_DEPENDENCY("t3d >= 2.5")
  ADD_REQUIRED_DEPENDENCY("jrlMathTools >= 1.4")

  SET(SMALLMATRIXLIB_CXXFLAGS ${T3D_CFLAGS})
  SET(SMALLMATRIXLIB_FOUND 1)
  SET(_T3D_R3D_V3D_FOUND_ 1)
ENDIF(SMALLMATRIX STREQUAL "t3d")

IF(NOT ${SMALLMATRIXLIB_FOUND})
  MESSAGE(FATAL_ERROR
    "No small matrix library found or specified.\n"
    "Two underlying small matrices libraries are currently supported:\n"
    "* jrl-mathtools - ``cmake -DSMALLMATRIX=jrl-mathtools''\n"
    "* t3d - ``cmake -DSMALLMATRIX=t3d''\n"
    )
ENDIF(NOT ${SMALLMATRIXLIB_FOUND})

CONFIG_FILES(include/jrl/mal/configMAL.hh)

CONFIG_FILES(include/MatrixAbstractLayer/configMAL.h)

SET(${PROJECT_NAME}_HEADERS
  ${CMAKE_BINARY_DIR}/include/jrl/mal/config.hh
  ${CMAKE_BINARY_DIR}/include/jrl/mal/configMAL.hh
  include/jrl/mal/MatrixAbstractLayer.hh
  include/jrl/mal/MatrixAbstractLayerCheck.hh
  include/jrl/mal/MatrixAbstractLayerBoost.hh
  include/jrl/mal/MatrixAbstractLayerDoc.hh
  include/jrl/mal/MatrixAbstractLayerSmall.hh
  include/jrl/mal/MatrixAbstractLayerMatrix3x3JrlMath.hh
  include/jrl/mal/MatrixAbstractLayerMatrix4x4JrlMath.hh
  include/jrl/mal/MatrixAbstractLayerVector3JrlMath.hh
  include/jrl/mal/MatrixAbstractLayerVector4JrlMath.hh
  include/jrl/mal/MatrixAbstractLayerVNL.hh
  include/jrl/mal/MatrixAbstractLayerT3D.hh
  include/jrl/mal/abstract.hh
  include/jrl/mal/abstractMatrix.hh
  include/jrl/mal/abstractVector.hh
  include/jrl/mal/boost.hh
  include/jrl/mal/boostMacros.hh
  include/jrl/mal/boostMatrix.hh
  include/jrl/mal/boostMatrixSvd.hh
  include/jrl/mal/boostspecific.hh
  include/jrl/mal/boostSvd.hh
  include/jrl/mal/boostVector.hh
)

# Deprecated headers
# These headers are installed to preserve includes retro-compatbility.
SET(DEPRECATED_HEADERS
  ${CMAKE_BINARY_DIR}/include/MatrixAbstractLayer/configMAL.h
  include/MatrixAbstractLayer/MatrixAbstractLayer.h
  include/MatrixAbstractLayer/MatrixAbstractLayerCheck.h
  include/MatrixAbstractLayer/MatrixAbstractLayerBoost.h
  include/MatrixAbstractLayer/MatrixAbstractLayerDoc.h
  include/MatrixAbstractLayer/MatrixAbstractLayerSmall.h
  include/MatrixAbstractLayer/MatrixAbstractLayerMatrix3x3JrlMath.h
  include/MatrixAbstractLayer/MatrixAbstractLayerMatrix4x4JrlMath.h
  include/MatrixAbstractLayer/MatrixAbstractLayerVector3JrlMath.h
  include/MatrixAbstractLayer/MatrixAbstractLayerVector4JrlMath.h
  include/MatrixAbstractLayer/MatrixAbstractLayerVNL.h
  include/MatrixAbstractLayer/MatrixAbstractLayerT3D.h
  include/MatrixAbstractLayer/abstract.h
  include/MatrixAbstractLayer/abstractMatrix.h
  include/MatrixAbstractLayer/abstractVector.h
  include/MatrixAbstractLayer/boost.h
  include/MatrixAbstractLayer/boostMacros.h
  include/MatrixAbstractLayer/boostMatrix.h
  include/MatrixAbstractLayer/boostMatrixSvd.h
  include/MatrixAbstractLayer/boostspecific.h
  include/MatrixAbstractLayer/boostSvd.h
  include/MatrixAbstractLayer/boostVector.h
)
INSTALL(FILES ${DEPRECATED_HEADERS}
  DESTINATION include/MatrixAbstractLayer
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
  )
# Install jrlMathTools.pc for retro-compatibility.
INSTALL(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
  DESTINATION "${PKG_CONFIG_DIR}"
  RENAME MatrixAbstractLayer.pc
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE)

ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
