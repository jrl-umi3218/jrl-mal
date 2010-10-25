/*
 * Copyright 2007, 2008, 2009, 2010,
 *
 * Francois Keith,
 * Florent Lamiraux,
 * Nicolas Mansard,
 * Olivier Stasse,
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

/*!
 * @defgroup abstract Abstract
 * @ingroup maal2
 *
 */


#ifndef __MAAL_ABSTRACT__
# define __MAAL_ABSTRACT__

/** \brief Compehensive namespace of the second version of the MAAL.
 */
namespace maal
{
  namespace abstract
    {

      /** \brief Native type of the Matrix and Vector classes.
       *
       * Change here if a float or a double lib is needed.
       */
      typedef double FloatType;
    }
}

# include <jrl/mal/abstractVector.hh>
# include <jrl/mal/abstractMatrix.hh>

#endif /* #ifndef __MAAL_ABSTRACT__ */
