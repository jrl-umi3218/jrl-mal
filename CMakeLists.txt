# Olivier Stasse, Francois Keith, JRL, CNRS/AIST
# Creation: 31/10/2008
# History:
#
# Copyright CNRS/AIST

# Copyright CNRS/AIST
cmake_minimum_required(VERSION 2.6)

enable_language(CXX)
enable_language(Fortran)

ENABLE_TESTING()

# Debug mode for cmake.
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Set version
# CPack version numbers for release tarball name.
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 9)
set(CPACK_PACKAGE_VERSION_PATCH 0)

SET(PROJECT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.99)
MESSAGE(STATUS "Project Version:${PROJECT_VERSION}")

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

# where are use-specific cmake modules
SET(CMAKE_MODULE_PATH ${${PROJECT_NAME}_SOURCE_DIR}/CMakeModules)

# Load Pkgconfig macros
# ---------------------
INCLUDE(FindPkgConfig)

# Strategy to detect small matrices computation
# ---------------------------------------------
SET(SMALLMATRIXLIB_FOUND 0)

# Required versions of dependencies
# ---------------------------------
SET(T3D_REQUIRED_VERSION 2.5)
SET(JRLMATHTOOLS_REQUIRED_VERSION 1.2)


# handle jrlMathTools
IF (SMALLMATRIX STREQUAL "jrlMathTools")
  # Check for required packages
  # -------------------------
  pkg_check_modules(JRLMATHTOOLS REQUIRED jrlMathTools>=${JRLMATHTOOLS_REQUIRED_VERSION})

  SET(PACKAGE_REQUIREMENTS "jrlMathTools >= ${JRLMATHTOOLS_REQUIRED_VERSION}")
  SET(SMALLMATRIXLIB_FOUND 1)		 
  SET(SMALLMATRIXLIB_CXXFLAGS ${JRLMATHTOOLS_CFLAGS})
ENDIF(SMALLMATRIX STREQUAL "jrlMathTools")

# handle t3d
SET(_T3D_R3D_V3D_FOUND_ 0)
IF (SMALLMATRIX STREQUAL "t3d")
  # Looking for T3d and jrlMathTools
  # 
  # jrlMathTools is required for 3x3 matrices that are not rotation matrices.
  #
  # -------------------------
  pkg_check_modules(T3D REQUIRED t3d>=${T3D_REQUIRED_VERSION})
  pkg_check_modules(JRLMATHTOOLS REQUIRED jrlMathTools>=${JRLMATHTOOLS_REQUIRED_VERSION})
  SET(PACKAGE_REQUIREMENTS "t3d >= ${T3D_REQUIRED_VERSION}, jrlMathTools >= ${JRLMATHTOOLS_REQUIRED_VERSION}")
  SET(_T3D_R3D_V3D_FOUND_ 1)
  SET(SMALLMATRIXLIB_FOUND 1)		 
  SET(SMALLMATRIXLIB_CXXFLAGS ${T3D_CFLAGS})
ENDIF(SMALLMATRIX STREQUAL "t3d")

IF(NOT ${SMALLMATRIXLIB_FOUND})
  MESSAGE(FATAL_ERROR "No small matrix library found or specified (neither t3d or jrlMathTools...).\n Please try one of the two following commands: \n cmake -DSMALLMATRIX="t3d" .. \n or \n cmake -DSMALLMATRIX="jrlMathTools" ..")
ENDIF(NOT ${SMALLMATRIXLIB_FOUND})

# Looking for LAPACK
# -------------------
INCLUDE(FindLAPACK)

