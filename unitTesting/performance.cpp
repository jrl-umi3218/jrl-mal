/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      tboost.h
 * Project:   Maal
 * Author:    Olivier Stasse
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
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

#include "boost/numeric/bindings/traits/ublas_matrix.hpp"
#include <MatrixAbstractLayer/boost.h>
namespace ml = maal::boost;

namespace traits = boost::numeric::bindings::traits;

#include <iostream>
using namespace std;

int main( void )
{

  ml::Vector e(3); 
  
  ml::Matrix I(6,6); I.setIdentity();

  
  ml::Matrix M(40,40); M.fill(3.14);
  ml::Matrix L(40,6);

  ml::Matrix MH(40,40); MH.fill(3.14);
  ml::Matrix LH(40,6);

  double TotalTimeBoost = 0;
  double TotalTimeHand = 0;
  struct timeval begin_boost,end_boost;
  struct timeval begin_hand,end_hand;
  unsigned int NbOfIt = 10000;
  //  unsigned int NbOfIt = 1;

  gettimeofday(&begin_boost,0);
  srand(begin_boost.tv_usec);
  ml::Matrix J(40,6); 
  ml::Matrix JH(40,6); 
  for(unsigned int i=0;i<NbOfIt;i++)
    {
      if (i%10==0)
	cout << i << endl; 
      for(unsigned int li=0;li<40;li++)
	{
	  for(unsigned int lj=0;lj<40;lj++)
	    M(li,lj) = (10000.0 * (double)rand())/(double)RAND_MAX;
	  for(unsigned int lj=0;lj<6;lj++)
	    L(li,lj) = (10000.0 * (double)rand())/(double)RAND_MAX;
	}
      //      cout << L <<endl;
      //      cout << M <<endl;
      // boost computation.

      gettimeofday(&begin_boost,0);
      M.multiply(L,J);
      gettimeofday(&end_boost,0);
      
      TotalTimeBoost += end_boost.tv_sec - begin_boost.tv_sec + 0.000001 * (end_boost.tv_usec - begin_boost.tv_usec);

      // hand made.
      MH = M;
      LH = L;
      
      double *pL,*pM,*pJ,*pLtmp, *pMtmp;
      gettimeofday(&begin_hand,0);
      pL= pLtmp = traits::matrix_storage(LH.matrix) ;
      pM = pMtmp = traits::matrix_storage(MH.matrix);
      pJ = traits::matrix_storage(JH.matrix);

      for(unsigned int li=0;li<40;li++)
	{
	  pLtmp = traits::matrix_storage(LH.matrix);
	  for(unsigned int lj=0;lj<6;lj++)
	    {
	      *pJ=0;
	      pL = pLtmp;
	      pM = pMtmp;
	      for(unsigned int lk=0;lk<40;lk++)
		{
		  *pJ+= (*pM++)*(*pL);
		  pL+=6;
		}
	      pLtmp++;
	      pJ++;
	    }
	  pMtmp+=40;
	}
      gettimeofday(&end_hand,0);
      TotalTimeHand += end_hand.tv_sec - begin_hand.tv_sec + 0.000001 * (end_hand.tv_usec - begin_hand.tv_usec);
#if 0
      cout << "M:" << endl;
      cout << M << endl;
      cout << "MH:" << endl;
      cout << MH << endl;

      cout << "L:" << endl;
      cout << L << endl;
      cout << "LH:" << endl;
      cout << LH << endl;

      cout << "J:" << endl;
      cout << J << endl;
      cout << "JH:" << endl;
      cout << JH << endl;
      
      cout << JH-J <<endl;
#endif

    }

  cout << "Boost: " << TotalTimeBoost / NbOfIt << endl;
  cout << "Hand: " << TotalTimeHand / NbOfIt << endl;

#if 0
  cout << e <<endl;

  J=M.transpose();
  cout<<J<<endl;
  J=M.transpose()*M;
  cout<<J<<endl;
  J=M.transpose()*M+I;
  cout<<J<<endl;

  cout << "**** READY TO INVERSE ****"<<endl;
  J=J.inverse();
  cout<<J<<endl;

  cout << "**** READY TO [!]PSEUDO[!]-INVERSE ****"<<endl;
  ml::Matrix Mp(6,3);
  cout<<"M"<<M<<endl;
  M.transpose().pseudoInverse(Mp);
  cout<<"Mpt"<<Mp<<endl;
  M.pseudoInverse(Mp);
  cout<<"Mp"<<Mp<<endl;

  ml::Vector q(6); q=Mp*e;
  cout<<q<<endl;


  I.fill(2);
  cout<<"I"<<I<<endl; 
  ml::Matrix tmp = I;
  tmp *= tmp;
  cout<<"Mp2"<<tmp<<endl;
  
  cout << I*I << endl;
  cout << tmp-I*I<<endl;
#endif

  return 0;
}

