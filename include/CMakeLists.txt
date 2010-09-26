# Copyright 2008, 2009, 2010, Olivier Stasse, JRL, CNRS/AIST
#
# This file is part of MatrixAbstractLayer.
# MatrixAbstractLayer is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MatrixAbstractLayer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Lesser Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with MatrixAbstractLayer.  If not, see <http://www.gnu.org/licenses/>.
#

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
	DESTINATION include/${PROJECT_NAME}
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
