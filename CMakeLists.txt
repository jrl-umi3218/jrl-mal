# Olivier Stasse, Francois Keith, JRL, CNRS/AIST
# Creation: 31/10/2008
# History:
#
# Copyright CNRS/AIST

# Copyright CNRS/AIST
cmake_minimum_required(VERSION 2.6)

enable_language(CXX)
enable_language(Fortran)

# Debug mode for cmake.
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Set version
SET(PROJECT_VERSION 1.5.99)

IF(WIN32)
  SET(LIBDIR_KW "/LIBPATH:")
  SET(LIBINCLUSION_KW "")
ENDIF(WIN32)

IF(UNIX)
  SET(LIBDIR_KW "-L")
  SET(LIBINCLUSION_KW "-l")
ENDIF(UNIX)

# name of the project
SET(PROJECT_NAME MatrixAbstractLayer)
SET(PROJECT_CONTACT olivier.stasse@aist.go.jp)

project(${PROJECT_NAME})

# Check for required packages
# -------------------------
INCLUDE(FindPkgConfig)
pkg_check_modules(JRLMATHTOOLS REQUIRED jrlMathTools>=1.0.99 )

SET(PACKAGE_REQUIREMENTS "jrlMathTools >= 1.0.99")

# Looking for LAPACK
# -------------------
INCLUDE(FindLAPACK)

# Looking for boost.
# -------------------------
INCLUDE(FindBoost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE( Boost 1.34.1 COMPONENTS thread )

SET(MATRIXLIB_FOUND 0)
SET(_BOOST_MATRIX_FOUND_ 0)
SET(_VNL_MATRIX_FOUND_ 0)
SET(_T3D_R3D_V3D_FOUND_ 0)

IF(LAPACK_FOUND)
  IF(Boost_FOUND)
    MESSAGE(STATUS "Current strategy prefer boost to VNL")
    MESSAGE(STATUS "Boost was found and will be used over VNL")
    SET(${${PROJECT_NAME}}_CFLAGS "-I${Boost_INCLUDE_DIR} -DNDEBUG -D_BOOST_ " )
	SET(${${PROJECT_NAME}}_LDFLAGS "")
	foreach(boost_lib_dir ${Boost_LIBRARY_DIRS})
		SET(${${PROJECT_NAME}}_LDFLAGS "${${${PROJECT_NAME}}_LDFLAGS} ${LIBDIR_KW}${boost_lib_dir} ")
	endforeach(boost_lib_dir)
	foreach(lapack_lib ${LAPACK_LIBRARIES})
		SET(${${PROJECT_NAME}}_LDFLAGS "${${${PROJECT_NAME}}_LDFLAGS} ${LIBINCLUSION_KW}${lapack_lib} ")
	endforeach(lapack_lib)
	IF (WIN32)
		SET(${${PROJECT_NAME}}_CFLAGS "${${${PROJECT_NAME}}_CFLAGS} -DBOOST_NUMERIC_BINDINGS_USE_CLAPACK" )
	ENDIF (WIN32)

    SET(MATRIXLIB_FOUND 1)
    SET(_BOOST_MATRIX_FOUND_ 1)
  ELSE(Boost_FOUND)
    # TO DO : find vnl...
  ENDIF(Boost_FOUND)

ENDIF(LAPACK_FOUND)

MESSAGE(STATUS "Cflags :" ${${${PROJECT_NAME}}_CFLAGS} )
MESSAGE(STATUS "Ldflags :" ${${${PROJECT_NAME}}_LDFLAGS} )
IF(NOT ${MATRIXLIB_FOUND})
  MESSAGE(SEND_ERROR "No matrix library found (neither boost/lapack or VNL...)")
ENDIF(NOT ${MATRIXLIB_FOUND})

#pkg_check_modules(T3D_R3D_V3D )


			  
# To deal with the headers.
#--------------------------
add_subdirectory(include)

# Prepare the documentation
# -------------------------
INCLUDE(FindDoxygen)
IF(DOXYGEN_FOUND)
  MESSAGE(STATUS "Doxygen found")
  add_subdirectory(doc)
ENDIF(DOXYGEN_FOUND)

# Prepare description file for pkg-config.
#-----------------------------------------

SET(install_pkg_prefix "\${prefix}")
SET(install_pkg_exec_prefix "\${exec_prefix}")
SET(install_pkg_libdir "\${libdir}")
SET(install_pkg_include_dir "\${includedir}")

# Install the file in the appropriate place.
SET(install_libdir_pkgconfig ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)

CONFIGURE_FILE(${${PROJECT_NAME}_SOURCE_DIR}/${PROJECT_NAME}.pc.cmake
	       ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc )

INSTALL(FILES ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc
	DESTINATION ${install_libdir_pkgconfig}	
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)




