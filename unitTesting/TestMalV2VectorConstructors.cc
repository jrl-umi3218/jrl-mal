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
 * Test Vector class
 */

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Vector constructors
*/
void run_test()
{
  internalVector _m(3);
  _m(0) = 1.0; _m(1) = 2.0; _m(2) = 3.0;
  Vector v1(3),     // Create size 3 internal vector
         v2(&_m),   // Build capsule around existing size 3 eigen vector
         v3(v2);    // Create copy of existing size 3 vector
  // Check size
  JRL_MAL_ASSERT(v1.size() == 3
              && "test vector size after initialisation through internal vector creation");
  JRL_MAL_ASSERT(v2.size() == 3
              && "test vector size after initialisation through existing internal vector encapsulation");
  JRL_MAL_ASSERT(v3.size() == 3
              && "test vector size after initialisation through existing internal vector copy");

  // Check internal vector values when creating a new vector, encapsuling or copying an existing one
  JRL_MAL_ASSERT(v1(0) == 0
              && v1(1) == 0
              && v1(2) == 0
              && "test vector values after initialisation through internal vector creation and initialisation");
  JRL_MAL_ASSERT(v2(0) == 1
              && v2(1) == 2
              && v2(2) == 3
              && "test vector values after initialisation through existing internal vector encapsulation");
  JRL_MAL_ASSERT(v3(0) == 1
              && v3(1) == 2
              && v3(2) == 3
              && "test vector values after initialisation through existing internal vector copy");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Vector constructors test has succeeded." << std::endl;
}

GENERATE_TEST()
