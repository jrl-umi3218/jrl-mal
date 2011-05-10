/* 
Test Matrix class 
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Matrix inverse method
*/
void run_test()
{
  srand(time(NULL));
  Matrix M(10,10), invM, I(10,10), tmp;
  I.setIdentity();
  
  setRandom(M, 10,10);
  M.inverse(invM);
  tmp = M*invM - I;
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: M*invM = I");
  tmp = invM*M - I; 
  JRL_MAL_ASSERT(isMatrixNull(tmp)
              && "test matrix inverse property: invM*M = I");

  std::cout << "Matrix inverse test has succeeded." << std::endl;
}

GENERATE_TEST()
