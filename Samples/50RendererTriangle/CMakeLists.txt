#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
define_project(50RendererTriangle NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/Main.cpp
	src/Application50.cpp
	src/SPTriangle.cpp
	src/SPTriangleShaders.cpp
	src/SPTriangleFixedFunctions.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_LIB_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLCore
	PLMath
	PLGraphics
	PLRenderer
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
if(ANDROID)
	build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
else()
	build_executable(${CMAKETOOLS_CURRENT_TARGET} WIN32)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer)
add_dependencies(Samples						${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################
if(ANDROID)
	# Dynamic library
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_SAMPLES_BIN_DIR}
	)
else()
	# Executable
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} ${PL_SAMPLES_BIN_DIR}
	)
endif()

if(LINUX AND NOT ANDROID)
	add_runner_shell_script()
endif()

##################################################
## Install
##################################################
if(ANDROID)
	# Library
	install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
		RUNTIME DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT Samples
		LIBRARY DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT Samples
		ARCHIVE DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
	)
else()
	# Executable
	install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
		RUNTIME DESTINATION ${PL_INSTALL_SAMPLES_BIN}	COMPONENT SDK
	)
endif()

if(LINUX AND NOT ANDROID)
	# Install runner script
	install(PROGRAMS "${CMAKE_TOOLS_CURRENT_RUNNERSCRIPT}"
		DESTINATION ${PL_INSTALL_SAMPLES_BIN}/../	COMPONENT SDK
	)
endif()

# Source files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	DESTINATION ${PL_INSTALL_SAMPLES} 		COMPONENT SDK
	PATTERN "build" EXCLUDE
	PATTERN "enc_temp_folder" EXCLUDE
	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
	PATTERN "CMakeLists.txt" EXCLUDE
	PATTERN "50RendererTriangleInternal.sln" EXCLUDE
	PATTERN "50RendererTriangleInternal.vcxproj" EXCLUDE
	PATTERN "50RendererTriangleInternal.vcxproj.filters" EXCLUDE
)
