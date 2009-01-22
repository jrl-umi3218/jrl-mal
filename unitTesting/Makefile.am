# 
#  Copyright 2009 JRL AIST-CNRS
# 


noinst_PROGRAMS = testMatrixAbstractLayer performance

testMatrixAbstractLayer_SOURCES =\
	main.cpp 			\
	MatrixAbstractLayerTest.h	\
	MatrixAbstractLayerTest.cpp

testMatrixAbstractLayer_CPPFLAGS = -I../include -I$(top_srcdir)/include -I../include/MatrixAbstractLayer -I. @MATRIX_CFLAGS@ 
testMatrixAbstractLayer_LDADD = @MATRIX_LDFLAGS@ 

tsvd_SOURCES =\
	tsvd.cpp \
	jrlgesvd.f

tsvd_CPPFLAGS =-I../include  -I$(top_srcdir)/include  -I. @MATRIX_CFLAGS@ 	
tsvd_LDADD = @MATRIX_LDFLAGS@ -llapack

tsvd_withopenhrp_SOURCES =\
	tsvd.cpp \
	jrlgesvd.f

tsvd_withopenhrp_CPPFLAGS =-DWITH_OPENHRP -I../include  -I$(top_srcdir)/include  -I. @MATRIX_CFLAGS@ 	
tsvd_withopenhrp_LDADD = @MATRIX_LDFLAGS@ -llapack

performance_SOURCES =\
	performance.cpp

performance_CPPFLAGS = -I$(top_srcdir)/include -I../include -I. @MATRIX_CFLAGS@ -O3 -DNDEBUG
performance_LDADD = @MATRIX_LDFLAGS@ -llapack
