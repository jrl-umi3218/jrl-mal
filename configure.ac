
dnl 
dnl configure.ac file for package MatrixAbstractLayer 
dnl

AC_INIT([MatrixAbstractLayer], [1.2], [olivier.stasse@aist.go.jp])
AC_PREREQ(2.59)

AM_INIT_AUTOMAKE

AC_PROG_CXX
AC_PROG_INSTALL

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
		AC_MSG_NOTICE([using boot in ${with_boost}/include.])
	else
		AC_MSG_NOTICE([using boot in default location.])
		AC_MSG_NOTICE([configure --with-boost=path to choose a specific location.])
	fi
	MATRIX_LDFLAGS="${MATRIX_LDLAGS} -llapack -lblas"
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

AC_ARG_WITH(t3d, AC_HELP_STRING([--with-t3d],
	[use t3d for rigid body transformations]),,with_t3d=no)

dnl use t3d
if test x${with_t3d} != xno; then
	_T3D_R3D_V3D_=1

	if test x${with_t3d} != xyes; then
		AC_ERROR([do not supply a path to --with-t3d: pkg-config is used])
	fi

	MATRIX_REQUIRE="t3d >= 2.2"
	PKG_CHECK_MODULES(T3D, [t3d >= 2.2])
	MATRIX_CFLAGS="${MATRIX_CFLAGS} ${T3D_CFLAGS}"
	MATRIX_LDFLAGS="${MATRIX_LDFLAGS} ${T3D_LIBS}"
	AC_MSG_NOTICE([using T3D small matrices implementation.])
else
	_T3D_R3D_V3D_=0
	AC_MSG_NOTICE([using default small matrices implementation.])
fi

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
