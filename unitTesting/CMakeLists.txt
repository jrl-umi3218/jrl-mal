# Copyright 2008, 2009, 2010, Olivier Stasse,
#                             Florent Lamiraux,JRL, CNRS/AIST
#
# This file is part of jrl-mal.
# jrl-mathtools is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# jrl-mal is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Lesser Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with jrl-mal.  If not, see <http://www.gnu.org/licenses/>.

# Add Boost path to include directories.
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# Make Boost.Test generates the main function in test cases.
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)
ADD_DEFINITIONS(${SMALLMATRIXLIB_CXXFLAGS})
# JRL_MAL_TEST(NAME)
# ------------------------
#
# Define a test named `NAME'.
#
# This macro will create a binary from `NAME.cc', link it against
# Boost and add it to the test suite.
#
MACRO(JRL_MAL_TEST NAME)
  ADD_EXECUTABLE(${NAME} ${NAME}.cc)
  ADD_TEST(${NAME} ${RUNTIME_OUTPUT_DIRECTORY}/${NAME})

  # Link against LAPACK.
  TARGET_LINK_LIBRARIES(${NAME} ${LAPACK_LIBRARIES})

  # Link against Boost.
  TARGET_LINK_LIBRARIES(${NAME} ${Boost_LIBRARIES})
ENDMACRO(JRL_MAL_TEST)

# Simple test.
JRL_MAL_TEST(simple)
JRL_MAL_TEST(TestMalV2VectorConstructors)
JRL_MAL_TEST(TestMalV2VectorAccessors)
JRL_MAL_TEST(TestMalV2VectorModifiors)
JRL_MAL_TEST(TestMalV2VectorNorms)
JRL_MAL_TEST(TestMalV2VectorXVectorOperators)
JRL_MAL_TEST(TestMalV2MatrixConstructors)
JRL_MAL_TEST(TestMalV2MatrixAccessors)
JRL_MAL_TEST(TestMalV2MatrixModifiors)
JRL_MAL_TEST(TestMalV2MatrixSetIdentity)
JRL_MAL_TEST(TestMalV2MatrixNorms)
JRL_MAL_TEST(TestMalV2MatrixXMatrixOperators)
JRL_MAL_TEST(TestMalV2MatrixInverse)
JRL_MAL_TEST(TestMalV2MatrixPseudoInverse)
JRL_MAL_TEST(TestMalV2MatrixDampedInverse)
JRL_MAL_TEST(TestMalV2MatrixTranspose)
JRL_MAL_TEST(TestMalV1VectorAccessors)
JRL_MAL_TEST(TestMalV1VectorModifiors)
JRL_MAL_TEST(TestMalV1VectorCrossProduct)
JRL_MAL_TEST(TestMalV1VectorNorm)
JRL_MAL_TEST(TestMalV1MatrixAccessors)
JRL_MAL_TEST(TestMalV1MatrixModifiors)
JRL_MAL_TEST(TestMalV1MatrixSetIdentity)
JRL_MAL_TEST(TestMalV1MatrixInverse)
JRL_MAL_TEST(TestMalV1MatrixTranspose)
JRL_MAL_TEST(TestMalV1MatrixProduct)
