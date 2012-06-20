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
#*********************************************************/


[TODO] Bring me into PixelLight form


cmake_minimum_required(VERSION 2.8.3)


##################################################
## Define the project
##################################################
set(CURRENT_TARGET_NAME PLLoaderPVM)
project(${CURRENT_TARGET_NAME})


##################################################
## Find packages
##################################################
if(ANDROID)
	find_host_package(PixelLight)	# "find_package"-variant provided by "android.toolchain.cmake", required for PixelLight CMake variables like "PL_PLCORE_INCLUDE_DIR"
else()
	find_package(PixelLight REQUIRED)
endif()


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)				# The current source directory
include_directories(${PL_PLCORE_INCLUDE_DIR})							# PLCore headers
include_directories(${PL_PLMATH_INCLUDE_DIR})							# PLMath headers
include_directories(${PL_PLGRAPHICS_INCLUDE_DIR})						# PLGraphics headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../PLVolume/include/)	# PLVolume


##################################################
## Source codes
##################################################
set(CURRENT_SRC
	src/PLLoaderPVM.cpp				# Project main file
	src/ImageLoaderPVM.cpp			# Image loader for volume file format "pvm"
	src/VolumeLoaderPVM.cpp			# Volume loader for volume file format "pvm"
	src/PVM_GPL_License/ddsbase.cpp	# Volume file format "pvm" -> Lookout! GPL code!
)


##################################################
## Additional libraries
##################################################
add_libs(
	${PL_PLCORE_LIBRARY}
	${PL_PLMATH_LIBRARY}
	${PL_PLGRAPHICS_LIBRARY}
	PLVolume
)


##################################################
## Preprocessor definitions
##################################################
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_compile_defs(
		${LINUX_COMPILE_DEFS}
	)
endif()


##################################################
## Compiler flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_compile_flags(
		${WIN32_COMPILE_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_compile_flags(
		${LINUX_COMPILE_FLAGS}
	)
endif()


##################################################
## Linker flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_linker_flags(
		${WIN32_LINKER_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_linker_flags(
		${LINUX_LINKER_FLAGS}
	)
endif()


##################################################
## Build
##################################################
add_library(${CURRENT_TARGET_NAME} SHARED ${CURRENT_SRC})
target_link_libraries (${CURRENT_TARGET_NAME} ${libs})
set_project_properties(${CURRENT_TARGET_NAME})


##################################################
## Post-Build
##################################################
# Executable
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CURRENT_TARGET_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}"
)

# Plugin file
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND "${PL_ROOT}/Bin/Tools/${PL_ARCHBITSIZE}/PLProject${CMAKE_EXECUTABLE_SUFFIX}" ${CMAKE_CURRENT_SOURCE_DIR} --output-path "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}" --write-plugin
	WORKING_DIRECTORY ${dir}
)


##################################################
## Dependencies
##################################################
add_dependencies(${CURRENT_TARGET_NAME}	PLVolume)
