/* 
Test Matrix class
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Matrix norm methods
*/
void run_test()
{
  Matrix m1(2,2);
//  m1(0,0) = 1.0; m1(0,1) = 2.0; m1(1,0) = -3.0; m1(1,1) = 4.0;
  setRandom(m1,2,2);
  FloatType x, tmp;
 
  // Test norm1
  x = m1.norm1();
  tmp = manuallyComputedNorm1(m1);
  JRL_MAL_ASSERT(x == tmp
              && "matrix.norm1() is equal to manually computed norm1");

  // Test norm infinity
  x = m1.normInfty();
  tmp = manuallyComputedNormInfty(m1);
  JRL_MAL_ASSERT(x == tmp
              && "matrix.normInfty() is equal to manually computed norm infinity");

  // All assertions true, test is passed
  std::cout << "Matrix norm methods test has succeeded." << std::endl;
}

GENERATE_TEST()
