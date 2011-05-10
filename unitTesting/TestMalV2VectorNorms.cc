/* 
Test Vector class
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Vector norm methods
*/
void run_test()
{
  Vector v1(3);
  v1(0) = 1.0; v1(1) = 2.0; v1(2) = -3.0;
  FloatType x, tmp;
  
  // Test euclidian norm
  x = v1.norm();
  tmp = sqrt(v1(0)*v1(0)+v1(1)*v1(1)+v1(2)*v1(2));
  JRL_MAL_ASSERT(x == tmp
              && "test vector norm");

  // Test norm1
  x = v1.norm1();
  tmp = fabs(v1(0)) + fabs(v1(1)) + fabs(v1(2));
  JRL_MAL_ASSERT(x == tmp
              && "test vector norm1");

  // Test norm infinity
  x = v1.normInfty();
  tmp = std::max(std::max(fabs(v1(0)), fabs(v1(1))), fabs(v1(2)));
  JRL_MAL_ASSERT(x == tmp
              && "test vector norm infinity");

  // All assertions true, test is passed
  std::cout << "Vector norm methods test has succeeded." << std::endl;
}

GENERATE_TEST()
