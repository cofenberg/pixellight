#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
add_subdirectory(PLTest)		# [TODO] Remove me when the new unit tests are there
add_subdirectory(PLTestBase)	# [TODO] Remove me when the new unit tests are there
# Experimental
#	add_subdirectory(98GuiTest)
#	add_subdirectory(99Test)
#	add_subdirectory(99TestPlugin)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Tests)
