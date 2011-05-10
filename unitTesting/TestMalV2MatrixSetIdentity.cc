/* 
Test Matrix class
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test of Matrix class set to identity method
*/
void run_test()
{
  Matrix m1(2,2), m2(3,2), m3(2,3);
  m1.fill(2); m2.fill(2); m3.fill(2);

  // Square matrix
  m1.setIdentity();
  JRL_MAL_ASSERT(m1(0,0) == 1 && m1(0,1) == 0
              && m1(1,0) == 0 && m1(1,1) == 1
              && "test set square matrix to identity matrix");

  // Non-square matrix
  m2.setIdentity();
  JRL_MAL_ASSERT(m2(0,0) == 1 && m2(0,1) == 0
              && m2(1,0) == 0 && m2(1,1) == 1
              && m2(2,0) == 0 && m2(2,1) == 0
              && "test set non-square matrix to identity matrix #1");

  m3.setIdentity();
  JRL_MAL_ASSERT(m3(0,0) == 1 && m3(0,1) == 0 && m3(0,2) == 0
              && m3(1,0) == 0 && m3(1,1) == 1 && m3(1,2) == 0
              && "test set non-square matrix to identity matrix #2");

  // All assertions true, test is passed
  std::cout << "Matrix set to identity test has succeeded." << std::endl;
}

GENERATE_TEST()
