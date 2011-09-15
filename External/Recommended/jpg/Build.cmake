#*********************************************************#
#*  File: Build.cmake                                    *
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
include(${CMAKETOOLS_DIR}/External/Build.cmake)

##################################################
## Build
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Build project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Use nmake
		external_run_nmake("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/makefile.vc" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c" "")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use make
		external_run_make2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c")
	endif()
endif()

# Done
external_build_done()
