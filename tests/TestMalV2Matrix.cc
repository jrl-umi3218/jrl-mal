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
 * Test Matrix class
 */

#define BOOST_TEST_MODULE Mal_V2_Vector

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "malv2utils.hh"

BOOST_AUTO_TEST_CASE (malv2_matrix_constructors)
{
  internalMatrix _m(2,2);
  _m(0,0) = 1.0; _m(0,1) = 2.0; _m(1,0) = 3.0; _m(1,1) = 4.0;
  Matrix m1(2,2),   // Create size (2,2) internal matrix
         m2(&_m),   // Build capsule around existing size (2,2) eigen matrix
         m3(m2);    // Create copy of existing size (2,2) matrix
  // Check size
  BOOST_CHECK (m1.nbRows() == 2
              && m1.nbCols() == 2
              && "test matrix size after initialisation through internal matrix creation");
  BOOST_CHECK (m2.nbRows() == 2
              && m2.nbCols() == 2
              && "test matrix size after initialisation through existing internal matrix encapsulation");
  BOOST_CHECK (m3.nbRows() == 2
              && m3.nbCols() == 2
              && "test matrix size after initialisation through existing internal matrix copy");

  // Check internal matrix values when encapsuling or copying an existing matrix
  BOOST_CHECK (m2(0,0) == 1 && m2(0,1) == 2
              && m2(1,0) == 3 && m2(1,1) == 4
              && "test matrix values after initialisation through existing internal matrix encapsulation");
  BOOST_CHECK (m3(0,0) == 1 && m3(0,1) == 2
              && m3(1,0) == 3 && m3(1,1) == 4
              && "test matrix values after initialisation through existing internal matrix copy");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_accessors)
{
  Matrix m1(4,4), sub_m1(2,2), tmp(4,4);
  setRandom(m1,4,4);
  FloatType *raw_m1;

  // Check raw data accessor
  raw_m1 = m1.datablock();
  for(unsigned int i=0; i<m1.nbRows(); i++)
  {
    for(unsigned int j=0; j<m1.nbCols(); j++)
    {
      tmp(i,j) = raw_m1[m1.nbCols()*i + j];
    }
  }
  tmp = tmp - m1;
  BOOST_CHECK (isMatrixNull(tmp)
              && "correct raw data access in row major matrix");


  // Check element accessor
  for(unsigned int i=0; i<m1.nbRows(); i++)
  {
    for(unsigned int j=0; j<m1.nbCols(); j++)
    {
      tmp(i,j) = m1(i,j) - m1(m1.nbCols()*i + j);
    }
  }
  BOOST_CHECK (isMatrixNull(tmp)
              && "correct raw single-indexed element access in row major matrix");

  // Check sub-matrix extraction
  sub_m1 = m1.extract(0,0,2,2);
  manuallyComputedSubMatrix(m1, 0, 0, 2, 2, tmp);
  tmp = tmp - sub_m1;
  BOOST_CHECK (isMatrixNull(tmp)
              && "correct sub-matrix extraction #1");

  sub_m1 = m1.extract(1,1,1,2);
  manuallyComputedSubMatrix(m1, 1, 1, 1, 2, tmp);
  tmp = tmp - sub_m1;
  BOOST_CHECK (isMatrixNull(tmp)
              && "correct sub-matrix extraction #2");

  sub_m1 = m1.extract(1,0,3,4);
  manuallyComputedSubMatrix(m1, 1, 0, 3, 4, tmp);
  tmp = tmp - sub_m1;
  BOOST_CHECK (isMatrixNull(tmp)
              && "correct sub-matrix extraction #3");
}


