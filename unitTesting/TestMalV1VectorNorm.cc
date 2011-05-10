/* 
Test Vector macros
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
  std::cout << "Vector norm test has succeeded." << std::endl;
}

GENERATE_TEST()
