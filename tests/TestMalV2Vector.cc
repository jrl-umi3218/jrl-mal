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
 * Test Vector class
 */

#define BOOST_TEST_MODULE Mal_V2_Vector

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "malv2utils.hh"

BOOST_AUTO_TEST_CASE (malv2_vector_constructors)
{
  internalVector _m(3);
  _m(0) = 1.0; _m(1) = 2.0; _m(2) = 3.0;
  Vector v1(3),     // Create size 3 internal vector
         v2(&_m),   // Build capsule around existing size 3 eigen vector
         v3(v2);    // Create copy of existing size 3 vector
  // Check size
  BOOST_CHECK (v1.size() == 3
              && "test vector size after initialisation through internal vector creation");
  BOOST_CHECK (v2.size() == 3
              && "test vector size after initialisation through existing internal vector encapsulation");
  BOOST_CHECK (v3.size() == 3
              && "test vector size after initialisation through existing internal vector copy");

  // Check internal vector values when creating a new vector, encapsuling or copying an existing one
  BOOST_CHECK (v2(0) == 1
              && v2(1) == 2
              && v2(2) == 3
              && "test vector values after initialisation through existing internal vector encapsulation");
  BOOST_CHECK (v3(0) == 1
              && v3(1) == 2
              && v3(2) == 3
              && "test vector values after initialisation through existing internal vector copy");
}

BOOST_AUTO_TEST_CASE (malv2_vector_accessors)
{
  Vector v1(4), sub_v1(2), tmp(4);
  setRandom(v1,4);
  FloatType *raw_v1;

  // Check raw data accessor
  raw_v1 = v1.datablock();
  for(unsigned int i=0; i<v1.size(); i++)
  {
    tmp(i) = raw_v1[i];
  }
  tmp = tmp - v1;
  BOOST_CHECK (isVectorNull(tmp)
              && "test raw data access in vector");

  // Check sub-matrix extraction
  sub_v1 = v1.extract(0,2);
  manuallyComputedSubVector(v1, 0, 2, tmp);
  tmp = tmp - sub_v1;
  BOOST_CHECK (isVectorNull(tmp)
              && "test sub-vector extraction #1");

  sub_v1 = v1.extract(1,3);
  manuallyComputedSubVector(v1, 1, 3, tmp);
  tmp = tmp - sub_v1;
  BOOST_CHECK (isVectorNull(tmp)
              && "test sub-vector extraction #2");
}

BOOST_AUTO_TEST_CASE (malv2_vector_modifiors)
{
  srand(time(NULL));
  Vector v1(3), v2(3), tmp(3);
  setRandom(v1, 3); setRandom(v2, 2);

  // Check resize without value reset
  tmp = v1;
  v1.resize(2, false);
  tmp(0) = tmp(0) - v1(0);
  tmp(1) = tmp(1) - v1(1);
  tmp(2) = 0;
  BOOST_CHECK (v1.size() == 2
              && isVectorNull(tmp)
              && "test vector resize without value reset");

  // Check resize with reset
  v1.resize(3);
  BOOST_CHECK (v1.size() == 3
              && isVectorNull(v1)
              && "test vector resize with value reset");

  // Check fill with constant method
  FloatType x = randomFloat();
  v1.fill(x);
  BOOST_CHECK ((v1(0) == x)
              && (v1(1) == x)
              && (v1(2) == x)
              && "test filling vector with constant");

  // Check opposite method
  v1.opposite(v2);
  BOOST_CHECK ((v2(0) == -x)
              && (v2(1) == -x)
              && (v2(2) == -x)
              && "test vector opposite method");

  // Check reset method
  v1.setZero();
  BOOST_CHECK (isVectorNull(v1)
              && "test vector reset method");
}

BOOST_AUTO_TEST_CASE (malv2_vector_norm)
{
  Vector v1(3);
  v1(0) = 1.0; v1(1) = 2.0; v1(2) = -3.0;
  FloatType x, tmp;
  
  // Test euclidian norm
  x = v1.norm();
  tmp = sqrt(v1(0)*v1(0)+v1(1)*v1(1)+v1(2)*v1(2));
  std::clog << "NORM TEST"         << std::endl
            << "  v1.norm = " << x << std::endl
            << "  tmp = " << tmp   << std::endl;
  BOOST_CHECK (x == tmp
              && "test vector norm");

  // Test norm1
  x = v1.norm1();
  tmp = fabs(v1(0)) + fabs(v1(1)) + fabs(v1(2));
  BOOST_CHECK (x == tmp
              && "test vector norm1");

  // Test norm infinity
  x = v1.normInfty();
  tmp = std::max(std::max(fabs(v1(0)), fabs(v1(1))), fabs(v1(2)));
  BOOST_CHECK (x == tmp
              && "test vector norm infinity");
}

BOOST_AUTO_TEST_CASE (malv2_vector_x_vector_operations)
{
  srand(time(NULL));
  Vector v1(3), v2(3), v3(3), tmp(3);
  FloatType x = randomFloat();
  FloatType scalarProduct, tmp1;
  setRandom(v1,3); setRandom(v2,3);

  // Test vector * vector
  v3 = v1.multiply(v2);
  tmp(0) = v1(0)*v2(0);
  tmp(1) = v1(1)*v2(1);
  tmp(2) = v1(2)*v2(2);
  tmp = tmp - v3;
  BOOST_CHECK (isVectorNull(tmp)
              && "test vector * vector product");

  // Test vector * scalar
  v3 = v1.multiply(x);
  tmp(0) = v1(0)*x;
  tmp(1) = v1(1)*x;
  tmp(2) = v1(2)*x;
  tmp = tmp - v3;
  BOOST_CHECK (isVectorNull(tmp)
              && "test vector * scalar product");

  // Test vector + vector
  v3 = v1.addition(v2);
  tmp(0) = v1(0)+v2(0);
  tmp(1) = v1(1)+v2(1);
  tmp(2) = v1(2)+v2(2);
  tmp = tmp - v3;
  BOOST_CHECK (isVectorNull(tmp)
              && "test vector * vector addition");

  // Test vector - vector
  v3 = v1.substraction(v2);
  tmp(0) = v1(0)-v2(0);
  tmp(1) = v1(1)-v2(1);
  tmp(2) = v1(2)-v2(2);
  tmp = tmp - v3;
  BOOST_CHECK (isVectorNull(tmp)
              && "test vector * vector substraction");

  // Test vector cross product
  v3 = v1.crossProduct(v2);
  tmp(0) = v1(1)*v2(2)-v2(1)*v1(2);
  tmp(1) = v1(2)*v2(0)-v2(2)*v1(0);
  tmp(2) = v1(0)*v2(1)-v2(0)*v1(1);
  tmp = tmp - v3;
  BOOST_CHECK (isVectorNull(tmp)
              && "test vector cross product");

  // Test scalar product
  scalarProduct = v1.scalarProduct(v2);
  tmp1 = v1(0)*v2(0) + v1(1)*v2(1) + v1(2)*v2(2);
  BOOST_CHECK (fabs(scalarProduct-tmp1)<1e-6
              && "test vector scalar product");
}
