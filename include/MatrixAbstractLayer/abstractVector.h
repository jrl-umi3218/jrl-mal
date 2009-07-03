/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      abstractVector.h
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


#ifndef __MAAL_ABSTRACT_VECTOR_
#define __MAAL_ABSTRACT_VECTOR_

#warning "deprecated header file. Please consider using boost instead."

#include <MatrixAbstractLayer/abstractMacros.h>

namespace maal{  namespace abstract {

  
  /* --- VECTOR --------------------------------------------------------- */
  /* --- VECTOR --------------------------------------------------------- */
  /* --- VECTOR --------------------------------------------------------- */

  /** \brief Abstract Vector class. 
   */
  
  class Vector
    {
    public: /* Constructors */

      Vector( const unsigned int size=0 );
      Vector( InternalVector* clone,const bool proprio=false );
      Vector( const Vector& copy );
      virtual ~Vector( void );

      InternalVector& accessToMotherLib( void );
      const InternalVector& accessToMotherLib( void ) const;
      Vector & initFromMotherLib( const InternalVector& bv );

    public:
      /* ------------ */
      /* --- INIT --- */
      /* ------------ */
      inline unsigned int size( void ) const;
      inline Vector& resize( const unsigned int nbRows,const bool setZero=true );

      inline Vector& fill( const FloatType value );
      inline Vector& setZero( void );
      inline Vector& opposite( Vector&res ) const;
      inline Vector& opposite( void ) const;

    public:
      /* -------------- */
      /* --- SCALAR --- */
      /* -------------- */
      inline FloatType norm ( void ) const;
      inline FloatType norm1 ( void ) const;
      inline FloatType max( void ) const;
      inline FloatType min( void ) const;
      inline FloatType sumSquare( void ) const;
      inline FloatType normInfty( void ) const;
      inline FloatType scalarProduct ( const Vector& v2 ) const;
      static inline FloatType scalarProduct ( const Vector& v1,const Vector& v2 );

    public:
      /* ----------------------- */
      /* --- OPERATOR ExE->E --- */
      /* ----------------------- */

      /* --- CROSS PRODUCT v1 x v2 --- */
      static Vector& crossProduct( const Vector&v1,const Vector&v2,Vector&res);
      inline Vector& crossProduct( const Vector&v2,Vector&res ) const;
      inline Vector crossProduct( const Vector&v2 );
	
      /* --- <Vector> x <Vector> --- */
      static Vector& multiply( const Vector&v1,const Vector&v2,Vector&res);
      inline Vector multiply( const Vector&v2 ) const;
      inline Vector& multiply( const Vector&v2,Vector&res ) const;

      /* --- <Vector> x <Float> --- */
      static Vector& multiply( const Vector&v1,const FloatType x,Vector&res);
      inline Vector multiply( const FloatType x ) const;
      inline Vector& multiply( const FloatType x,Vector&res ) const;

      /* --- <Vector> + <Vector> --- */
      static Vector& addition( const Vector&v1,const Vector&v2,Vector&res);
      inline Vector addition( const Vector&v2 ) const;
      inline Vector& addition( const Vector&v2,Vector&res ) const;

      /* --- <Vector> - <Vector> --- */
      static Vector& substraction( const Vector&v1,const Vector&v2,Vector&res);
      inline Vector substraction( const Vector&v2 ) const;
      inline Vector& substraction( const Vector&v2,Vector&res ) const;

    public:
      /* ------------------- */
      /* --- DATA ACCESS --- */
      /* ------------------- */
      inline const FloatType* datablock( void ) const;
      inline  FloatType* datablock( void);
      inline const FloatType& elementAt( const unsigned int row ) const;
      inline FloatType& elementAt( const unsigned int row );
      inline Vector& extract( const unsigned int top,
			      const unsigned int nbrows,Vector& C ) const;
      inline Vector extract( const unsigned int top,const unsigned int nbrows ) const;

    public:
      /* ----------------- */
      /* --- OPERATORS --- */
      /* ----------------- */
      inline friend Vector operator+ ( const Vector&v1,const Vector&v2 );
      inline friend Vector operator- ( const Vector&v1,const Vector&v2 );
      inline friend Vector operator* ( const Vector&v1,const Vector&v2 );
      inline friend Vector operator* ( const Vector&v1,const FloatType x );
      inline friend Vector operator* ( const FloatType x,const Vector&v1 );
      inline Vector& operator- ( const Vector&v1 );
      inline Vector& operator+= ( const Vector&v1 );
      inline Vector& operator-= ( const Vector&v1 );
      inline Vector& operator*= ( const Vector&v1 );
      inline Vector& operator*= ( const FloatType x );
      inline const FloatType& operator()( const unsigned int i )const;
      inline FloatType& operator()( const unsigned int i );
      inline Vector& operator= ( const Vector&v1 );

      inline friend std::istream& operator>> ( std::istream& is,Vector& v1 );
      inline friend std::ostream& operator<< ( std::ostream& os,const Vector& v1 ); 
    };

}}

#endif // #ifndef __MAAL_ABSTRACT_VECTOR_

