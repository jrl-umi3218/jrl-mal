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
Test Vector x Vector operations
*/
void run_test()
{
  srand(time(NULL));
  Vector v1(3), v2(3), v3(3), tmp(3);
  FloatType x = randomFloat();
  FloatType scalarProduct, tmp1;
  setRandom(v1,3); setRandom(v2,3);

  // Test vector * vector
  v3 = v1.multiply(v2);
  tmp(0) = v1(0)*v2(0);
  tmp(1) = v1(1)*v2(1);
  tmp(2) = v1(2)*v2(2);
  tmp = tmp - v3;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector * vector product");

  // Test vector * scalar
  v3 = v1.multiply(x);
  tmp(0) = v1(0)*x;
  tmp(1) = v1(1)*x;
  tmp(2) = v1(2)*x;
  tmp = tmp - v3;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector * scalar product");

  // Test vector + vector
  v3 = v1.addition(v2);
  tmp(0) = v1(0)+v2(0);
  tmp(1) = v1(1)+v2(1);
  tmp(2) = v1(2)+v2(2);
  tmp = tmp - v3;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector * vector addition");

  // Test vector - vector
  v3 = v1.substraction(v2);
  tmp(0) = v1(0)-v2(0);
  tmp(1) = v1(1)-v2(1);
  tmp(2) = v1(2)-v2(2);
  tmp = tmp - v3;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector * vector substraction");

  // Test vector cross product
  v3 = v1.crossProduct(v2);
  tmp(0) = v1(1)*v2(2)-v2(1)*v1(2);
  tmp(1) = v1(2)*v2(0)-v2(2)*v1(0);
  tmp(2) = v1(0)*v2(1)-v2(0)*v1(1);
  tmp = tmp - v3;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector cross product");

  // Test scalar product
  scalarProduct = v1.scalarProduct(v2);
  tmp1 = v1(0)*v2(0) + v1(1)*v2(1) + v1(2)*v2(2);
  JRL_MAL_ASSERT(fabs(scalarProduct-tmp1)<1e-6
              && "test vector scalar product");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Vector x vector operations test has succeeded." << std::endl;
}

GENERATE_TEST()
