/* 
Test Matrix class
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test of Matrix class modifior methods
*/
void run_test()
{
  srand(time(NULL));
  Matrix m1(2,2), m2(2,2), m3(2,2), tmp1(2,2), tmp2(3,1);
  setRandom(m1, 2, 2);

  // Check resize without value reset
  tmp1 = m1;
  m1.resize(3, 1, false);
  tmp2(0,0) = tmp1(0,0) - m1(0,0);
  tmp2(1,0) = tmp1(1,0) - m1(1,0);
  JRL_MAL_ASSERT(m1.nbRows() == 3
              && m1.nbCols() == 1
              && isMatrixNull(tmp2)
              && "test resize matrix without value reset");

  // Check resize with reset
  m1.resize(2, 2, true); // FIXME: For some reason, non-preservative resize does not clear the matrix with Boost, hence the failing test.
  JRL_MAL_ASSERT(m1.nbRows() == 2
              && m1.nbCols() == 2
              && isMatrixNull(m1)
              && "test matrix resize with value reset");

  // Check fill with constant method
  FloatType x = randomFloat();
  m1.fill(x);
  JRL_MAL_ASSERT(m1(0,0) == x
              && m1(0,1) == x
              && m1(1,0) == x
              && m1(1,1) == x
              && "test filling matrix with constant");

  // Check opposite method
  m1.opposite(m2);
  JRL_MAL_ASSERT(m2(0,0) == -x
              && m2(0,1) == -x
              && m2(1,0) == -x
              && m2(1,1) == -x
              && "test matrix opposite method");

  // Check reset method
  m1.setZero();
  JRL_MAL_ASSERT(isMatrixNull(m1)
              && "test matrix reset method");

  // All assertions true, test is passed
  std::cout << "Matrix modifiors test has succeeded." << std::endl;
}

GENERATE_TEST()
