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
 * Test Matrix macros
 */

#include "assertion.hh"
#include "malv1utils.hh"

/* 
Test Matrix x Matrix operations
*/
void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M1,    FloatType, 2, 2);
  MAL_MATRIX_DIM(M2,    FloatType, 1, 2);
  MAL_MATRIX_DIM(M3,    FloatType, 2, 3);
  MAL_MATRIX(    M4,    FloatType);
  MAL_MATRIX_DIM(tmp_m, FloatType, 2, 2);
  MAL_VECTOR_DIM(V1,    FloatType, 3);
  MAL_VECTOR(    V2,    FloatType);
  MAL_VECTOR_DIM(tmp_v, FloatType, 3);
  setRandom(M1,2,2); setRandom(M2,1,2); setRandom(M3,2,3);
  setRandom(V1,3);

/* Product */
  // Test matrix * matrix
  M4 = MAL_RET_A_by_B(M1,M1);
  manuallyComputedProduct(M1,M1,tmp_m);
  tmp_m = tmp_m - M4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,2)");

  M4 = MAL_RET_A_by_B(M2,M1);
  manuallyComputedProduct(M2,M1,tmp_m);
  tmp_m = tmp_m - M4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,2)");

  M4 = MAL_RET_A_by_B(M1,M3);
  manuallyComputedProduct(M1,M3,tmp_m);
  tmp_m = tmp_m - M4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,3)");

  M4 = MAL_RET_A_by_B(M2,M3);
  manuallyComputedProduct(M2,M3,tmp_m);
  tmp_m = tmp_m - M4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,3)");

  // Test matrix x vector
  V2 = MAL_RET_A_by_B(M3,V1);
  manuallyComputedProduct(M3,V1,tmp_v);
  tmp_v = tmp_v - V2;
  JRL_MAL_ASSERT(isVectorNull(tmp_v)
              && "test M(2,3)*V(3)");

  // All assertions true, test is passed
  std::cout << "Mal v1 : Matrix product test has succeeded." << std::endl;
}

GENERATE_TEST()
