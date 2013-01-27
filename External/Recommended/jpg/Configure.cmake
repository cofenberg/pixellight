#*********************************************************#
#*  File: Configure.cmake                                *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the "Software"), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
	external_extract_tar(TARGZ "${CMAKETOOLS_CURRENT_DOWNLOAD_DIR}/jpegsrc.v8c.tar.gz" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/")

	# Configure project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Copy configuration from sample file
		external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/jconfig.vc" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/jconfig.h")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use configure script
		external_run_configure2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c")
	endif()
endif()

# Done
external_configure_done()
