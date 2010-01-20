/**
 *
 * (c) 2008 , Nicolas Mansard, Olivier Stasse JRL-Japan, CNRS-AIST, ISRI.
 */

/*!
 * @defgroup abstract Abstract
 * @ingroup maal2
 * 
 */


#ifndef __MAAL_ABSTRACT__
#define __MAAL_ABSTRACT__

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

#include <MatrixAbstractLayer/abstractVector.h>
#include <MatrixAbstractLayer/abstractMatrix.h>




#endif /* #ifndef __MAAL_ABSTRACT__ */


