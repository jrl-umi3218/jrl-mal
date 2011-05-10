/* 
Test Matrix macros
*/

#include "assertion.hh"
#include "malv1utils.hh"

void run_test()
{
  srand(time(NULL));
  MAL_MATRIX_DIM(M1,   FloatType, 2, 2);
  MAL_MATRIX_DIM(M2,   FloatType, 3, 2);
  MAL_MATRIX_DIM(M3,   FloatType, 2, 3);

  MAL_MATRIX_FILL(M1,2); MAL_MATRIX_FILL(M2,2); MAL_MATRIX_FILL(M3,2);

  // Check set to identity macro with square matrix
  MAL_MATRIX_SET_IDENTITY(M1);
  JRL_MAL_ASSERT(M1(0,0) == 1 && M1(0,1) == 0
              && M1(1,0) == 0 && M1(1,1) == 1
              && "test set square matrix to identity matrix");

  // Check set to identity macro with square matrix
  MAL_MATRIX_SET_IDENTITY(M2);
  JRL_MAL_ASSERT(M2(0,0) == 1 && M2(0,1) == 0
              && M2(1,0) == 0 && M2(1,1) == 1
              && M2(2,0) == 0 && M2(2,1) == 0
              && "test set non-square matrix to identity matrix #1");

  MAL_MATRIX_SET_IDENTITY(M3);
  JRL_MAL_ASSERT(M3(0,0) == 1 && M3(0,1) == 0 && M3(0,2) == 0
              && M3(1,0) == 0 && M3(1,1) == 1 && M3(1,2) == 0
              && "test set non-square matrix to identity matrix #2");


  // All assertions true, test is passed
  std::cout << "Matrix modifiors test has succeeded." << std::endl;
}

GENERATE_TEST()
