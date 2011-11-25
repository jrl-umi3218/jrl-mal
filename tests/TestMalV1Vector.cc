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
#define BOOST_TEST_MODULE Mal_V1_Vector

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "malv1utils.hh"

BOOST_AUTO_TEST_CASE (malv1_vector_accessors)
{
  MAL_VECTOR_DIM(V1,    FloatType, 3);
  MAL_VECTOR_DIM(V2,    FloatType, 4);

  // Check vector size accessor
  BOOST_CHECK (MAL_VECTOR_SIZE(V1) == 3
              && "test vector size accessor");

  // Check raw data vector accessor
  V2(0) = 1; V2(1) = 2; V2(2) = 3; V2(3) = 4;
  FloatType *rawV2 = MAL_RET_VECTOR_DATABLOCK(V2);
  BOOST_CHECK (V2(0) == rawV2[0]
              && V2(1) == rawV2[1]
              && V2(2) == rawV2[2]
              && V2(3) == rawV2[3]
              && "test vector raw data accessor");
}

BOOST_AUTO_TEST_CASE (malv1_vector_modifiors)
{
  srand(time(NULL));
  MAL_VECTOR_DIM(V1,   FloatType, 3);
  MAL_VECTOR_DIM(V2,   FloatType, 2);
  MAL_VECTOR_DIM(V3,   FloatType, 2);
  MAL_VECTOR_DIM(tmp,  FloatType, 2);
  MAL_VECTOR_DIM(tmp2, FloatType, 2);

  // Check vector resize
  MAL_VECTOR_RESIZE(V1, 2);
  BOOST_CHECK (MAL_VECTOR_SIZE(V1) == 2
              && "test vector resize");

  // Check value conservation while resizing
  setRandom(V1, 2);
  tmp = V1;
  MAL_VECTOR_RESIZE(V1, 3);
  tmp2(0) = tmp(0) - V1(0);
  tmp2(1) = tmp(1) - V1(1);
  BOOST_CHECK (isVectorNull(tmp2)
              && "test value conservation while resizing vector");

  // Check fill with constant method
  MAL_VECTOR_RESIZE(V1, 4);
  FloatType x = randomFloat();
  MAL_VECTOR_FILL(V1,x);
  BOOST_CHECK (V1(0) == x
              && V1(1) == x
              && V1(2) == x
              && V1(3) == x
              && "test filling vector with constant");
}

BOOST_AUTO_TEST_CASE (malv1_vector_corss_product)
{
  srand(time(NULL));
  MAL_VECTOR_DIM(V1,  FloatType, 3);
  MAL_VECTOR_DIM(V2,  FloatType, 3);
  MAL_VECTOR_DIM(V3,  FloatType, 3);
  MAL_VECTOR_DIM(tmp, FloatType, 3);
  setRandom(V1, 3); setRandom(V2, 3);

  // Check vector cross product
  MAL_VECTOR_3D_CROSS_PRODUCT(V3, V1, V2);
  tmp(0) = V1(1)*V2(2)-V2(1)*V1(2);
  tmp(1) = V1(2)*V2(0)-V2(2)*V1(0);
  tmp(2) = V1(0)*V2(1)-V2(0)*V1(1);
  tmp = tmp - V3;
  BOOST_CHECK (isVectorNull(tmp)
              && "test vector cross product");
}

BOOST_AUTO_TEST_CASE (malv1_vector_norm)
{
  srand(time(NULL));
  MAL_VECTOR_DIM(V1,  FloatType, 5);
  FloatType x, tmp;
  setRandom(V1, 5);

  // Check vector norm
  x = MAL_VECTOR_NORM(V1);
  manuallyComputedVectorNorm(V1, tmp);
  tmp = (fabs(tmp-x) < 1e-6)?0:tmp-x;;
  BOOST_CHECK (tmp == 0
              && "test vector norm");
}
