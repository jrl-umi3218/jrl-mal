
dnl 
dnl configure.ac file for package MatrixAbstractLayer 
dnl

AC_INIT([MatrixAbstractLayer], [1.4.99], [olivier.stasse@aist.go.jp])
AC_PREREQ(2.59)

AM_INIT_AUTOMAKE([foreign no-define])

AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

dnl defaults
AC_SUBST(_BOOST_MATRIX_,	0)
AC_SUBST(_VNL_MATRIX_,		0)
AC_SUBST(_T3D_R3D_V3D_,		0)
AC_SUBST(MATRIX_REQUIRE,	[])
AC_SUBST(MATRIX_CFLAGS,		[])
AC_SUBST(MATRIX_LDFLAGS,	[])


dnl --- matrix libraries configuration -------------------------------

AC_ARG_WITH(boost, AC_HELP_STRING([--with-boost],
	[use boost for generic NxP matrix implementation]),,with_boost=no)
AC_ARG_WITH(vnl, AC_HELP_STRING([--with-vnl],
	[use VNL for generic NxP matrix implementation]),,with_vnl=no)
AC_ARG_WITH(lapack, AC_HELP_STRING([--with-lapack],
	[prefix of lapack installation]),,with_lapack=no)

if test x${with_boost} = xno -a x${with_vnl} = xno; then
	AC_ERROR([please configure either --with-boost or --with-vnl])
fi
if test x${with_boost} != xno -a x${with_vnl} != xno; then
	AC_ERROR([please select either --with-boost or --with-vnl, but not both])
fi

dnl use boost
if test x${with_boost} != xno; then
	_BOOST_MATRIX_=1
	_VNL_MATRIX_=0

	if test x${with_boost} != xyes; then
		MATRIX_CFLAGS="${MATRIX_CFLAGS} -I${with_boost}/include"
		AC_MSG_NOTICE([using boost in ${with_boost}/include.])
	else
		AC_MSG_NOTICE([using boost in default location.])
		AC_MSG_NOTICE([configure --with-boost=path to choose a specific location.])
	fi
	MATRIX_LDFLAGS="${MATRIX_LDFLAGS} -llapack -lblas"
fi

dnl use VNL
if test x${with_vnl} != xno; then
	_BOOST_MATRIX_=0
	_VNL_MATRIX_=1

	if test x${with_vnl} != xyes; then
		MATRIX_CFLAGS="${MATRIX_CFLAGS} -I${with_vnl}/include"
		AC_MSG_NOTICE([using VNL in ${with_vnl}/include.])
	else
		AC_MSG_NOTICE([using VNL in default location.])
		AC_MSG_NOTICE([configure --with-vnl=path to choose a specific location.])
	fi
fi

dnl lapack path
if test x${with_lapack} != xno ; then
	if test x${with_lapack} = xyes ; then
		AC_ERROR([please specify path to lapack installation in --with-lapack])
	fi
	MATRIX_CFLAGS="${MATRIX_CFLAGS} -I${with_lapack}/include"
	MATRIX_LDFLAGS="-Wl,-R${with_lapack} -L${with_lapack}/lib ${MATRIX_LDFLAGS}"
fi


dnl --- small matrices implementation --------------------------------

AC_ARG_WITH(smallMatrix, AC_HELP_STRING([--with-smallMatrix],
	[Choose implementation for rigid body transformations]),,with_smallMatrix=no)

dnl test that small matrix implementation has been selected

if test x${with_smallMatrix} == xno; then
	AC_ERROR([Choose a small matrix and vector implementation --with-smallMatrix=[t3d,jrlMathTools]])
fi

dnl use t3d
if test x${with_smallMatrix} == xt3d; then
	_T3D_R3D_V3D_=1

	MATRIX_REQUIRE="t3d >= 2.5"
	AC_MSG_NOTICE([using T3D small matrices implementation.])

elif test  x${with_smallMatrix} == xjrlMathTools; then
	_T3D_R3D_V3D_=0

	MATRIX_REQUIRE="jrlMathTools >= 1.0"
	AC_MSG_NOTICE([using jrlMathTools small matrice and vector implementation.])

else
	AC_ERROR([Choose a small matrix and vector implementation --with-smallMatrix=[t3d or jrlMathTools]])
fi

PKG_CHECK_MODULES(SMALL_MATRIX_IMPL, [${MATRIX_REQUIRE}])
MATRIX_CFLAGS="${MATRIX_CFLAGS} ${SMALL_MATRIX_IMPL_CFLAGS}"
MATRIX_LDFLAGS="${MATRIX_LDFLAGS} ${SMALL_MATRIX_IMPL_LIBS}"

dnl --- output configuration files -----------------------------------

AC_OUTPUT(
	MatrixAbstractLayer.pc
	Makefile
	include/MatrixAbstractLayer/Makefile
	include/MatrixAbstractLayer/configMAL.h
	doc/Makefile
	doc/package.dox
	unitTesting/Makefile
	)
