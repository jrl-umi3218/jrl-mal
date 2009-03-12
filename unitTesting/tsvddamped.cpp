/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      tboost.h
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
 * Unit testing of the maal V2, boost (namespace maal::boost).
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <MatrixAbstractLayer/MatrixAbstractLayer.h>

#include <MatrixAbstractLayer/boost.h>
#include <MatrixAbstractLayer/boostMatrixSvd.h>
namespace ml = maal::boost;

#include <iostream>
#ifdef WIN32
#include <Windows.h>
#include "TimeUtilsWindows.h"
#else
#include <sys/time.h>
#endif /* WIN32 */

using namespace std;

int main( void )
{
  // Test pseudo-inverse
  int nr,nc;
  nr=3,nc=5; 
  nr=50,nc=30;
  unsigned int pb[4]= {0,0,0,0};

  const bool dispMatrix = false;
  ml::MatrixSvd M0(nr,nc);
  ml::Matrix M0inv(nc,nr);
  ml::Matrix M1(nc,nr);
  
  ml::Matrix U,V,S;
  
  struct timeval t0,t1;
  bool result1=true;
  bool result2=true;

  for( unsigned int loop=0;loop<10;++loop )
    {
      //nc++; M0.resize(nr,nc); 
      
      //unsigned int nbzeros=0;
      for( int j=0;j<nc;++j )
	{
// 	  if( (rand()+1.) / RAND_MAX > .8 )
// 	    { for( unsigned int i=0;i<r;++i ) M0(i,j) = 0.;
// 	    nbzeros++ ;}
// 	  else
	    for( int i=0;i<nr;++i )
	      { M0(i,j) = (rand()+1.) / RAND_MAX*2-1;}
	}
      
      if( dispMatrix&&(loop==0) ) 
	{cout << ml::MATLAB <<"M0 = "<< M0 <<endl;
	cout << ml::MATLAB <<"M0 = " << M0.nbRows() << "x" << M0.nbCols() << std::endl;}
      else std::cout << " ---------------- " << std::endl;

      unsigned int t0t1 = 0;
     for(unsigned int rep=0;rep<100;++rep )
       {
	 gettimeofday(&t0,NULL);
	 M0.dampedInverse(M1,1e-15);
	 gettimeofday(&t1,NULL);
	 t0t1 += (t1.tv_sec-t0.tv_sec)*1000*1000+(t1.tv_usec-t0.tv_usec);
       }

     /*! Pseudo-inverse test. */
     ml::Matrix test;
     test= M1*M0;

     for(unsigned int i=0;i<test.nbRows();i++)
       {
	 for(unsigned int j=0;j<test.nbCols();j++)
	   {
	     if (i==j)
	       {
		 if (fabs(test(i,j)-1.0)>1e-14)
		   {
		     result1 = false;
		     pb[0]++;
		     cout << test(i,j) << endl;
		   }
	       }
	     else
	       {
		 if(test(i,j)>1e-14)
		   {
		     result1 = false;
		     pb[1]++;
		     cout << test(i,j) << endl;
		   }
	       }
	   }
       }

     if( dispMatrix )
       {if( loop==0 ) cout << "Display the pseudo inverse maal2:" << endl;
	 cout << ml::MATLAB << "M2 = "<< M1 <<endl; }
     cout << "dt = " << t0t1/1000 << "ms " << std::endl;
     
     t0t1 = 0;
     for(unsigned int rep=0;rep<100;++rep ) 
       {
	  M0inv = M0;
	  gettimeofday(&t0,NULL);
	  MAL_INVERSE(M0inv.matrix,M1.matrix,double);
	  gettimeofday(&t1,NULL);
	  t0t1 += (t1.tv_sec-t0.tv_sec)*1000*1000+(t1.tv_usec-t0.tv_usec);
       }
     test = M1*M0;
     for(unsigned int i=0;i<test.nbRows();i++)
       {
	 for(unsigned int j=0;j<test.nbCols();j++)
	   {
	     if (i==j)
	       {
		 if (fabs(test(i,j)-1.0)>1e-14)
		   {
		     result2 = false;
		     pb[2]++;
		     cout << test(i,j) << endl;
		   }
	       }
	     else
	       {
		 if(test(i,j)>1e-14)
		   {
		     result2 = false;
		     pb[3]++;
		     cout << test(i,j) << endl;
		   }
	       }
	   }
       }

     if( dispMatrix )
       {
	 if( loop==0 ) cout << "Display the pseudo inverse maal1:" << endl;
	 cout << ml::MATLAB << "M1 = "<< M1 << endl; }
     cout << "dt = " << t0t1/1000 << "ms " << std::endl;
    }

  cout << pb[0] << " " << pb[1] << " " << pb[2] << " " <<pb[3]<<endl;
  if ((!result1) || (!result2))
    return -1;

  return 0;
}

