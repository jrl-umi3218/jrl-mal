/* 
Test Matrix macros 
*/

#include "assertion.hh"
#include "malv1utils.hh"

/* 
Test Matrix inverse macro
*/
void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M, FloatType, 10, 10);
  MAL_MATRIX(invM, FloatType);
  MAL_MATRIX_DIM(I, FloatType, 10, 10);
  MAL_MATRIX(tmp, FloatType);
  MAL_MATRIX_SET_IDENTITY(I);
  
  setRandom(M, 10,10);
  MAL_INVERSE(M, invM, FloatType);
  tmp = MAL_RET_A_by_B(M, invM) - I;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: M*invM = I");
  tmp = MAL_RET_A_by_B(invM, M) - I;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: invM*M = I");

  std::cout << "Matrix inverse test has succeeded." << std::endl;
}

GENERATE_TEST()
