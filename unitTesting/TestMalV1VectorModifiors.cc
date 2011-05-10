/* 
Test Vector macros
*/

#include "assertion.hh"
#include "malv1utils.hh"

void run_test()
{
  srand(time(NULL));
  MAL_VECTOR_DIM(V1,   FloatType, 3);
  MAL_VECTOR_DIM(V2,   FloatType, 2);
  MAL_VECTOR_DIM(V3,   FloatType, 2);
  MAL_VECTOR_DIM(tmp,  FloatType, 2);
  MAL_VECTOR_DIM(tmp2, FloatType, 2);

  // Check vector resize
  MAL_VECTOR_RESIZE(V1, 2);
  JRL_MAL_ASSERT(MAL_VECTOR_SIZE(V1) == 2
              && "test vector resize");

  // Check value conservation while resizing
  setRandom(V1, 2);
  tmp = V1;
  MAL_VECTOR_RESIZE(V1, 3);
  tmp2(0) = tmp(0) - V1(0);
  tmp2(1) = tmp(1) - V1(1);
  JRL_MAL_ASSERT(isVectorNull(tmp2)
              && "test value conservation while resizing vector");

  // Check fill with constant method
  MAL_VECTOR_RESIZE(V1, 4);
  FloatType x = randomFloat();
  MAL_VECTOR_FILL(V1,x);
  JRL_MAL_ASSERT(V1(0) == x
              && V1(1) == x
              && V1(2) == x
              && V1(3) == x
              && "test filling vector with constant");

  // All assertions true, test is passed
  std::cout << "Vector modifiors test has succeeded." << std::endl;
}

GENERATE_TEST()
