/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      boostMacros.h
 * Project:   Maal
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef __MAAL_BOOST_MACROS_
#define __MAAL_BOOST_MACROS_

#warning "deprecated header file. Please consider using boost instead."

#include "boost/numeric/bindings/traits/ublas_matrix.hpp"
#include "boost/numeric/bindings/traits/std_vector.hpp"
#include "boost/numeric/bindings/traits/std_vector.hpp"

#include "boost/numeric/ublas/matrix_proxy.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"
#include "boost/numeric/bindings/lapack/gesvd.hpp"
#include "boost/numeric/ublas/operation.hpp"
#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/vector_proxy.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include "boost/numeric/ublas/lu.hpp"


namespace ublas = boost::numeric::ublas;
namespace traits = boost::numeric::bindings::traits;
namespace lapack = boost::numeric::bindings::lapack;


#define ML_NOT_IMPLEMENTED(a)  do { \
    fprintf( stderr,"Not implemented yet.\n" ); fflush(stderr); \
    } while( 0 ); return a; 

#define MAAL_CHECKVERBOSE(b) if( !b ) { \
     fprintf( stderr,"!! %s(#%d)\tError in check size for matrix lib.\n", \
	      __FUNCTION__,__LINE__); fflush(stderr);  \
   }

  
namespace maal{  namespace boost {

  /** \brief Native type of the Matrix and Vector classes. 
   * 
   * Change here if a float or a double lib is needed. 
   */
  typedef double FloatType;

  
  /** \brief Option of display for the matrix and vector output (cout<<).
   * 
   * Two solutions can be usedto modify the display. The static
   * function setDisplayType( DisplayType ) is the classical solution.
   * The second solution is to pass the DisplayType directly to the
   * ouput operator: cout << DisplayType
   */
  
  enum DisplayType
    {SIMPLE
     ,COMPLET
     ,CPP
     ,MATLAB
    };

  /** \brief Modify the display type. */
  inline DisplayType setDisplayType( const DisplayType type, const bool read=false ) 
    {
      static DisplayType memory = MATLAB; // Memory kept in static memory. 
      // Used as a static global variable
      if(read)
	return memory;
      return (memory = type);
    }
  
  /** \brief Get the current display type. */
  inline DisplayType getDisplayType( void ) 
    { return setDisplayType( SIMPLE,true ); }
  
  
  /** The second solution is to pass the DisplayType directly to the
   * ouput operator: cout << DisplayType
   */
  inline std::ostream& operator<< (std::ostream& os,DisplayType disp )
    { setDisplayType(disp); return os; }
   
}
};

#endif // #ifndef __MAAL_BOOST_MACROS_

