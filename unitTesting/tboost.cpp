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
namespace ml = maal::boost;

#include <iostream>
using namespace std;

int main( void )
{
  unsigned int NR=6,NC=3;

  ml::Vector e(NR); 
  
  ml::Matrix I(6,6); I.setIdentity();

  ml::Matrix M(NR,NC); M.fill(3.14);
  ml::Matrix L; L=I.extract(0,0,3,NR);

  cout << L <<endl;
  cout << M <<endl;

  ml::Matrix J; L.multiply(M,J);

  cout << "J = " << J <<endl;
  cout << e <<endl;

  J=M.transpose();
  cout<<J<<endl;
  J=M.transpose()*M;
  cout<<J<<endl;

  I.resize(NC,NC); I.setIdentity();
  J=M.transpose()*M+I;
  cout<<J<<endl;

  cout << "**** READY TO INVERSE ****"<<endl;
  J=J.inverse();
  cout<<J<<endl;

  cout << "**** READY TO [!]PSEUDO[!]-INVERSE ****"<<endl;
  ml::Matrix Mp(NC,NR); Mp.fill(0);
  cout<<"M"<<M<<endl;
  M.transpose().pseudoInverse(Mp);
  cout<<"Mpt"<<Mp<<endl;
  M.pseudoInverse(Mp);
  cout<<"Mp"<<Mp<<endl; 

  ml::Vector q(NC); q=Mp*e;
  cout<<q<<endl;


  I.fill(2);
  cout<<"I"<<I<<endl; 
  ml::Matrix tmp = I;
  tmp *= tmp;
  cout<<"Mp2"<<tmp<<endl;
  
  cout << I*I << endl;
  cout << tmp-I*I<<endl;

  cout << "M = " << M << endl;
  J.resize(NR,NC);
  cout << "J = " << J << endl;
  ml::Matrix M_J(NR,NC); M_J+=M-J;
  cout << "M-J = " << M_J << endl;

  ml::Vector e1(NC),e2(NR); 
  e2=J*e1-M*e1;
  cout << e2 << endl;


  // Test pseudo-inverse
  int r=7,c=16;
  ml::Matrix M0(r,c);
  ml::Matrix M1(r,c);
  ml::Matrix Minv(c,r);
  
  ml::Matrix U,V,S;
  
  unsigned int nbzeros=0;
  for( unsigned int j=0;j<c;++j )
    {
      if( (rand()+1.) / RAND_MAX > .8 )
	{ for( unsigned int i=0;i<r;++i ) M0(i,j) = 0.;
	nbzeros++ ;}
      else
	for( unsigned int i=0;i<r;++i )
	  M0(i,j) = (rand()+1.) / RAND_MAX*2-1;
    }
  for( unsigned int i=0;i<r;++i )
    for( unsigned int j=0;j<c;++j )
      M1(i,j) = M0(i,j); //+ ((rand()+1.) / RAND_MAX*2-1) * 1e-28 ;
  
  cout << ml::MATLAB <<"M0 = "<< M0 <<endl;
  cout <<"M1 = " << M1<<endl;
  cout <<"Nb zeros = " << nbzeros<<endl;

  cout << "Display the pseudo inverse:" << endl;
  cout << M0.pseudoInverse() <<endl;
  MAL_INVERSE(M0.matrix,M1.matrix,double);
  cout << ml::MATLAB << "M1 = "<< M1 << endl;
  return 0;
}

