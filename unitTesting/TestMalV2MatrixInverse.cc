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
Test Matrix inverse method
*/
void run_test()
{
  srand(time(NULL));
  Matrix M(10,10), invM, I(10,10), tmp;
  I.setIdentity();
  
  setRandom(M, 10,10);
  M.inverse(invM);
  tmp = M*invM - I;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: M*invM = I");
  tmp = invM*M - I; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: invM*M = I");

  std::cout << "Mal v2 : Matrix inverse test has succeeded." << std::endl;
}

GENERATE_TEST()
