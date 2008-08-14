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

#include <MatrixAbstractLayer/boost.h>
namespace ml = maal::boost;

#include <iostream>
using namespace std;

int main( void )
{

  ml::Vector e(3); 
  
  ml::Matrix I(6,6); I.setIdentity();

  
  ml::Matrix M(3,6); M.fill(3.14);
  ml::Matrix L; L=I.extract(0,0,3,3);

  cout << L <<endl;
  cout << M <<endl;

  ml::Matrix J; L.multiply(M,J);

  cout << "J = " << J <<endl;
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

  cout << "M = " << M << endl;
  J.resize(3,6);
  cout << "J = " << J << endl;
  ml::Matrix M_J(3,6); M_J+=M-J;
  cout << "M-J = " << M_J << endl;

  ml::Vector e1(6),e2(3); 
  e2=J*e1-M*e1;
  cout << e2 << endl;

  return 0;
}

