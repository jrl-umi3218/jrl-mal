/* 
Test Matrix macros
*/

#include "assertion.hh"
#include "malv1utils.hh"

/* 
Test Matrix transpose macro
*/

void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M, FloatType, 10, 10);
  MAL_MATRIX(tmp, FloatType);

  // Case of a square matrix
  setRandom(M, 10, 10);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of square matrix");

  // Case of a non-square matrix
  setRandom(M, 5, 15);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of non-square matrix #1");
  
  setRandom(M, 15, 5);
  manuallyComputedTranspose(M,tmp);
  tmp = tmp - MAL_RET_TRANSPOSE(M);
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test transpose of non-square matrix #2");
  

  std::cout << "Matrix transpose test has succeeded." << std::endl;
}

GENERATE_TEST()
