/* 
Test Vector class
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test of Vector class accessors
*/
void run_test()
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
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test raw data access in vector");

  // Check sub-matrix extraction
  sub_v1 = v1.extract(0,2);
  manuallyComputedSubVector(v1, 0, 2, tmp);
  tmp = tmp - sub_v1;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test sub-vector extraction #1");

  sub_v1 = v1.extract(1,3);
  manuallyComputedSubVector(v1, 1, 3, tmp);
  tmp = tmp - sub_v1;
  JRL_MAL_ASSERT(isVectorNull(tmp)
              && "test sub-vector extraction #2");

  // All assertions true, test is passed
  std::cout << "Vector accessors test has succeeded." << std::endl;
}

GENERATE_TEST()
