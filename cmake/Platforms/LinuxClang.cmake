#*********************************************************#
#*  File: LinuxClang.cmake                               *
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
## Linux/clang platform definitions
##
## This file contains compiler and linker settings which are specific to the clang compiler suit under linux
##################################################


##################################################
## Libraries
##################################################

# X11 libraries
set(LINUX_X11_LIBS
	X11									# X-Lib
	Xext								# X extentions library
	Xcursor								# X cursor library
)
set(LINUX_X11_LIB		X11)			# X-Lib
set(LINUX_XEXT_LIB		Xext)			# X extentions library
set(LINUX_XCURSOR_LIB	Xcursor)		# X cursor library


##################################################
## Preprocessor definitions
##################################################

# Preprocessor definitions
if(APPLE)
	# Add a handy APPLE definition (just like WIN32, LINUX and so on)
	set(LINUX_COMPILE_DEFS
		${LINUX_COMPILE_DEFS}
		APPLE							# We are building for an APPLE OS
	)

	# No visibility compiler flags for now or we get issues with several vtables
	set(NO_VISIBILITY_CHECK 1)			# Do not add the visibility related compiler flags within "CheckLinuxCompiler.cmake" below
endif()


##################################################
## Version checks
##################################################
# Do only this check when using the Makefiles cmake generator
IF(CMAKE_GENERATOR MATCHES "Makefiles")
	MESSAGE(STATUS "Check for clang compiler version")
	SET(CMAKE_TEST_COMPILER ${CMAKE_C_COMPILER})
	IF (NOT CMAKE_C_COMPILER)
		SET(CMAKE_TEST_COMPILER ${CMAKE_CXX_COMPILER})
	ENDIF(NOT CMAKE_C_COMPILER)

	EXEC_PROGRAM(${CMAKE_TEST_COMPILER}
		ARGS --version
		OUTPUT_VARIABLE CMAKE_COMPILER_OUTPUT
		RETURN_VALUE CMAKE_COMPILER_RETURN
	)
	IF(NOT CMAKE_COMPILER_RETURN)
		FILE(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
			"Determining the version of compiler passed with the following output:\n"
			"${CMAKE_COMPILER_OUTPUT}\n\n")
		STRING(REGEX REPLACE "\n" " " compilerVersion "${CMAKE_COMPILER_OUTPUT}")
		MESSAGE(STATUS "Check for clang compiler version - ${compilerVersion}")
		SET(Cang3)
		string(REGEX REPLACE "^.*[ ]([0-9]+)\\.[0-9].*$" "\\1" CLANG_MAJOR "${compilerVersion}")
		string(REGEX REPLACE "^.*[ ][0-9]+\\.([0-9]).*$" "\\1" CLANG_MINOR "${compilerVersion}")
		SET(Clang${CLANG_MAJOR} 1)
		SET(Clang_VERSION "${CLANG_MAJOR}.${CLANG_MINOR}")
	ELSE(NOT CMAKE_COMPILER_RETURN)
		MESSAGE(STATUS "Check for Clang compiler version - failed")
		FILE(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
			"Determining the version of compiler failed with the following output:\n"
			"${CMAKE_COMPILER_OUTPUT}\n\n")
	ENDIF(NOT CMAKE_COMPILER_RETURN)

	SET(MIN_CLANG_VERSION "3.0")
	IF(Clang_VERSION VERSION_LESS MIN_CLANG_VERSION)
		Message(FATAL_ERROR "Clang version \"${Clang_VERSION}\" not supported at least Clang version ${MIN_CLANG_VERSION} is needed")
	endif()
ENDIF(CMAKE_GENERATOR MATCHES "Makefiles")

# Check compiler features
# currently clang < 3.2 has problems with visibility and template instances which gets exported in a library (see http://llvm.org/bugs/show_bug.cgi?id=10113)
# and it adds references to methods to the export table which shouldn't be there (e.g. PLMesh: PLCore::ElementManager<PLRenderer::Animation>::GetByIndex(unsigned int) const) see http://llvm.org/bugs/show_bug.cgi?id=12714
IF(Clang_VERSION VERSION_LESS "3.2")
	set(NO_VISIBILITY_CHECK 1)
endif()
include(${CMAKETOOLS_DIR}/Modules/CheckLinuxCompiler.cmake)	# Adds e.g. visibility attribute (http://gcc.gnu.org/wiki/Visibility)


##################################################
## Compiler flags
##################################################

set(LINUX_COMPILE_FLAGS
	${LINUX_COMPILE_FLAGS}
	-msse3								# Use SSE3 instruction set / code might not run on CPUs with no sse3 instruction
)
if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
		-O2								# Balance speed and binary size
		# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
		-fomit-frame-pointer			# Don't keep the frame pointer in a register for functions that don't need one
	)
endif()
