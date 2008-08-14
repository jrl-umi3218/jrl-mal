/*
 *  Copyright
 */

#include <iostream>

#include <MatrixAbstractLayer/MatrixAbstractLayer.h>

int main (int argc, char** argv)
{

  //T3D m1 = T3D(T3D_MATRIX,0);

  MAL_S4x4_MATRIX((*m1),double) = new MAL_S4x4_MATRIX(,double);
  MAL_S4x4_MATRIX(inv_m1,double);
  MAL_S4x4_INVERSE((*m1),inv_m1,double)
  MAL_S4x4_MATRIX(m2,double); 
  MAL_S4x4_MATRIX(inv_m2,double);
  MAL_S4x4_INVERSE(m2,inv_m2,double)
  MAL_S4x4_MATRIX(A,double);
  MAL_S4x4_MATRIX_SET_IDENTITY(A);
  MAL_S4x4_MATRIX(B,double);
  MAL_S4x4_MATRIX(C,double);
  MAL_S4x4_C_eq_A_by_B(C,A,B);



  MAL_S3_VECTOR(v1,double);
  std::cout << MAL_S3_VECTOR_SIZE(v1) <<std::endl;

  MAL_S3_VECTOR_FILL(v1,4)

  double norm=MAL_S3_VECTOR_NORM(v1);

  MAL_S3_VECTOR(v2,double);
  MAL_S3_VECTOR_FILL(v2,2)

  MAL_S3_VECTOR(res,double);
  MAL_S3_VECTOR_CROSS_PRODUCT(res,v1,v2);

  MAL_S3_RET_VECTOR_DATABLOCK(v1);


  MAL_S4_VECTOR(v4,double);
  double s=MAL_S4_VECTOR_SIZE(v4);
  MAL_S4_VECTOR_FILL(v4,32)

  double norm2=MAL_S4_VECTOR_NORM(v4);

  MAL_S4_RET_VECTOR_DATABLOCK(v4);

  std::cout << "prueba" << std::endl;
}

/*g++ -DPACKAGE_NAME=\"dynamics-JRLJapan\" -DPACKAGE_TARNAME=\"dynamics-jrljapan\" -DPACKAGE_VERSION=\"1.0\" "-DPACKAGE_STRING=\"dynamics-JRLJapan 1.0\"" -DPACKAGE_BUGREPORT=\"olivier.stasse@aist.go.jp\" -DPACKAGE=\"dynamics-jrljapan\" -DVERSION=\"1.0\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -I. -I../../src -I../../src/../include/robotDynamicsJRLJapan/ -g -O2 -I/home/ldelgado/openrobots/include -D_DEFAULT_MATRIX3x3_ -D_DEFAULT_VECTOR3D_ -MT libdynamicsJRLJapan_la-Joint.lo -MD -MP -MF .deps/libdynamicsJRLJapan_la-Joint.Tpo -c ../../src/Joint.cpp  -fPIC -DPIC -o .libs/libdynamicsJRLJapan_la-Joint.o
*/


/*g++ main.cpp -I. -I../../src -I../../src/../include/ -I/home/ldelgado/openrobots/include*/
