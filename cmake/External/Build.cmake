#*********************************************************#
#*  File: Build.cmake                                    *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the “Software”), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## CMakeTools externals - Build script
##
## Base for 'build'-scripts
##################################################


##################################################
## Includes
##################################################
include(${CMAKETOOLS_DIR}/External/Base.cmake)


##################################################
## MACRO: external_build_done
##
## Mark the end of a 'build'-script
##################################################
MACRO(external_build_done)
	# Create 'done'-file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Build.done "done")
ENDMACRO(external_build_done)


##################################################
## Default actions
##################################################

# Remove 'done'-files
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Build.done)
file(REMOVE ${CMAKETOOLS_CURRENT_BUILD_DIR}/Install.done)

# Set log file
set(CMAKETOOLS_CURRENT_LOG "${CMAKETOOLS_CURRENT_BUILD_DIR}/Log/Build.log")
file(WRITE ${CMAKETOOLS_CURRENT_LOG} "")
