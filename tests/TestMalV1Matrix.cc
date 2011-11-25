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
#define BOOST_TEST_MODULE Mal_V1_Matrix

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "malv1utils.hh"


BOOST_AUTO_TEST_CASE (malv1_matrix_accessors)
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M1,    FloatType, 3, 1);
  MAL_MATRIX_DIM(M2,    FloatType, 2, 2);
  MAL_MATRIX_DIM(M3,    FloatType, 4, 4);
  MAL_MATRIX_DIM(subM3, FloatType, 2, 2);
  MAL_MATRIX_DIM(tmp,   FloatType, 2, 2);
  setRandom(M3, 4, 4);

  // Check matrix size accessors
  BOOST_CHECK (MAL_MATRIX_NB_ROWS(M1) == 3
            && MAL_MATRIX_NB_COLS(M1) == 1
            && "test matrix size accessors");

  // Check raw data matrix accessor
  M2(0,0) = 1; M2(0,1) = 2; M2(1,0) = 3; M2(1,1) = 4;
  FloatType *rawM2 = MAL_RET_MATRIX_DATABLOCK(M2);
  BOOST_CHECK (M2(0,0) == rawM2[0]
            && M2(0,1) == rawM2[1]
            && M2(1,0) == rawM2[2]
            && M2(1,1) == rawM2[3]
            && "test matrix raw data accessor");

  // Check sub-matrix extraction
  MAL_MATRIX_C_eq_EXTRACT_A(subM3, M3, FloatType, 0, 0, 2, 2);
  manuallyComputedSubMatrix(M3, 0, 0, 2, 2, tmp);
  tmp = tmp - subM3;
  BOOST_CHECK (isMatrixNull(tmp)
            && "correct sub-matrix extraction #1");

  MAL_MATRIX_C_eq_EXTRACT_A(subM3, M3, FloatType, 1, 1, 1, 2);
  manuallyComputedSubMatrix(M3, 1, 1, 1, 2, tmp);
  tmp = tmp - subM3;
  BOOST_CHECK (isMatrixNull(tmp)
            && "correct sub-matrix extraction #2");

  MAL_MATRIX_C_eq_EXTRACT_A(subM3, M3, FloatType, 1, 0, 3, 4);
  manuallyComputedSubMatrix(M3, 1, 0, 3, 4, tmp);
  tmp = tmp - subM3;
  BOOST_CHECK (isMatrixNull(tmp)
            && "correct sub-matrix extraction #3");
}

BOOST_AUTO_TEST_CASE (malv1_matrix_modifiors)
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M1,   FloatType, 3, 1);
  MAL_MATRIX_DIM(M2,   FloatType, 2, 2);
  MAL_MATRIX_DIM(M3,   FloatType, 2, 2);
  MAL_MATRIX_DIM(tmp,  FloatType, 2, 2);
  MAL_MATRIX_DIM(tmp2, FloatType, 2, 2);

  // Check matrix resize
  MAL_MATRIX_RESIZE(M1, 2, 2);
  BOOST_CHECK (MAL_MATRIX_NB_ROWS(M1) == 2
              && MAL_MATRIX_NB_COLS(M1) == 2
              && "test matrix resize");

  // Check value conservation while resizing
  setRandom(M1, 2, 2);
  tmp = M1;
  MAL_MATRIX_RESIZE(M1, 3, 1);
  tmp2(0,0) = tmp(0,0) - M1(0,0);
  tmp2(1,0) = tmp(1,0) - M1(1,0);
  BOOST_CHECK (isMatrixNull(tmp2)
              && "test value conservation while resizing matrix");

  // Check fill with constant method
  MAL_MATRIX_RESIZE(M1, 2, 2);
  FloatType x = randomFloat();
  MAL_MATRIX_FILL(M1,x);
  BOOST_CHECK (M1(0,0) == x
              && M1(0,1) == x
              && M1(1,0) == x
              && M1(1,1) == x
              && "test filling matrix with constant");

  // Check reset method
  MAL_MATRIX_CLEAR(M1);
  BOOST_CHECK (isMatrixNull(M1)
              && "test matrix reset method");
}

BOOST_AUTO_TEST_CASE (malv1_matrix_set_identity)
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M1,   FloatType, 2, 2);
  MAL_MATRIX_DIM(M2,   FloatType, 3, 2);
  MAL_MATRIX_DIM(M3,   FloatType, 2, 3);

  MAL_MATRIX_FILL(M1,2); MAL_MATRIX_FILL(M2,2); MAL_MATRIX_FILL(M3,2);

  // Check set to identity macro with square matrix
  MAL_MATRIX_SET_IDENTITY(M1);
  BOOST_CHECK (M1(0,0) == 1 && M1(0,1) == 0
              && M1(1,0) == 0 && M1(1,1) == 1
              && "test set square matrix to identity matrix");

  // Check set to identity macro with square matrix
  MAL_MATRIX_SET_IDENTITY(M2);
  BOOST_CHECK (M2(0,0) == 1 && M2(0,1) == 0
              && M2(1,0) == 0 && M2(1,1) == 1
              && M2(2,0) == 0 && M2(2,1) == 0
              && "test set non-square matrix to identity matrix #1");

  MAL_MATRIX_SET_IDENTITY(M3);
  BOOST_CHECK (M3(0,0) == 1 && M3(0,1) == 0 && M3(0,2) == 0
              && M3(1,0) == 0 && M3(1,1) == 1 && M3(1,2) == 0
              && "test set non-square matrix to identity matrix #2");
}

BOOST_AUTO_TEST_CASE (malv1_matrix_transpose)
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M, FloatType, 10, 10);
  MAL_MATRIX(tmp, FloatType);

  // Case of a square matrix
  setRandom(M, 10, 10);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  BOOST_CHECK (isMatrixNull(tmp)
              && "test transpose of square matrix");

  // Case of a non-square matrix
  setRandom(M, 5, 15);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  BOOST_CHECK (isMatrixNull(tmp)
              && "test transpose of non-square matrix #1");
  
  setRandom(M, 15, 5);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  BOOST_CHECK (isMatrixNull(tmp)
              && "test transpose of non-square matrix #2");
}

BOOST_AUTO_TEST_CASE (malv1_matrix_product)
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
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,2)");

  M4 = MAL_RET_A_by_B(M2,M1);
  manuallyComputedProduct(M2,M1,tmp_m);
  tmp_m = tmp_m - M4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,2)");

  M4 = MAL_RET_A_by_B(M1,M3);
  manuallyComputedProduct(M1,M3,tmp_m);
  tmp_m = tmp_m - M4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,3)");

  M4 = MAL_RET_A_by_B(M2,M3);
  manuallyComputedProduct(M2,M3,tmp_m);
  tmp_m = tmp_m - M4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,3)");

  // Test matrix x vector
  V2 = MAL_RET_A_by_B(M3,V1);
  manuallyComputedProduct(M3,V1,tmp_v);
  tmp_v = tmp_v - V2;
  BOOST_CHECK (isVectorNull(tmp_v)
              && "test M(2,3)*V(3)");
}

BOOST_AUTO_TEST_CASE (malv1_matrix_inverse)
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
  BOOST_CHECK (isMatrixNull(tmp)
            && "test matrix inverse property: M*invM = I");

  tmp = MAL_RET_A_by_B(invM, M) - I;
  BOOST_CHECK (isMatrixNull(tmp)
            && "test matrix inverse property: invM*M = I");
}