# Looking for boost.
# -------------------------
INCLUDE(FindBoost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE( Boost 1.33.1 )

SET(MATRIXLIB_FOUND 0)
SET(_BOOST_MATRIX_FOUND_ 0)
SET(_VNL_MATRIX_FOUND_ 0)

IF(LAPACK_FOUND)
  IF(Boost_FOUND)
    MESSAGE(STATUS "Current strategy prefer boost to VNL")
    MESSAGE(STATUS "Boost was found and will be used over VNL")
    SET(${PROJECT_NAME}_CFLAGS "-I${Boost_INCLUDE_DIR}" )
	SET(${PROJECT_NAME}_LDFLAGS "")
	foreach(boost_lib_dir ${Boost_LIBRARY_DIRS})
		SET(${PROJECT_NAME}_LDFLAGS "${${PROJECT_NAME}_LDFLAGS} ${LIBDIR_KW}${boost_lib_dir} ")
	endforeach(boost_lib_dir)
	foreach(lapack_lib ${LAPACK_LIBRARIES})
		SET(${PROJECT_NAME}_LDFLAGS "${${PROJECT_NAME}_LDFLAGS} ${lapack_lib} ")
	endforeach(lapack_lib)
	IF (WIN32)
		SET(${PROJECT_NAME}_CFLAGS "${${PROJECT_NAME}_CFLAGS} -DBOOST_NUMERIC_BINDINGS_USE_CLAPACK" )
	ENDIF (WIN32)

    SET(MATRIXLIB_FOUND 1)
    SET(_BOOST_MATRIX_FOUND_ 1)
  ELSE(Boost_FOUND)
    # TO DO : find vnl...
  ENDIF(Boost_FOUND)

ENDIF(LAPACK_FOUND)

# --- BOOST NUMERIC BINDINGS-------------------------------------
IF (Boost_VERSION LESS 104000)
  INCLUDE(${CMAKE_MODULE_PATH}/FindBoostNumericBindings.cmake)
  MESSAGE(STATUS "BoostNumericBindings_INCLUDE_DIR=${BoostNumericBindings_INCLUDE_DIR}")
  INCLUDE_DIRECTORIES(${BoostNumericBindings_INCLUDE_DIR})
  SET(${PROJECT_NAME}_CFLAGS "${${PROJECT_NAME}_CFLAGS} -I${BoostNumericBindings_INCLUDE_DIR}")

  MESSAGE(STATUS "Cflags :" ${${PROJECT_NAME}_CFLAGS} )
  MESSAGE(STATUS "Ldflags :" ${${PROJECT_NAME}_LDFLAGS} )
  IF(NOT ${MATRIXLIB_FOUND})
    MESSAGE(FATAL_ERROR "No matrix library found (neither boost/lapack or VNL...)")
  ENDIF(NOT ${MATRIXLIB_FOUND})
ENDIF(Boost_VERSION LESS 104000)

#pkg_check_modules(T3D_R3D_V3D )

# To deal with the headers.
#--------------------------
add_subdirectory(include)

# Prepare the documentation
# -------------------------
OPTION(GENERATE_DOC 0 "Generate html documentation")
IF (GENERATE_DOC)
  INCLUDE(FindDoxygen)
  IF(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen found")
	ADD_SUBDIRECTORY(doc)
  ENDIF(DOXYGEN_FOUND)
ENDIF (GENERATE_DOC)

# Uninstall target.
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# Prepare description file for pkg-config.
#-----------------------------------------

SET(install_pkg_prefix "\${prefix}")
SET(install_pkg_exec_prefix "\${exec_prefix}")
SET(install_pkg_libdir "\${libdir}")
SET(install_pkg_include_dir "\${includedir}")

IF(UNIX)
	SET (${PROJECT_NAME}_LDFLAGS "-Wl,-R${install_pkg_libdir} ${${PROJECT_NAME}_LDFLAGS}")
ENDIF(UNIX)

# Install the file in the appropriate place.
SET(install_libdir_pkgconfig lib/pkgconfig)

CONFIGURE_FILE(${${PROJECT_NAME}_SOURCE_DIR}/${PROJECT_NAME}.pc.cmake
	       ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc )

INSTALL(FILES ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc
	DESTINATION ${install_libdir_pkgconfig}	
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

#---------------
# Package target
#---------------
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Matrix Abstract Layer - Define an abstract layer to manipulate matrices")
set(CPACK_PACKAGE_VENDOR "JRL CNRS/AIST")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set(CPACK_PACKAGE_CONTACT "Olivier Stasse")

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "jrlmathtools (>=1.2)")
set(CPACK_PACKAGE_NAME "matrixabstractlayer")
set(
CPACK_SOURCE_PACKAGE_FILE_NAME
"matrixabstractlayer-src-${PROJECT_VERSION}"
CACHE INTERNAL "tarball basename"
)

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
"~$"
"^${PROJECT_SOURCE_DIR}/build/"
"^${PROJECT_SOURCE_DIR}/.git/"
)

#message("CPACK_SOURCE_IGNORE_FILES = ${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)

	
