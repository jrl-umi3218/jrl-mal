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
Test of Matrix class set to identity method
*/
void run_test()
{
  Matrix m1(2,2), m2(3,2), m3(2,3);
  m1.fill(2); m2.fill(2); m3.fill(2);

  // Square matrix
  m1.setIdentity();
  JRL_MAL_ASSERT(m1(0,0) == 1 && m1(0,1) == 0
              && m1(1,0) == 0 && m1(1,1) == 1
              && "test set square matrix to identity matrix");

  // Non-square matrix
  m2.setIdentity();
  JRL_MAL_ASSERT(m2(0,0) == 1 && m2(0,1) == 0
              && m2(1,0) == 0 && m2(1,1) == 1
              && m2(2,0) == 0 && m2(2,1) == 0
              && "test set non-square matrix to identity matrix #1");

  m3.setIdentity();
  JRL_MAL_ASSERT(m3(0,0) == 1 && m3(0,1) == 0 && m3(0,2) == 0
              && m3(1,0) == 0 && m3(1,1) == 1 && m3(1,2) == 0
              && "test set non-square matrix to identity matrix #2");

  // All assertions true, test is passed
  std::cout << "Mal v2 : Matrix set to identity test has succeeded." << std::endl;
}

GENERATE_TEST()
