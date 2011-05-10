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

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test of Matrix class accessors
*/
void run_test()
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
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct raw data access in row major matrix");


  // Check element accessor
  for(unsigned int i=0; i<m1.nbRows(); i++)
  {
    for(unsigned int j=0; j<m1.nbCols(); j++)
    {
      tmp(i,j) = m1(i,j) - m1(m1.nbCols()*i + j);
    }
  }
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct raw single-indexed element access in row major matrix");

  // Check sub-matrix extraction
  sub_m1 = m1.extract(0,0,2,2);
  manuallyComputedSubMatrix(m1, 0, 0, 2, 2, tmp);
  tmp = tmp - sub_m1;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct sub-matrix extraction #1");

  sub_m1 = m1.extract(1,1,1,2);
  manuallyComputedSubMatrix(m1, 1, 1, 1, 2, tmp);
  tmp = tmp - sub_m1;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct sub-matrix extraction #2");

  sub_m1 = m1.extract(1,0,3,4);
  manuallyComputedSubMatrix(m1, 1, 0, 3, 4, tmp);
  tmp = tmp - sub_m1;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "correct sub-matrix extraction #3");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Matrix accessors test has succeeded." << std::endl;
}

GENERATE_TEST()
