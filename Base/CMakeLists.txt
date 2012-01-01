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
project(Base)

##################################################
## Prerequisites
##################################################

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/Runtime/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/Runtime/Data/*.zip" "${PL_BIN_DIR}/Runtime/Data")

##################################################
## Target
##################################################
add_custom_target(Base)

##################################################
## Projects
##################################################
add_subdirectory(PLCore)
add_subdirectory(PLGraphics)
add_subdirectory(PLMath)
add_subdirectory(PLDatabase)
add_subdirectory(PLInput)
add_subdirectory(PLRenderer)
add_subdirectory(PLMesh)
add_subdirectory(PLScene)
add_subdirectory(PLPhysics)
add_subdirectory(PLSound)
add_subdirectory(PLEngine)
if(PL_PLGUI)
	add_subdirectory(PLGui)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Base)

##################################################
## Install
##################################################

# Data
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Runtime/Data
	DESTINATION ${PL_INSTALL_RUNTIME}		COMPONENT Runtime	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
