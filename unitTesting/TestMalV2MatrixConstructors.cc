// Copyright 2011 Maxime Reis.
//
// This file is part of jrl-mal.
// jrl-mal is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// jrl-mal is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License
// along with jrl-mal.  If not, see <http://www.gnu.org/licenses/>.

/* 
 * Test Matrix class
 */

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test of Matrix class constructors
*/
void run_test()
{
  internalMatrix _m(2,2);
  _m(0,0) = 1.0; _m(0,1) = 2.0; _m(1,0) = 3.0; _m(1,1) = 4.0;
  Matrix m1(2,2),   // Create size (2,2) internal matrix
         m2(&_m),   // Build capsule around existing size (2,2) eigen matrix
         m3(m2);    // Create copy of existing size (2,2) matrix
  // Check size
  JRL_MAL_ASSERT(m1.nbRows() == 2
              && m1.nbCols() == 2
              && "test matrix size after initialisation through internal matrix creation");
  JRL_MAL_ASSERT(m2.nbRows() == 2
              && m2.nbCols() == 2
              && "test matrix size after initialisation through existing internal matrix encapsulation");
  JRL_MAL_ASSERT(m3.nbRows() == 2
              && m3.nbCols() == 2
              && "test matrix size after initialisation through existing internal matrix copy");

  // Check internal matrix values when creating a new matrix, encapsuling or copying an existing one
  JRL_MAL_ASSERT(m1(0,0) == 0 && m1(0,1) == 0
              && m1(1,0) == 0 && m1(1,1) == 0
              && "test matrix values after initialisation through internal matrix creation and initialisation");
  JRL_MAL_ASSERT(m2(0,0) == 1 && m2(0,1) == 2
              && m2(1,0) == 3 && m2(1,1) == 4
              && "test matrix values after initialisation through existing internal matrix encapsulation");
  JRL_MAL_ASSERT(m3(0,0) == 1 && m3(0,1) == 2
              && m3(1,0) == 3 && m3(1,1) == 4
              && "test matrix values after initialisation through existing internal matrix copy");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Matrix constructors test has succeeded." << std::endl;
}

GENERATE_TEST()
