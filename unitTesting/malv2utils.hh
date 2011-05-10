#include <time.h>
#include <jrl/mal/configmal.hh>

#if _BOOST_MATRIX_ == 1
#  include <jrl/mal/boost.hh>
   using namespace maal::boost;
   typedef boost::numeric::ublas::vector<FloatType> internalVector;
   typedef boost::numeric::ublas::matrix<FloatType> internalMatrix;
#elif _EIGEN_MATRIX_ == 1
#  include <jrl/mal/eigen.hh>
   using namespace maal::eigen;
   typedef Eigen::Matrix<FloatType, Eigen::Dynamic, 1> internalVector;
   typedef Eigen::Matrix<FloatType, Eigen::Dynamic, Eigen::Dynamic> internalMatrix;
#endif



FloatType randomFloat()
{
  return ((FloatType)rand()/RAND_MAX-0.5)*2;
}

void setRandom(Matrix& M, int nbRows, int nbCols)
{
  M.resize(nbRows, nbCols);
  FloatType *rawMatrix = M.datablock();
  for(unsigned int i=0; i<M.nbCols()*M.nbRows(); i++){ rawMatrix[i] = randomFloat(); }
}

void setRandom(Vector& V, int size)
{
  V.resize(size);
  for(unsigned int i=0; i<V.size(); i++){ V(i) = randomFloat(); }
}

bool isMatrixNull(Matrix matrix, const double threshold = 1e-6)
{
  bool result = true;
  double* rawMatrix = matrix.datablock();
  for(unsigned int i=0; i<matrix.nbRows()*matrix.nbCols(); i++)
  {
    if(fabs(rawMatrix[i]) >= threshold) result = false;
  }
  return result;
}

bool isVectorNull(Vector vector, const double threshold = 1e-6)
{
  bool result = true;
  for(unsigned int i=0; i<vector.size(); i++)
  {
    if(fabs(vector(i)) >= threshold) result = false;
  }
  return result;
}

void manuallyComputedProduct(Matrix& m1, Matrix& m2, Matrix& result)
{
  result.resize(m1.nbRows(), m2.nbCols());
  for(unsigned int i=0; i<result.nbRows(); i++)
  {
    for(unsigned int j=0; j< result.nbCols(); j++)
    {
      result(i,j) = 0;
      for(unsigned int k=0; k<m1.nbCols(); k++){ result(i,j) += m1(i,k)*m2(k,j); }
    }
  }
} 

void manuallyComputedProduct(Matrix& m1, Vector& v1, Vector& result)
{
  result.resize(m1.nbRows());
  for(unsigned int i=0; i<result.size(); i++)
  {
    result(i) = 0;
    for(unsigned int k=0; k<m1.nbCols(); k++){ result(i) += m1(i,k)*v1(k); }
  }
}

void manuallyComputedProduct(Matrix& m1, FloatType x, Matrix& result)
{
  result.resize(m1.nbRows(), m1.nbCols());
  FloatType *rawM1 = m1.datablock(), *rawResult = result.datablock();
  for(unsigned int i=0; i<result.nbRows()*result.nbCols(); i++)
  {
      rawResult[i] = x*rawM1[i];
  }
}

void manuallyComputedSubMatrix(Matrix& m, int top, int left, int nbRows, int nbCols, Matrix& result)
{
  result.resize(nbRows, nbCols);
  for(int i=0; i<nbRows; i++)
  {
    for(int j=0; j<nbCols; j++)
    {
      result(i,j) = m(i+top,j+left);
    }
  }
}

void manuallyComputedSubVector(Vector& v, int top, int nbRows, Vector& result)
{
  result.resize(nbRows);
  for(int i=0; i<nbRows; i++)
  {
    result(i) = v(i+top);
  }
}

FloatType manuallyComputedNorm1(Matrix& m)
{
  FloatType result = 0, tmp;
  for(unsigned int j=0; j<m.nbCols(); j++)
  {
    tmp = 0;
    for(unsigned int i=0; i<m.nbRows(); i++){ tmp += fabs(m(i,j)); }
    result = std::max(result, tmp);
  }
  return result;
} 

FloatType manuallyComputedNormInfty(Matrix& m)
{
  FloatType result = 0, tmp;
  for(unsigned int i=0; i<m.nbRows(); i++)
  {
    tmp = 0;
    for(unsigned int j=0; j<m.nbCols(); j++){ tmp += fabs(m(i,j)); }
    result = std::max(result, tmp);
  }
  return result;
} 

void manuallyComputedAddition(Matrix& m1, Matrix& m2, Matrix& result)
{
  result.resize(m1.nbRows(), m1.nbCols());
  FloatType *raw_m1 = m1.datablock(), *raw_m2 = m2.datablock(), *raw_result = result.datablock();
  for(unsigned int i=0; i<m1.nbRows()*m1.nbCols(); i++){ raw_result[i] = raw_m1[i] + raw_m2[i]; }
} 

void manuallyComputedAddition(Matrix& m1, FloatType x, Matrix& result)
{
  result.resize(m1.nbRows(), m1.nbCols());
  FloatType *raw_m1 = m1.datablock(), *raw_result = result.datablock();
  for(unsigned int i=0; i<m1.nbRows()*m1.nbCols(); i++){ raw_result[i] = raw_m1[i] + x; }
} 


void manuallyComputedSubstraction(Matrix& m1, Matrix& m2, Matrix& result)
{
  result.resize(m1.nbRows(), m1.nbCols());
  FloatType *raw_m1 = m1.datablock(), *raw_m2 = m2.datablock(), *raw_result = result.datablock();
  for(unsigned int i=0; i<m1.nbRows()*m1.nbCols(); i++){ raw_result[i] = raw_m1[i] - raw_m2[i]; }
} 

void manuallyComputedSubstraction(Matrix& m1, FloatType x, Matrix& result)
{
  result.resize(m1.nbRows(), m1.nbCols());
  FloatType *raw_m1 = m1.datablock(), *raw_result = result.datablock();
  for(unsigned int i=0; i<m1.nbRows()*m1.nbCols(); i++){ raw_result[i] = raw_m1[i] - x; }
} 

void manuallyComputedTranspose(Matrix& m, Matrix& result)
{
  result.resize(m.nbCols(), m.nbRows());
  for(unsigned int i=0; i<result.nbRows(); i++)
  {
    for(unsigned int j=0; j<result.nbCols(); j++){ result(i,j) = m(j,i); }
  }
}
