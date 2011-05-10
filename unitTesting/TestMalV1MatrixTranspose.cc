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
Test Matrix transpose macro
*/

void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M, FloatType, 10, 10);
  MAL_MATRIX(tmp, FloatType);

  // Case of a square matrix
  setRandom(M, 10, 10);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of square matrix");

  // Case of a non-square matrix
  setRandom(M, 5, 15);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of non-square matrix #1");
  
  setRandom(M, 15, 5);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of non-square matrix #2");
  

  std::cout << "Mal v1 : Matrix transpose test has succeeded." << std::endl;
}

GENERATE_TEST()
