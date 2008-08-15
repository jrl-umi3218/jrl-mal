# 
#  Copyright 
# 


noinst_PROGRAMS = testMatrixAbstractLayer tboost tboost_withopenhrp performance

testMatrixAbstractLayer_SOURCES =\
	main.cpp 			\
	MatrixAbstractLayerTest.h	\
	MatrixAbstractLayerTest.cpp

testMatrixAbstractLayer_CPPFLAGS = -I../include -I$(top_srcdir)/include -I../include/MatrixAbstractLayer -I. @MATRIX_CFLAGS@ 
testMatrixAbstractLayer_LDADD = @MATRIX_LDFLAGS@ 

tboost_SOURCES =\
	tboost.cpp \
	jrlgesvd.f

tboost_CPPFLAGS =-I../include  -I$(top_srcdir)/include  -I. @MATRIX_CFLAGS@ 	
tboost_LDADD = @MATRIX_LDFLAGS@ -llapack

tboost_withopenhrp_SOURCES =\
	tboost.cpp \
	jrlgesvd.f

tboost_withopenhrp_CPPFLAGS =-DWITH_OPENHRP -I../include  -I$(top_srcdir)/include  -I. @MATRIX_CFLAGS@ 	
tboost_withopenhrp_LDADD = @MATRIX_LDFLAGS@ -llapack

performance_SOURCES =\
	performance.cpp

performance_CPPFLAGS = -I$(top_srcdir)/include -I../include -I. @MATRIX_CFLAGS@ -O3 -DNDEBUG
performance_LDADD = @MATRIX_LDFLAGS@ -llapack
