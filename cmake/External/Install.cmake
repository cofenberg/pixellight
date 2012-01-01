#*********************************************************#
#*  File: Install.cmake                                  *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#*********************************************************#


##################################################
## CMakeTools externals - Install script
##
## Base for 'install'-scripts
##################################################


##################################################
## Includes
##################################################
include(${CMAKETOOLS_DIR}/External/Base.cmake)


##################################################
## MACRO: external_install_pack
##
## Pack the result of the 'install'-script
##################################################
macro(external_install_pack)
	# Pack tar archive
	external_pack_tar(TARGZ "${CMAKETOOLS_CURRENT_EXT_DIR}/${CMAKETOOLS_CURRENT_NAME}.tar.gz" "${CMAKETOOLS_CURRENT_DEST_DIR}")
endmacro(external_install_pack)

##################################################
## MACRO: external_install_done
##
## Mark the end of a 'install'-script
##################################################
macro(external_install_done)
	# Create 'done'-file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done "done")
endmacro(external_install_done)


##################################################
## Default actions
##################################################

# Remove 'done'-files
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done)

# Set log file
set(CMAKETOOLS_CURRENT_LOG "${CMAKETOOLS_CURRENT_BUILD_DIR}/Log/Install.log")
file(WRITE ${CMAKETOOLS_CURRENT_LOG} "")

# Create include and lib directories
file(MAKE_DIRECTORY ${CMAKETOOLS_CURRENT_INCLUDE_DIR})
file(MAKE_DIRECTORY ${CMAKETOOLS_CURRENT_LIB_DIR})
