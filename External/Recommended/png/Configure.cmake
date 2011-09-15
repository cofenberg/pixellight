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
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Configure.cmake)

##################################################
## Configure
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Extract tar archive
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/libpng-1.5.4.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Configure project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Update VC project files
		external_vcproj_upgrade("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/projects/visualc71/libpng.vcproj")
		external_vcproj_upgrade("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/projects/visualc71/pngtest.vcproj")
		external_vcproj_upgrade("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/projects/visualc71/zlib.vcproj")

		# Copy zlib header
		external_makedir("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/zlib")
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/../zlib/include/zlib/zlib.h" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/zlib")
		external_copy("${CMAKETOOLS_CURRENT_DEST_DIR}/../zlib/include/zlib/zconf.h" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/zlib")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use configure script
		external_run_configure2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4")
	endif()
endif()

# Done
external_configure_done()
