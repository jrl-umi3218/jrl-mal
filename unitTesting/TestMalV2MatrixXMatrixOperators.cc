/* 
Test Matrix class
*/

#include "assertion.hh"
#include "malv2utils.hh"

/* 
Test Matrix x Matrix operations
*/
void run_test()
{
  srand(time(NULL));
  Matrix m1(2,2), m2(1,2), m3(2,3), m4, tmp_m(2,2);
  Vector v1(3), v2, tmp_v(3);
  FloatType x = randomFloat();
  setRandom(m1,2,2); setRandom(m2,1,2); setRandom(m3,2,3);
  setRandom(v1,3);

/* Product */
  // Test matrix * matrix
  m4 = m1.multiply(m1);
  manuallyComputedProduct(m1,m1,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,2)");

  m4 = m2.multiply(m1);
  manuallyComputedProduct(m2,m1,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,2)");

  m4 = m1.multiply(m3);
  manuallyComputedProduct(m1,m3,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(2,2)*M(2,3)");

  m4 = m2.multiply(m3);
  manuallyComputedProduct(m2,m3,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M(1,2)*M(2,3)");

  // Test matrix x vector
  v2 = m3.multiply(v1);
  manuallyComputedProduct(m3,v1,tmp_v);
  tmp_v = tmp_v - v2;
  JRL_MAL_ASSERT(isVectorNull(tmp_v)
              && "test M(2,3)*V(3)");

  // Test matrix x float
  m4 = m1.multiply(x);
  manuallyComputedProduct(m1,x,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M*float");

/* Addition */
  // Test matrix + matrix
  setRandom(m1,3,3); setRandom(m2,3,3);
  m4 = m1.addition(m2);
  manuallyComputedAddition(m1,m2,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M+M");

  x = randomFloat();
  m4 = m1.addition(x);
  manuallyComputedAddition(m1,x,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M+Float");

/* Substraction */
  // Test matrix - matrix
  m4 = m1.substraction(m2);
  manuallyComputedSubstraction(m1,m2,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M-M");

  m4 = m1.substraction(x);
  manuallyComputedSubstraction(m1,x,tmp_m);
  tmp_m = tmp_m - m4;
  JRL_MAL_ASSERT(isMatrixNull(tmp_m)
              && "test M-Float");

  // All assertions true, test is passed
  std::cout << "Matrix x matrix operations test has succeeded." << std::endl;
}

GENERATE_TEST()
