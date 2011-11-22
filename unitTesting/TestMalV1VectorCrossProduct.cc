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
 * Test Vector macros
 */

#include "assertion.hh"
#include "malv1utils.hh"

void run_test()
{
  srand(time(NULL));
  MAL_VECTOR_DIM(V1,  FloatType, 3);
  MAL_VECTOR_DIM(V2,  FloatType, 3);
  MAL_VECTOR_DIM(V3,  FloatType, 3);
  MAL_VECTOR_DIM(tmp, FloatType, 3);
  setRandom(V1, 3); setRandom(V2, 3);

  // Check vector cross product
  MAL_VECTOR_3D_CROSS_PRODUCT(V3, V1, V2);
  tmp(0) = V1(1)*V2(2)-V2(1)*V1(2);
  tmp(1) = V1(2)*V2(0)-V2(2)*V1(0);
  tmp(2) = V1(0)*V2(1)-V2(0)*V1(1);
  tmp = tmp - V3;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector cross product");

  // All assertions true, test is passed
  std::cout << "Mal v1 : Vector cross product test has succeeded." << std::endl;
}

GENERATE_TEST()
