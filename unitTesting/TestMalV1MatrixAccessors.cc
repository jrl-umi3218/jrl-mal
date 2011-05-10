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
  MAL_MATRIX_DIM(M1,    FloatType, 3, 1);
  MAL_MATRIX_DIM(M2,    FloatType, 2, 2);
  MAL_MATRIX_DIM(M3,    FloatType, 4, 4);
  MAL_MATRIX_DIM(subM3, FloatType, 2, 2);
  MAL_MATRIX_DIM(tmp,   FloatType, 2, 2);
  setRandom(M3, 4, 4);

  // Check matrix size accessors
  JRL_MAL_ASSERT(MAL_MATRIX_NB_ROWS(M1) == 3
              && MAL_MATRIX_NB_COLS(M1) == 1
              && "test matrix size accessors");

  // Check raw data matrix accessor
  M2(0,0) = 1; M2(0,1) = 2; M2(1,0) = 3; M2(1,1) = 4;
  FloatType *rawM2 = MAL_RET_MATRIX_DATABLOCK(M2);
  JRL_MAL_ASSERT(M2(0,0) == rawM2[0]
              && M2(0,1) == rawM2[1]
              && M2(1,0) == rawM2[2]
              && M2(1,1) == rawM2[3]
              && "test matrix raw data accessor");

  // Check sub-matrix extraction
  MAL_MATRIX_C_eq_EXTRACT_A(subM3, M3, FloatType, 0, 0, 2, 2);
  manuallyComputedSubMatrix(M3, 0, 0, 2, 2, tmp);
  tmp = tmp - subM3;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct sub-matrix extraction #1");

  MAL_MATRIX_C_eq_EXTRACT_A(subM3, M3, FloatType, 1, 1, 1, 2);
  manuallyComputedSubMatrix(M3, 1, 1, 1, 2, tmp);
  tmp = tmp - subM3;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct sub-matrix extraction #2");

  MAL_MATRIX_C_eq_EXTRACT_A(subM3, M3, FloatType, 1, 0, 3, 4);
  manuallyComputedSubMatrix(M3, 1, 0, 3, 4, tmp);
  tmp = tmp - subM3;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct sub-matrix extraction #3");

  // All assertions true, test is passed
  std::cout << "Mal v1 : Matrix accessors test has succeeded." << std::endl;
}

GENERATE_TEST()
