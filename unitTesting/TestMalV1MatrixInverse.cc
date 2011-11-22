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
Test Matrix inverse macro
*/
void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M, FloatType, 10, 10);
  MAL_MATRIX(invM, FloatType);
  MAL_MATRIX_DIM(I, FloatType, 10, 10);
  MAL_MATRIX(tmp, FloatType);
  MAL_MATRIX_SET_IDENTITY(I);
  
  setRandom(M, 10,10);
  MAL_INVERSE(M, invM, FloatType);
  tmp = MAL_RET_A_by_B(M, invM) - I;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: M*invM = I");
  tmp = MAL_RET_A_by_B(invM, M) - I;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: invM*M = I");

  std::cout << "Mal v1 : Matrix inverse test has succeeded." << std::endl;
}

GENERATE_TEST()
