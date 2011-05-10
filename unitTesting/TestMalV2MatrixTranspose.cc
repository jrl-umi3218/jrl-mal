/* 
Test Matrix class 
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Matrix transpose method
*/

void run_test()
{
  srand(time(NULL));
  Matrix M(10,10), tmp;
  // Case of a square matrix
  setRandom(M, 10, 10);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - M.transpose();
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of square matrix");

  // Case of a non-square matrix
  setRandom(M, 5, 15);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - M.transpose();
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of non-square matrix #1");
  
  setRandom(M, 15, 5);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - M.transpose();
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of non-square matrix #2");
  

  std::cout << "Matrix transpose test has succeeded." << std::endl;
}

GENERATE_TEST()
