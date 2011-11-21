/*
 * Copyright 2010,
 *
 * Francois Keith
 * Florent Lamiraux
 *
 * CNRS/AIST
 *
 * This file is part of MatrixAbstractLayer.
 * MatrixAbstractLayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MatrixAbstractLayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with MatrixAbstractLayer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MATRIXABSTRACTLAYER_CHECK_H
# define MATRIXABSTRACTLAYER_CHECK_H

#include <boost/math/special_functions/fpclassify.hpp>

#include <jrl/mal/matrixabstractlayerboost.hh>


inline bool malIsNanVector(const vectorN& inVector)
{
  for (unsigned int i=0; i<MAL_VECTOR_SIZE(inVector); i++) {
    if (boost::math::isnan(inVector[i])) return true;
  }
  return false;
}

inline bool malIsNanMatrix(const matrixNxP& inMatrix)
{
  for (unsigned int i=0; i<MAL_MATRIX_NB_ROWS(inMatrix); i++) {
    for (unsigned int j=0; i<MAL_MATRIX_NB_COLS(inMatrix); i++) {
      if (boost::math::isnan(inMatrix(i,j))) return true;
    }
  }
  return false;
}

#endif /* MATRIXABSTRACTLAYER_CHECK_H */
