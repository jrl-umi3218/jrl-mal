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
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/lapack.cmake)
INCLUDE(cmake/cpack.cmake)

SET(PROJECT_NAME jrl-mal)
SET(PROJECT_VERSION 1.9.0.99)
SET(PROJECT_DESCRIPTION "JRL matrix abstract layer")
SET(PROJECT_URL "http://github.com/jrl-umi3218/jrl-mal")

SETUP_PROJECT()
SETUP_PROJECT_CPACK()

# Search for dependencies.
SEARCH_FOR_BOOST()
SEARCH_FOR_LAPACK()

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

CONFIG_FILES(include/jrl/mal/configmal.hh)

SET(${PROJECT_NAME}_HEADERS
  ${CMAKE_BINARY_DIR}/include/jrl/mal/config.hh
  ${CMAKE_BINARY_DIR}/include/jrl/mal/configmal.hh
  include/jrl/mal/matrixabstractlayer.hh
  include/jrl/mal/matrixabstractlayercheck.hh
  include/jrl/mal/matrixabstractlayerboost.hh
  include/jrl/mal/matrixabstractlayerdoc.hh
  include/jrl/mal/matrixabstractlayersmall.hh
  include/jrl/mal/matrixabstractlayermatrix3x3jrlmath.hh
  include/jrl/mal/matrixabstractlayermatrix4x4jrlmath.hh
  include/jrl/mal/matrixabstractlayervector3jrlmath.hh
  include/jrl/mal/matrixabstractlayervector4jrlmath.hh
  include/jrl/mal/matrixabstractlayert3d.hh
  include/jrl/mal/abstract.hh
  include/jrl/mal/abstractmatrix.hh
  include/jrl/mal/abstractvector.hh
  include/jrl/mal/boost.hh
  include/jrl/mal/boostmacros.hh
  include/jrl/mal/boostmatrix.hh
  include/jrl/mal/boostmatrixsvd.hh
  include/jrl/mal/boostspecific.hh
  include/jrl/mal/boostsvd.hh
  include/jrl/mal/boostvector.hh
)

ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
