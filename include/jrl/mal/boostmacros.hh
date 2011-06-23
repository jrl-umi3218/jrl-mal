/*
 * Copyright 2008, 2009, 2010,
 *
 * Francois Keith,
 * Florent Lamiraux,
 * Nicolas Mansard
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


#ifndef __MAAL_BOOST_MACROS_
# define __MAAL_BOOST_MACROS_
# include "boost/version.hpp"
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/stringize.hpp>

# if BOOST_VERSION < 104000
#  include "boost/numeric/bindings/traits/ublas_matrix.hpp"
#  include "boost/numeric/bindings/traits/std_vector.hpp"
# endif

# include "boost/numeric/ublas/matrix_proxy.hpp"
# include "boost/numeric/ublas/matrix.hpp"
# include "boost/numeric/ublas/io.hpp"
# include "boost/numeric/ublas/operation.hpp"
# include "boost/numeric/ublas/vector.hpp"
# include "boost/numeric/ublas/vector_proxy.hpp"
# include "boost/numeric/ublas/triangular.hpp"
# include "boost/numeric/ublas/lu.hpp"
# include <cstdio>


namespace ublas = boost::numeric::ublas;

# if BOOST_VERSION >= 104000
#  include "boost/numeric/ublas/detail/raw.hpp"
namespace traits=ublas::raw;
#  define MRAWDATA(x) x.data().begin()
#  define VRAWDATA(x) x.data().begin()
# else
#  include "boost/numeric/bindings/lapack/gesvd.hpp"
namespace traits = boost::numeric::bindings::traits;
namespace lapack = boost::numeric::bindings::lapack;
#  define MRAWDATA(x) traits::matrix_storage(x)
#  define VRAWDATA(x) traits::vector_storage(x)
# endif

extern "C"
{
  void dgesvd_(char const* jobu, char const* jobvt,
	       int const* m, int const* n, double* a, int const* lda,
	       double* s, double* u, int const* ldu,
	       double* vt, int const* ldvt,
	       double* work, int const* lwork, int* info);
}


# define ML_NOT_IMPLEMENTED(a)  do { \
    fprintf( stderr,"Not implemented yet.\n" ); fflush(stderr); \
    } while( 0 ); return a;

# define MAAL_CHECKVERBOSE(b) if( !b ) { \
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
      static DisplayType memory = SIMPLE; // Memory kept in static memory.
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
} // end of namespace maal.

#endif // #ifndef __MAAL_BOOST_MACROS_
