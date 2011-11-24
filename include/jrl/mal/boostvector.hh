/*
 * Copyright 2008, 2009, 2010,
 *
 * Paul Evrard,
 * Francois Keith,
 * Florent Lamiraux,
 * Nicolas Mansard,
 * Olivier Stasse
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


#ifndef __MAAL_BOOST_VECTOR_
# define __MAAL_BOOST_VECTOR_
# include <cstdio>
# include <jrl/mal/boostmacros.hh>

/**
 * \file boostVector.h Define maal::boost::Vector
 */

namespace maal{  namespace boost {


  /* --- VECTOR --------------------------------------------------------- */
  /* --- VECTOR --------------------------------------------------------- */
  /* --- VECTOR --------------------------------------------------------- */

  /** \brief Vector class that include the boost::ublas::vector
   *
   * The class simply encapsulates the ublas::vector object, and implement
   * a set of standard functions.
   * When the maal::boost::Vector object is constructed, it automatically
   * builds the internal ublas::vector object. The internal object can be
   * access through accessToMotherLib. Finally, it is possible to
   * build the capsule around an existing boost ublas::vector through the
   * appropriate constructor.
   */

  class Vector
    {
      typedef ::boost::numeric::ublas::vector<FloatType> InternalVector;

    protected:
      InternalVector staticVector;
      InternalVector* dynamicVector;
      InternalVector& vector;
      bool proprio;
      static const bool AUTORESIZE = true;
      static const bool CHECKRESIZE = true;


    public: /* Constructors */

      /** @name Constructors */
      //@{

      /** \brief Classical constructor.
       *
       * Build the internal vector from the demanded size.
       */
      Vector( const unsigned int size=0 )
	: staticVector( size ),dynamicVector( NULL ),vector(staticVector)
	{}

      /** \brief Build only the capsule around a already existing
       * boost vector object.
       */
      Vector( InternalVector* clone,const bool proprio=false )
	: staticVector(0),dynamicVector( clone ),vector(*dynamicVector)
	,proprio(proprio)
	{}

      /** \brief Build a new internal vector from existing
       * boost vector object by copying the data.
       */
      Vector( const Vector& copy )
	: staticVector( copy.vector ),dynamicVector( NULL )
	,vector(staticVector),proprio(false)
	{}

      virtual ~Vector( void )
	{
	  if( (NULL!=dynamicVector)&&(proprio) )
	    {    delete dynamicVector;   }
	}

      /** \brief Access to the boost internal vector. */
      InternalVector& accessToMotherLib( void ) { return vector; }
      /** \brief Access to the boost internal vector. */
      const InternalVector& accessToMotherLib( void ) const { return vector; }
      /** \brief Copy the values and data of an existing
       * boost vector. */
      Vector & initFromMotherLib( const InternalVector& bv )
	{ vector = bv; return *this;}
      //@}

     public:
      /* -------------- */
      /* --- SCALAR --- */
      /* -------------- */

      /** @name Modifiors */
      //@{
      inline unsigned int size( void ) const {
        /* XXX static_cast to avoid modifying the interface, but the function
         * should probably return size_t here */
        return static_cast<unsigned int>(vector.size());
      }

      inline Vector& resize( const unsigned int nbRows,const bool setZero=true )
	{
	  vector.resize(nbRows,!setZero);
	  return *this;
	}

      inline Vector& fill( const FloatType value )
	{
	  for(unsigned int i=0;i<size();vector[i++]=value) ;
	  return *this;
	}
      inline Vector& setZero( void )
	{
	  vector.clear();
	  return *this;
	}
      inline Vector& opposite( Vector&res ) const
	{ res.vector=vector; res.vector *=-1; return res; }
      inline Vector opposite( void ) const
	{ Vector res(size()); opposite(res); return res; }

      //@}


     public:
      /* -------------- */
      /* --- SCALAR --- */
      /* -------------- */

      /** @name Scalar Operator E->R */
      //@{

