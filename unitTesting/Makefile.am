# 
#  Copyright 
# 


noinst_PROGRAMS = testMatrixAbstractLayer tboost

testMatrixAbstractLayer_SOURCES =\
	main.cpp 			\
	MatrixAbstractLayerTest.cpp

testMatrixAbstractLayer_CPPFLAGS = -I$(top_srcdir)/include -I../include/MatrixAbstractLayer @MATRIX_CFLAGS@ 
testMatrixAbstractLayer_LDADD = @MATRIX_LDFLAGS@ 

tboost_SOURCES =\
	tboost.cpp

tboost_CPPFLAGS = -I$(top_srcdir)/include -I../include @MATRIX_CFLAGS@ 
tboost_LDADD = @MATRIX_LDFLAGS@ -llapack
