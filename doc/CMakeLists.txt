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
#
SET(${${PROJECT_NAME}_SOURCE_DIR}/doc/docfiles
    ${${PROJECT_NAME}_SOURCE_DIR}/doc/header.html
    ${${PROJECT_NAME}_SOURCE_DIR}/doc/footer.html
    ${${PROJECT_NAME}_SOURCE_DIR}/doc/package.css
    ${${PROJECT_NAME}_SOURCE_DIR}/doc/pictures/footer.jpg
    ${${PROJECT_NAME}_SOURCE_DIR}/doc/additionalDoc/package.h
    ${${PROJECT_NAME}_SOURCE_DIR}/doc/package.dox
    )

# Configure package.dox file
CONFIGURE_FILE(${${PROJECT_NAME}_SOURCE_DIR}/doc/package.dox.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/doc/package.dox
)


ADD_CUSTOM_COMMAND(OUTPUT ${${PROJECT_NAME}_SOURCE_DIR}/doc/html/index.html
                   COMMAND ${DOXYGEN_EXECUTABLE} \"${${PROJECT_NAME}_SOURCE_DIR}/doc/package.dox\"
                   DEPENDS ${docfiles}
)

ADD_CUSTOM_TARGET(documentation ALL
                  DEPENDS ${${PROJECT_NAME}_SOURCE_DIR}/doc/html/index.html)

#
# Install html documentation
#

# html files
INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
  DESTINATION share/doc/${PROJECT_NAME})

# doxytag
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.doxytag
  DESTINATION share/doc/${PROJECT_NAME}/html)

# pictures
INSTALL(DIRECTORY ${${PROJECT_NAME}_SOURCE_DIR}/doc/pictures
  DESTINATION share/doc/${PROJECT_NAME}/)

