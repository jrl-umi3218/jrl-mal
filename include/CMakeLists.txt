# Olivier Stasse, JRL, CNRS/AIST
# Creation: 31/10/2008
# History:
#
# Copyright CNRS/AIST

CONFIGURE_FILE(${${PROJECT_NAME}_SOURCE_DIR}/include/${PROJECT_NAME}/configMAL.h.cmake
	       ${${PROJECT_NAME}_SOURCE_DIR}/include/${PROJECT_NAME}/configMAL.h )

SET(${PROJECT_NAME}_HEADERS
configMAL.h					
MatrixAbstractLayer.h 				
MatrixAbstractLayerCheck.h 				
MatrixAbstractLayerBoost.h 			
MatrixAbstractLayerDoc.h 			
MatrixAbstractLayerSmall.h 			
MatrixAbstractLayerMatrix3x3JrlMath.h		
MatrixAbstractLayerMatrix4x4JrlMath.h		
MatrixAbstractLayerVector3JrlMath.h		
MatrixAbstractLayerVector4JrlMath.h		
MatrixAbstractLayerVNL.h 			
MatrixAbstractLayerT3D.h			
abstract.h					
abstractMatrix.h				
abstractVector.h				
boost.h						
boostMacros.h					
boostMatrix.h					
boostMatrixSvd.h					
boostspecific.h					
boostSvd.h					
boostVector.h					
)

# Recreate correct path for the headers
#--------------------------------------

SET(fullpath_${PROJECT_NAME}_HEADERS)
FOREACH(lHeader ${${PROJECT_NAME}_HEADERS})
  SET(fullpath_${PROJECT_NAME}_HEADERS 
    ${fullpath_${PROJECT_NAME}_HEADERS}
    ./${PROJECT_NAME}/${lHeader}
  )

ENDFOREACH(lHeader)

#----------------------------------------------------
# Install procedure for the header files
#----------------------------------------------------
INSTALL(FILES ${fullpath_${PROJECT_NAME}_HEADERS}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
