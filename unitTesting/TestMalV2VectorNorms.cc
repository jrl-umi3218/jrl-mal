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
Test Vector norm methods
*/
void run_test()
{
  Vector v1(3);
  v1(0) = 1.0; v1(1) = 2.0; v1(2) = -3.0;
  FloatType x, tmp;
  
  // Test euclidian norm
  x = v1.norm();
  tmp = sqrt(v1(0)*v1(0)+v1(1)*v1(1)+v1(2)*v1(2));
  std::cout << "x = " << x << " ; tmp = " << tmp << std::endl;
  JRL_MAL_ASSERT(x == tmp
              && "test vector norm");

  // Test norm1
  x = v1.norm1();
  tmp = fabs(v1(0)) + fabs(v1(1)) + fabs(v1(2));
  JRL_MAL_ASSERT(x == tmp
              && "test vector norm1");

  // Test norm infinity
  x = v1.normInfty();
  tmp = std::max(std::max(fabs(v1(0)), fabs(v1(1))), fabs(v1(2)));
  JRL_MAL_ASSERT(x == tmp
              && "test vector norm infinity");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Vector norm methods test has succeeded." << std::endl;
}

GENERATE_TEST()
