#*********************************************************#
#*  File: Configure.cmake                                *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
## CMakeTools externals - Configure script
##
## Base for 'configure'-scripts
##################################################


##################################################
## Includes
##################################################
include(${CMAKETOOLS_DIR}/External/Base.cmake)


##################################################
## MACRO: external_configure_done
##
## Mark the end of a 'configure'-script
##################################################
macro(external_configure_done)
	# Create 'done'-file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Configure.done "done")
endmacro(external_configure_done)


##################################################
## Default actions
##################################################

# Remove 'done'-files
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Configure.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Build.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done)

# Set log file
set(CMAKETOOLS_CURRENT_LOG "${CMAKETOOLS_CURRENT_BUILD_DIR}/Log/Configure.log")
file(WRITE ${CMAKETOOLS_CURRENT_LOG} "")
