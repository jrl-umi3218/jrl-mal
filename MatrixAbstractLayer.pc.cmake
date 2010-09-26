# Copyright 2008, 2009, 2010, O. Stasse, F. Lamiraux, CNRS/AIST
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
# GNU Lesser General Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with MatrixAbstractLayer.  If not, see <http://www.gnu.org/licenses/>.
#

prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${install_pkg_prefix}/bin
libdir=${install_pkg_prefix}/lib
includedir=${install_pkg_prefix}/include
datarootdir=${install_pkg_prefix}/share
docdir=${install_pkg_prefix}/share/doc/${CMAKE_PROJECT_NAME}

Name: ${PROJECT_NAME}
Description: Macros for versatile matrix and vector definitions and operations
Version: ${PROJECT_VERSION}
Requires: ${PACKAGE_REQUIREMENTS}
Libs:   ${LIBDIR_KW}${install_pkg_libdir} ${${PROJECT_NAME}_LDFLAGS}
Cflags: -I${install_pkg_include_dir} ${${PROJECT_NAME}_CFLAGS}
