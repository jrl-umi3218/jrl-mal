#ifndef MATRIXABSTRACTLAYER_CHECK_H
#define MATRIXABSTRACTLAYER_CHECK_H

//define isnan for win32 users
#ifdef WIN32
# ifndef isnan
#  include <float.h>
#  define isnan _isnan
# endif /*isnan*/
#endif /*WIN32*/

inline bool malIsNanVector(const vectorN& inVector)
{
  for (unsigned int i=0; i<MAL_VECTOR_SIZE(inVector); i++) {
    if (isnan(inVector[i])) return true;
  }
  return false;
}

inline bool malIsNanMatrix(const matrixNxP& inMatrix)
{
  for (unsigned int i=0; i<MAL_MATRIX_NB_ROWS(inMatrix); i++) {
    for (unsigned int j=0; i<MAL_MATRIX_NB_COLS(inMatrix); i++) {
      if (isnan(inMatrix(i,j))) return true;
    }
  }
  return false;
}

#endif
