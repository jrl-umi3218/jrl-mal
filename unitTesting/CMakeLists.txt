# Olivier Stasse, JRL, CNRS/AIST
# Creation: 11/03/2009
# History:
#
# Copyright CNRS/
# For the test, we include the same files as the src
SET(${PROJECT_NAME}_test_CXXFLAGS "-I${PROJECT_SOURCE_DIR}/include/ ${${PROJECT_NAME}_CFLAGS} ${SMALLMATRIXLIB_CXXFLAGS} ${MATRIXLIB_CFLAGS}")

# For the test, we link with the library corresponding to the src,  which is not installed yet
SET(${PROJECT_NAME}_test_LDFLAGS "${${PROJECT_NAME}_LDFLAGS}")

MESSAGE(STATUS " unitTesting: ${${PROJECT_NAME}_test_CXXFLAGS}")
MESSAGE(STATUS " unitTesting: ${${PROJECT_NAME}_test_LDFLAGS}")

ADD_EXECUTABLE(	testdampedinverse testdampedinverse.cpp)
SET_TARGET_PROPERTIES(testdampedinverse
	              PROPERTIES
		      COMPILE_FLAGS ${${PROJECT_NAME}_test_CXXFLAGS}
		      LINK_FLAGS ${${PROJECT_NAME}_test_LDFLAGS}
)

ADD_DEPENDENCIES (testdampedinverse ${PROJECT_NAME})
				   
ADD_EXECUTABLE(	testpseudoinverse testpseudoinverse.cpp)
SET_TARGET_PROPERTIES(testpseudoinverse
	              PROPERTIES
		      COMPILE_FLAGS ${${PROJECT_NAME}_test_CXXFLAGS}
		      LINK_FLAGS ${${PROJECT_NAME}_test_LDFLAGS}
)

ADD_DEPENDENCIES (testpseudoinverse ${PROJECT_NAME})

ADD_EXECUTABLE(	tsvd 
tsvd.cpp 
TimeUtilsWindows.h
TimeUtilsWindows.cpp
)
SET_TARGET_PROPERTIES(tsvd
	              PROPERTIES
		      COMPILE_FLAGS ${${PROJECT_NAME}_test_CXXFLAGS}
		      LINK_FLAGS ${${PROJECT_NAME}_test_LDFLAGS}
)

ADD_DEPENDENCIES (tsvd ${PROJECT_NAME})

ADD_EXECUTABLE(	tsvddamped
tsvddamped.cpp 
TimeUtilsWindows.h
TimeUtilsWindows.cpp
)
SET_TARGET_PROPERTIES(tsvddamped
	              PROPERTIES
		      COMPILE_FLAGS ${${PROJECT_NAME}_test_CXXFLAGS}
		      LINK_FLAGS ${${PROJECT_NAME}_test_LDFLAGS}
)

ADD_DEPENDENCIES (tsvddamped ${PROJECT_NAME})

ADD_TEST(dampedinverse testdampedinverse "")
ADD_TEST(pseudoinverse testpseudoinverse "")
ADD_TEST(svd tsvd "")
ADD_TEST(svddamped tsvddamped "")
