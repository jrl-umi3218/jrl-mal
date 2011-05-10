/* 
Test Vector macros
*/

#include "assertion.hh"
#include "malv1utils.hh"

void run_test()
{
  MAL_VECTOR_DIM(V1,    FloatType, 3);
  MAL_VECTOR_DIM(V2,    FloatType, 4);

  // Check vector size accessor
  JRL_MAL_ASSERT(MAL_VECTOR_SIZE(V1) == 3
              && "test vector size accessor");

  // Check raw data vector accessor
  V2(0) = 1; V2(1) = 2; V2(2) = 3; V2(3) = 4;
  FloatType *rawV2 = MAL_RET_VECTOR_DATABLOCK(V2);
  JRL_MAL_ASSERT(V2(0) == rawV2[0]
              && V2(1) == rawV2[1]
              && V2(2) == rawV2[2]
              && V2(3) == rawV2[3]
              && "test vector raw data accessor");

  // All assertions true, test is passed
  std::cout << "Vector accessors test has succeeded." << std::endl;
}

GENERATE_TEST()
