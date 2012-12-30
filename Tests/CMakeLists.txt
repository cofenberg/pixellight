#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
## Project
##################################################
project(Tests)

##################################################
## Prerequisites
##################################################

# Create "Tests"-directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Tests)
set(PL_TESTS_BIN_DIR "${PL_BIN_DIR}/Tests/${CMAKETOOLS_TARGET_ARCHBITSIZE}")
file(MAKE_DIRECTORY ${PL_TESTS_BIN_DIR})

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/Tests/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/Tests/Data/*.*" "${PL_BIN_DIR}/Tests/Data")

##################################################
## Target
##################################################
add_custom_target(Tests)

##################################################
## Projects
##################################################
add_subdirectory(PLUnitTests)
add_subdirectory(PLUnitTestsPerformance)
# Experimental
#	add_subdirectory(98GuiTest)
#	add_subdirectory(99Test)
#	add_subdirectory(99TestPlugin)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Tests)
