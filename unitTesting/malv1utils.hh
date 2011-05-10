#include <time.h>
#include <jrl/mal/configmal.hh>
#include <jrl/mal/matrixabstractlayer.hh>

typedef double FloatType;

FloatType randomFloat()
{
  return ((FloatType)rand()/RAND_MAX-0.5)*2;
}

void setRandom( MAL_MATRIX_TYPE(FloatType)& M, int nbRows, int nbCols)
{
  MAL_MATRIX_RESIZE(M, nbRows, nbCols);
  FloatType *rawMatrix = MRAWDATA(M);
  for(unsigned int i=0; i<MAL_MATRIX_NB_ROWS(M)*MAL_MATRIX_NB_COLS(M); i++){ rawMatrix[i] = randomFloat(); }
}

void setRandom(MAL_VECTOR_TYPE(FloatType)& V, int size)
{
  MAL_VECTOR_RESIZE(V,size);
  for(unsigned int i=0; i<MAL_VECTOR_SIZE(V); i++){ V(i) = randomFloat(); }
}

bool isMatrixNull(MAL_MATRIX_TYPE(FloatType) M, const double threshold = 1e-6)
{
  bool result = true;
  double* rawMatrix = MRAWDATA(M);
  for(unsigned int i=0; i<MAL_MATRIX_NB_ROWS(M)*MAL_MATRIX_NB_COLS(M); i++)
  {
    if(fabs(rawMatrix[i]) >= threshold) result = false;
  }
  return result;
}

bool isVectorNull(MAL_VECTOR_TYPE(FloatType) vector, const double threshold = 1e-6)
{
  bool result = true;
  for(unsigned int i=0; i<MAL_VECTOR_SIZE(vector); i++)
  {
    if(fabs(vector(i)) >= threshold) result = false;
  }
  return result;
}

void manuallyComputedTranspose(MAL_MATRIX_TYPE(FloatType) M, MAL_MATRIX_TYPE(FloatType)& result)
{
  MAL_MATRIX_RESIZE(result, MAL_MATRIX_NB_COLS(M), MAL_MATRIX_NB_ROWS(M));
  for(unsigned int i=0; i<MAL_MATRIX_NB_ROWS(result); i++)
  {
    for(unsigned int j=0; j<MAL_MATRIX_NB_COLS(result); j++){ result(i,j) = M(j,i); }
  }
}

void manuallyComputedProduct(MAL_MATRIX_TYPE(FloatType)& M1, MAL_MATRIX_TYPE(FloatType)& M2, MAL_MATRIX_TYPE(FloatType)& result)
{
  MAL_MATRIX_RESIZE(result, MAL_MATRIX_NB_ROWS(M1), MAL_MATRIX_NB_COLS(M2));
  for(unsigned int i=0; i<MAL_MATRIX_NB_ROWS(result); i++)
  {
    for(unsigned int j=0; j<MAL_MATRIX_NB_COLS(result); j++)
    {
      result(i,j) = 0;
      for(unsigned int k=0; k<MAL_MATRIX_NB_COLS(M1); k++){ result(i,j) += M1(i,k)*M2(k,j); }
    }
  }
} 

void manuallyComputedProduct(MAL_MATRIX_TYPE(FloatType)& M1, MAL_VECTOR_TYPE(FloatType)& V1, MAL_VECTOR_TYPE(FloatType)& result)
{
  MAL_VECTOR_RESIZE(result, MAL_MATRIX_NB_ROWS(M1));
  for(unsigned int i=0; i<MAL_VECTOR_SIZE(result); i++)
  {
    result(i) = 0;
    for(unsigned int k=0; k<MAL_MATRIX_NB_COLS(M1); k++){ result(i) += M1(i,k)*V1(k); }
  }
}

void manuallyComputedProduct(MAL_MATRIX_TYPE(FloatType)& M1, FloatType x, MAL_MATRIX_TYPE(FloatType)& result)
{
  MAL_MATRIX_RESIZE(result, MAL_MATRIX_NB_ROWS(M1), MAL_MATRIX_NB_COLS(M1));
  FloatType *rawM1 = MAL_RET_MATRIX_DATABLOCK(M1), *rawResult = MAL_RET_MATRIX_DATABLOCK(result);
  for(unsigned int i=0; i<MAL_MATRIX_NB_ROWS(result)*MAL_MATRIX_NB_COLS(result); i++)
  {
      rawResult[i] = x*rawM1[i];
  }
}

void manuallyComputedSubMatrix(MAL_MATRIX_TYPE(FloatType)& M, int top, int left, int nbRows, int nbCols, MAL_MATRIX_TYPE(FloatType)& result)
{
  MAL_MATRIX_RESIZE(result, nbRows, nbCols);
  for(int i=0; i<nbRows; i++)
  {
    for(int j=0; j<nbCols; j++)
    {
      result(i,j) = M(i+top,j+left);
    }
  }
}

void manuallyComputedVectorNorm(MAL_VECTOR_TYPE(FloatType) V, FloatType& result)
{
  result = 0;
  for(unsigned int i=0; i<MAL_VECTOR_SIZE(V); i++){ result += V(i)*V(i); }
  result = sqrt(result);
}
