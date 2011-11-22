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
Test Vector modifiors methods
*/
void run_test()
{
  srand(time(NULL));
  Vector v1(3), v2(3), tmp(3);
  setRandom(v1, 3); setRandom(v2, 2);

  // Check resize without value reset
  tmp = v1;
  v1.resize(2, false);
  tmp(0) = tmp(0) - v1(0);
  tmp(1) = tmp(1) - v1(1);
  tmp(2) = 0;
  JRL_MAL_ASSERT(v1.size() == 2
              && isVectorNull(tmp)
              && "test vector resize without value reset");

  // Check resize with reset
  v1.resize(3);
  JRL_MAL_ASSERT(v1.size() == 3
              && isVectorNull(v1)
              && "test vector resize with value reset");

  // Check fill with constant method
  FloatType x = randomFloat();
  v1.fill(x);
  JRL_MAL_ASSERT((v1(0) == x)
              && (v1(1) == x)
              && (v1(2) == x)
              && "test filling vector with constant");

  // Check opposite method
  v1.opposite(v2);
  JRL_MAL_ASSERT((v2(0) == -x)
              && (v2(1) == -x)
              && (v2(2) == -x)
              && "test vector opposite method");

  // Check reset method
  v1.setZero();
  JRL_MAL_ASSERT(isVectorNull(v1)
              && "test vector reset method");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Vector modifiors test has succeeded." << std::endl;
}

GENERATE_TEST()