      /* \brief Euclidian norm sqrt( x*x + y*y ... )  */
      inline FloatType norm ( void ) const
	{
	  return ::boost::numeric::ublas::norm_2( vector );
	}
      /** \brief Norm 1 sum( |xi| )  */
     inline FloatType norm1 ( void ) const
	{
	  return ::boost::numeric::ublas::norm_1( vector );
	}
     /** \brief Not implemented yet. */
     inline FloatType max( void ) const { ML_NOT_IMPLEMENTED(0) }
     /** \brief Not implemented yet. */
     inline FloatType min( void ) const { ML_NOT_IMPLEMENTED(0) }
     /** \brief Not implemented yet. */
     inline FloatType sumSquare( void ) const { ML_NOT_IMPLEMENTED(0) }
     /** \brief Infinity norm: max( |xi| ). */
     inline FloatType normInfty( void ) const
       {
	 return ::boost::numeric::ublas::norm_inf( vector );
       }
     /** \brief Scalar product: v1.v2 = sum( x1*x2 ).
      */
     inline FloatType scalarProduct ( const Vector& v2 ) const
       { return inner_prod(vector,v2.vector); }
     /** \brief Scalar product: v1.v2 = sum( x1*x2 ).
      */
     static inline FloatType scalarProduct ( const Vector& v1,const Vector& v2 )
       { return inner_prod(v1.vector,v2.vector); }
      //@}

    public:
      /* ----------------------- */
      /* --- OPERATOR ExE->E --- */
      /* ----------------------- */

      /** @name Operator Functions ExE->E
       *
       * Each C-style function is implemented as a C++ operator.
       */
      //@{

