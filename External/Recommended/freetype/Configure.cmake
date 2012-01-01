#*********************************************************#
#*  File: Configure.cmake                                *
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
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Configure.cmake)

##################################################
## Configure
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Extract tar archive
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/freetype-2.4.6.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Install cmake project
	set(cmakelists "${CMAKETOOLS_CURRENT_SOURCE_DIR}/Files/CMakeLists.txt")
	external_copy(${cmakelists} "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/freetype-2.4.6")

	# Configure project
	external_run_cmake("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/freetype-2.4.6")
endif()

# Done
external_configure_done()
