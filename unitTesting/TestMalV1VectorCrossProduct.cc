/* 
Test Vector macros
*/

#include "assertion.hh"
#include "malv1utils.hh"

void run_test()
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
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test vector cross product");

  // All assertions true, test is passed
  std::cout << "Vector cross product test has succeeded." << std::endl;
}

GENERATE_TEST()
