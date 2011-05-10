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

void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M1,   FloatType, 3, 1);
  MAL_MATRIX_DIM(M2,   FloatType, 2, 2);
  MAL_MATRIX_DIM(M3,   FloatType, 2, 2);
  MAL_MATRIX_DIM(tmp,  FloatType, 2, 2);
  MAL_MATRIX_DIM(tmp2, FloatType, 2, 2);

  // Check matrix resize
  MAL_MATRIX_RESIZE(M1, 2, 2);
  JRL_MAL_ASSERT(MAL_MATRIX_NB_ROWS(M1) == 2
              && MAL_MATRIX_NB_COLS(M1) == 2
              && "test matrix resize");

  // Check value conservation while resizing
  setRandom(M1, 2, 2);
  tmp = M1;
  MAL_MATRIX_RESIZE(M1, 3, 1);
  tmp2(0,0) = tmp(0,0) - M1(0,0);
  tmp2(1,0) = tmp(1,0) - M1(1,0);
  JRL_MAL_ASSERT(isMatrixNull(tmp2)
              && "test value conservation while resizing matrix");

  // Check fill with constant method
  MAL_MATRIX_RESIZE(M1, 2, 2);
  FloatType x = randomFloat();
  MAL_MATRIX_FILL(M1,x);
  JRL_MAL_ASSERT(M1(0,0) == x
              && M1(0,1) == x
              && M1(1,0) == x
              && M1(1,1) == x
              && "test filling matrix with constant");

  // Check reset method
  MAL_MATRIX_CLEAR(M1);
  JRL_MAL_ASSERT(isMatrixNull(M1)
              && "test matrix reset method");

  // All assertions true, test is passed
  std::cout << "Mal v1 : Matrix modifiors test has succeeded." << std::endl;
}

GENERATE_TEST()
