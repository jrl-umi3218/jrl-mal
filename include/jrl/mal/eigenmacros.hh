/*
 * Copyright 2011,
 *
 * Maxime Reis
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


#ifndef __MAAL_EIGEN_MACROS_
# define __MAAL_EIGEN_MACROS_
# include "Eigen/Dense"
# include <cstdio>

# define MRAWDATA(x) x.data()
# define VRAWDATA(x) x.data()

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


namespace maal{  namespace eigen {

  /** \brief Native type of the Matrix and Vector classes.
   *
   * Change here if a float or a double lib is needed.
   */
  typedef double FloatType;


  /** \brief Option of display for the matrix and vector output (cout<<).
   *
   * Two solutions can be used to modify the display. The static
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
} // end of namespace maal.

#endif // #ifndef __MAAL_EIGEN_MACROS_