      /* --- CROSS PRODUCT v1 x v2 --- */
      static Vector& crossProduct( const Vector&v1,const Vector&v2,Vector&res)
	{ return v1.crossProduct(v2,res); }
      inline Vector&
	crossProduct( const Vector&v2,Vector&res ) const
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,v2.vector)); _resize(res.vector,vector);
	  //if( (v1.size()==3) && (v2.size()==3) )
	  {
	    res.vector[0] = vector[1] * v2.vector[2] - v2.vector[1] * vector[2];
	    res.vector[1] = vector[2] * v2.vector[0] - v2.vector[2] * vector[0];
	    res.vector[2] = vector[0] * v2.vector[1] - v2.vector[0] * vector[1];
	  }
	  return res;
	}
      inline Vector
	crossProduct( const Vector&v2 )
	{
	  Vector res(size()); return crossProduct(v2,res);
	}


      /* --- <Vector> x <Vector> --- */
      static Vector& multiply( const Vector&v1,const Vector&v2,Vector&res)
	{ return v1.multiply(v2,res); }
      inline Vector multiply( const Vector&v2 ) const
	{ Vector res(size()); return multiply(v2,res); }
      inline Vector& multiply( const Vector&v2,Vector&res ) const
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,v2.vector)); _resize(res.vector,vector);
	  for( unsigned int i=0;i<size();++i )
	    { res.vector(i)=vector(i)*v2.vector(i); }
	  return res;
	}


      /* --- <Vector> x <Float> --- */
      static Vector& multiply( const Vector&v1,const FloatType x,Vector&res)
	{ return v1.multiply(x,res); }
      inline Vector multiply( const FloatType x ) const
	{ Vector res(size()); return multiply(x,res); }
      inline Vector& multiply( const FloatType x,Vector&res ) const
	{
	  //_resize(res.vector,vector);
	  res.vector=vector;
	  res.vector*=x;
	  return res;
	}

      /* --- <Vector> + <Vector> --- */
      static Vector& addition( const Vector&v1,const Vector&v2,Vector&res)
	{ return v1.addition(v2,res); }
      inline Vector addition( const Vector&v2 ) const
	{ Vector res(size()); return addition(v2,res); }
      inline Vector& addition( const Vector&v2,Vector&res ) const
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,v2.vector));
	  //_resize(res.vector,vector);
	  res.vector=vector;
	  res.vector+=v2.vector; return res;
	}

      /* --- <Vector> - <Vector> --- */
      static Vector& substraction( const Vector&v1,const Vector&v2,Vector&res)
	{ return v1.substraction(v2,res); }
      inline Vector substraction( const Vector&v2 ) const
	{ Vector res(size()); return substraction(v2,res);  }
      inline Vector& substraction( const Vector&v2,Vector&res ) const
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,v2.vector));
	  //_resize(res.vector,vector);
	  res.vector=vector;
	  res.vector-=v2.vector; return res;
	}
      //@}

    public:
      /* ------------------- */
      /* --- DATA ACCESS --- */
      /* ------------------- */

      /** @name Accessors
       *
       * Access to an element, a block of element or the hidden double-array matrix.
       */
      //@{

      /** \brief Access to the C-style double matrix. */
      inline const FloatType* datablock( void ) const
	{ return VRAWDATA(vector); }
      /** \brief Access to the C-style double matrix. */
      inline  FloatType* datablock( void)
	{ return VRAWDATA(vector); }

      /** \brief Access to the i-th element in R-only.
       *
       * This C-style function is equivalent to the C++ operator().
       */
      inline const FloatType& elementAt( const unsigned int row ) const
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,row));
	  return vector(row);
	}
      /** \brief Access to the i-th element in RW-mode.
       *
       * This C-style function is equivalent to the C++ operator().
       */
      inline FloatType& elementAt( const unsigned int row )
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,row));
	  return vector(row);
	}

      /** \brief Extract a part of the vector.
       *
       * Not implemented yet.
       */
      inline Vector& extract( const unsigned int top,const unsigned int nbrows,
			      Vector& C ) const
	{
	  MAAL_CHECKVERBOSE(_checksize(vector,top));  C.vector.resize(top+nbrows-1);
	  ::boost::numeric::ublas::vector_slice< ::boost::numeric::ublas::vector<FloatType> >
	      avec(vector,::boost::numeric::ublas::slice(top,1,nbrows));
	  C.vector = avec;
	  return C;
	}
      /** \brief Extract a part of the vector.
       *
       * Not implemented yet.
       */
      inline Vector extract( const unsigned int top,const unsigned int nbrows ) const
	{ Vector res(nbrows); return extract(top,nbrows,res); }

      //@}

    public:
      /* ----------------- */
      /* --- OPERATORS --- */
      /* ----------------- */

      /** @name Operators
       *
       * Classical operators: use v1 + v2 for addition, v1(i) for i-th element...
       */
      //@{

      inline friend Vector operator+ ( const Vector&v1,const Vector&v2 )
	{ Vector res; v1.addition(v2,res); return res; }
      inline friend Vector operator- ( const Vector&v1,const Vector&v2 )
	{ Vector res; v1.substraction(v2,res); return res; }
      inline friend Vector operator* ( const Vector&v1,const Vector&v2 )
	{ Vector res; v1.multiply(v2,res); return res; }
      inline friend Vector operator* ( const Vector&v1,const FloatType x )
	{ Vector res; v1.multiply(x,res); return res; }
      inline friend Vector operator* ( const FloatType x,const Vector&v1 )
	{ Vector res; v1.multiply(x,res); return res; }

      friend inline Vector operator- ( const Vector&v1 ){ return v1.opposite(); }
      inline Vector& operator+= ( const Vector&v1 ){ return addition(v1,*this); }
      inline Vector& operator-= ( const Vector&v1 ){ return substraction(v1,*this); }
      inline Vector& operator*= ( const Vector&v1 ){ return multiply(v1,*this); }
      inline Vector& operator*= ( const FloatType x ){ return multiply(x,*this); }
      inline const FloatType& operator()( const unsigned int i )const { return vector(i); }
      inline FloatType& operator()( const unsigned int i ){ return elementAt(i); }
      inline Vector& operator= ( const Vector&v1 ){ vector=v1.vector; return *this;}
      //inline friend std::ostream& operator<< ( std::ostream& os,const Vector& v1 ){ return os<<v1.vector; }
      inline friend std::istream& operator>> ( std::istream& is,Vector& v1 ){ return is>>v1.vector; }


      inline friend std::ostream& operator<< ( std::ostream& os,const Vector& v1 )
	{
	  return os<<v1.vector;
	}

      //@}

    public:

      friend class Matrix;

    public:

      /** @name Internal functions (autoresize) */
      //@{

      bool autoresize( void ) { return AUTORESIZE; }
    protected:
      static inline void _resize( InternalVector& vct1,const InternalVector& vct2 )
	{ if(AUTORESIZE) { vct1.resize( vct2.size() ); } }

      static inline bool _checksize( const InternalVector& vct1,const InternalVector& vct2 )
	{ return ( (!CHECKRESIZE)||(vct1.size()==vct2.size()) ); }
      static inline bool _checksizeVerb( const InternalVector& vct1,const InternalVector& vct2 )
	{
	  if ( (!CHECKRESIZE)||(vct1.size()==vct2.size()) )
	    return true;
	  else
	    {
	      fprintf(stderr,"!!\tmaal::Vector: error in vector size.\n"); fflush(stderr);
	      return false;
	    }
	}
      static inline bool _checksize( const InternalVector& vct1,const unsigned int s2 )
	{ return ( (!CHECKRESIZE)||(vct1.size()>s2) ); }
      static inline bool _checksizeVerb( const InternalVector& vct1,const unsigned int s2)
	{
	  if ( (!CHECKRESIZE)||(vct1.size()>s2) )
	    return true;
	  else
	    {
	      fprintf(stderr,"!!\tmaal::Vector: error in vector size.\n"); fflush(stderr);
	      return false;
	    }
	}

      //@}

    };

}}

#endif // #ifndef __MAAL_BOOST_VECTOR_