BOOST_AUTO_TEST_CASE (malv2_matrix_modifiors)
{
  srand(time(NULL));
  Matrix m1(2,2), m2(2,2), m3(2,2), tmp1(2,2), tmp2(3,1);
  setRandom(m1, 2, 2);

  // Check resize without value reset
  tmp1 = m1;
  m1.resize(3, 1, false);
  tmp2(0,0) = tmp1(0,0) - m1(0,0);
  tmp2(1,0) = tmp1(1,0) - m1(1,0);
  BOOST_CHECK (m1.nbRows() == 3
              && m1.nbCols() == 1
              && isMatrixNull(tmp2)
              && "test resize matrix without value reset");

  // Check resize with reset
  m1.resize(2, 2, true); // FIXME: For some reason, non-preservative resize does not clear the matrix with Boost, hence the failing test.
  BOOST_CHECK (m1.nbRows() == 2
              && m1.nbCols() == 2
              && "test matrix resize with value reset");

  // Check fill with constant method
  FloatType x = randomFloat();
  m1.fill(x);
  BOOST_CHECK (m1(0,0) == x
              && m1(0,1) == x
              && m1(1,0) == x
              && m1(1,1) == x
              && "test filling matrix with constant");

  // Check opposite method
  m1.opposite(m2);
  BOOST_CHECK (m2(0,0) == -x
              && m2(0,1) == -x
              && m2(1,0) == -x
              && m2(1,1) == -x
              && "test matrix opposite method");

  // Check reset method
  m1.setZero();
  BOOST_CHECK (isMatrixNull(m1)
              && "test matrix reset method");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_set_identity)
{
  Matrix m1(2,2), m2(3,2), m3(2,3);
  m1.fill(2); m2.fill(2); m3.fill(2);

  // Square matrix
  m1.setIdentity();
  BOOST_CHECK (m1(0,0) == 1 && m1(0,1) == 0
              && m1(1,0) == 0 && m1(1,1) == 1
              && "test set square matrix to identity matrix");

  // Non-square matrix
  m2.setIdentity();
  BOOST_CHECK (m2(0,0) == 1 && m2(0,1) == 0
              && m2(1,0) == 0 && m2(1,1) == 1
              && m2(2,0) == 0 && m2(2,1) == 0
              && "test set non-square matrix to identity matrix #1");

  m3.setIdentity();
  BOOST_CHECK (m3(0,0) == 1 && m3(0,1) == 0 && m3(0,2) == 0
              && m3(1,0) == 0 && m3(1,1) == 1 && m3(1,2) == 0
              && "test set non-square matrix to identity matrix #2");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_norms)
{
  Matrix m1(2,2);
//  m1(0,0) = 1.0; m1(0,1) = 2.0; m1(1,0) = -3.0; m1(1,1) = 4.0;
  setRandom(m1,2,2);
  FloatType x, tmp;
 
  // Test norm1
  x = m1.norm1();
  tmp = manuallyComputedNorm1(m1);
  BOOST_CHECK (x == tmp
              && "matrix.norm1() is equal to manually computed norm1");

  // Test norm infinity
  x = m1.normInfty();
  tmp = manuallyComputedNormInfty(m1);
  BOOST_CHECK (x == tmp
              && "matrix.normInfty() is equal to manually computed norm infinity");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_transpose)
{
  srand(time(NULL));
  Matrix M(10,10), tmp;
  // Case of a square matrix
  setRandom(M, 10, 10);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - M.transpose();
  BOOST_CHECK (isMatrixNull(tmp)
              && "test transpose of square matrix");

  // Case of a non-square matrix
  setRandom(M, 5, 15);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - M.transpose();
  BOOST_CHECK (isMatrixNull(tmp)
              && "test transpose of non-square matrix #1");
  
  setRandom(M, 15, 5);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - M.transpose();
  BOOST_CHECK (isMatrixNull(tmp)
              && "test transpose of non-square matrix #2");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_x_matrix_operators)
{
  srand(time(NULL));
  Matrix m1(2,2), m2(1,2), m3(2,3), m4, tmp_m(2,2);
  Vector v1(3), v2, tmp_v(3);
  FloatType x = randomFloat();
  setRandom(m1,2,2); setRandom(m2,1,2); setRandom(m3,2,3);
  setRandom(v1,3);

/* Product */
  // Test matrix * matrix
  m4 = m1.multiply(m1);
  manuallyComputedProduct(m1,m1,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,2)");

  m4 = m2.multiply(m1);
  manuallyComputedProduct(m2,m1,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,2)");

  m4 = m1.multiply(m3);
  manuallyComputedProduct(m1,m3,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,3)");

  m4 = m2.multiply(m3);
  manuallyComputedProduct(m2,m3,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,3)");

  // Test matrix x vector
  v2 = m3.multiply(v1);
  manuallyComputedProduct(m3,v1,tmp_v);
  tmp_v = tmp_v - v2;
  BOOST_CHECK (isVectorNull(tmp_v)
              && "test M(2,3)*V(3)");

  // Test matrix x float
  m4 = m1.multiply(x);
  manuallyComputedProduct(m1,x,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M*float");

/* Addition */
  // Test matrix + matrix
  setRandom(m1,3,3); setRandom(m2,3,3);
  m4 = m1.addition(m2);
  manuallyComputedAddition(m1,m2,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M+M");

  x = randomFloat();
  m4 = m1.addition(x);
  manuallyComputedAddition(m1,x,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M+Float");

/* Substraction */
  // Test matrix - matrix
  m4 = m1.substraction(m2);
  manuallyComputedSubstraction(m1,m2,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M-M");

  m4 = m1.substraction(x);
  manuallyComputedSubstraction(m1,x,tmp_m);
  tmp_m = tmp_m - m4;
  BOOST_CHECK (isMatrixNull(tmp_m)
              && "test M-Float");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_inverse)
{
  srand(time(NULL));
  Matrix M(10,10), invM, I(10,10), tmp;
  I.setIdentity();
  
  setRandom(M, 10,10);
  M.inverse(invM);
  tmp = M*invM - I;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix inverse property: M*invM = I");
  tmp = invM*M - I; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix inverse property: invM*M = I");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_damped_inverse)
{
  srand(time(NULL));
  Matrix M(10,10), invM, tmp;
  
  // Case of a square matrix
  setRandom(M, 10,10);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: (invM*M)T = invM*M");

  // Case of a non-square matrix
  setRandom(M, 5,15);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: (invM*M)T = invM*M");

  setRandom(M, 15,5);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: (invM*M)T = invM*M");
}

BOOST_AUTO_TEST_CASE (malv2_matrix_pseudo_inverse)
{
  srand(time(NULL));
  Matrix M(10,10), invM, tmp;
  
  // Case of a square matrix
  setRandom(M, 10,10);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: (invM*M)T = invM*M");

  // Case of a non-square matrix
  setRandom(M, 5,15);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: (invM*M)T = invM*M");

  setRandom(M, 15,5);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  BOOST_CHECK (isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: (invM*M)T = invM*M");
}
