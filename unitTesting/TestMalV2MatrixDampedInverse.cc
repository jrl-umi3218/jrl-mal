/* 
Test Matrix class 
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Matrix damped-inverse method
*/
void run_test()
{
  srand(time(NULL));
  Matrix M(10,10), invM, tmp;
  
  // Case of a square matrix
  setRandom(M, 10,10);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a square matrix: (invM*M)T = invM*M");

  // Case of a non-square matrix
  setRandom(M, 5,15);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #1: (invM*M)T = invM*M");

  setRandom(M, 15,5);
  M.pseudoInverse(invM);
  tmp = M*invM*M - M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: M*invM*M = M");
  tmp = invM*M*invM - invM; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: invM*M*invM = invM");
  tmp = (M*invM).transpose() - M*invM;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: (M.invM)T = M*invM");
  tmp = (invM*M).transpose() - invM*M;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix damped inverse property for a non-square matrix #2: (invM*M)T = invM*M");

  std::cout << "Matrix damped-inverse test has succeeded." << std::endl;
}

GENERATE_TEST()
