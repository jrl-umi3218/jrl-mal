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
 * Test Vector macros
 */

#include "assertion.hh"
#include "malv1utils.hh"

void run_test()
{
  srand(time(NULL));
  MAL_VECTOR_DIM(V1,  FloatType, 5);
  FloatType x, tmp;
  setRandom(V1, 5);

  // Check vector norm
  x = MAL_VECTOR_NORM(V1);
  manuallyComputedVectorNorm(V1, tmp);
  tmp = (fabs(tmp-x) < 1e-6)?0:tmp-x;;
  JRL_MAL_ASSERT(tmp == 0
              && "test vector norm");

  // All assertions true, test is passed
  std::cout << "Mal v1 : Vector norm test has succeeded." << std::endl;
}

GENERATE_TEST()
