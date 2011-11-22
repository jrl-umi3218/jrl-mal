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
Test Matrix pseudo-inverse method
*/
void run_test()
{
  srand(time(NULL));
  Matrix M(10,10), invM, tmp;
  
  // Case of a square matrix
  setRandom(M, 10,10);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a square matrix: (invM*M)T = invM*M");

  // Case of a non-square matrix
  setRandom(M, 5,15);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #1: (invM*M)T = invM*M");

  setRandom(M, 15,5);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix pseudo inverse property for a non-square matrix #2: (invM*M)T = invM*M");

  std::cout << "Mal v2 : Matrix pseudo-inverse test has succeeded." << std::endl;
}

GENERATE_TEST()
