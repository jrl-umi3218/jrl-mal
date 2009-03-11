#include <iostream>
#include <fstream>

#include <MatrixAbstractLayer/MatrixAbstractLayer.h>
#include <MatrixAbstractLayer/boostVector.h>
#include <MatrixAbstractLayer/boostMatrix.h>

int main (int argc, char** argv)
{

  maal::boost::Matrix Jt,S,V,Jp;
  double dJt[3][30]={
    { 0.00645703, 3.32535e-19, -0.0411488, -0.0170703, 
      -0.0019119, -3.08188e-21, -0.0649074, -4.42244e-17, 
      -0.200751, -0.446311, -0.705216, 4.19569e-17, 
      -0.00154964, 0.0230427, -2.95901e-05, 0.0018998, 
      -0.024098, -0.00124622, 0.000169495, -0.00943761, 
      3.87661e-05, -0.0017839, -2.49748e-05, -0.0240835, 
      0.00124492, -0.000167245, -0.00942246, -3.61685e-05, -0.0017839, -2.49748e-05 },
    { 0.00557834, 0.0411902, 0, 0, 0, 0.0018841, -0.00811358, 
      0.200793, -1.46833e-15, -1.4706e-15, -1.49835e-15, 0.705188, 
      -0.00803413, 0, 0.000221111, 0, 0, 0.023754, 0.00470899, -0.000856842,
      4.22276e-05, -0.000173345, 5.28316e-06, 0, 0.0237255, 0.00475828, 
      0.000865534, 9.91453e-05, 0.000173345, -5.28316e-06 },
    { 3.27459e-19, -0.00655713, -0.00581651, 0.00606791, -7.59409e-05, 
      -0.00013513, 1.26678e-15, 0.0650075, 0.0078754, -0.111752, 0.00412562, 
      0.0935855, -7.85877e-20, 0.00781562, -1.50062e-21, -0.000226879, 0.00185162, 
      -0.00465094, -0.000905028, -0.00250201, 4.0023e-06, -0.000539774, 9.39073e-05, 
      0.0017959, 0.0046461, 0.000913423, -0.00255711, 5.69186e-06, -0.000539774, 9.39073e-05}};
 

  Jt.resize(3,30);
  for(unsigned int i=0;i<3;i++)
    {
      for(unsigned int j=0;j<30;j++)
	{
	  Jt(i,j) =dJt[i][j];
	}
    }
  
  const unsigned int nJ = Jt.nbRows();
  const unsigned int mJ = Jt.nbCols();
  V.resize(mJ,mJ);
  Jp.resize(mJ,nJ);
  Jt.dampedInverse( Jp,1e-15,NULL,NULL,&V );

  maal::boost::Matrix M=Jt*Jp;

  bool result=true;
  for(unsigned int i=0;i<3;i++)
      for(unsigned int j=0;j<3;j++)
	{
	  if (i==j)
	    {
	      if (M(i,j)!=1.0)
		result=false;
	    }
	  else
	    if (M(i,j)>1e-15)
	      result=false;
	}
  if (false)
    return -1;

  return 0;
}
