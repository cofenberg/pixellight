#*********************************************************#
#*  File: CMakeTools.cmake                               *
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
## CMakeTools
##
## CMakeTools is a collection of cmake scripts and macros that provides
## a simplified build system framework to build C++ applications, libraries,
## documentation and packages for your project.
##
##
## General variables:
##   CMAKETOOLS_DIR						Path to CMakeTools directory
##   CMAKETOOLS_GENERATOR				Name of used generator (same as CMAKE_GENERATOR, but gets passed also to external scripts)
##   CMAKETOOLS_HOST_SYSTEM				Name of host system ("Windows", "Linux" or "Apple")
##   CMAKETOOLS_HOST_SYSTEM_WIN32		Set if host system is "Windows"
##   CMAKETOOLS_HOST_SYSTEM_LINUX       Set if host system is "Linux"
##   CMAKETOOLS_HOST_SYSTEM_APPLE       Set if host system is "Apple"
##   CMAKETOOLS_TARGET_SYSTEM			Name of target system ("Windows", "Linux" or "Apple")
##   CMAKETOOLS_TARGET_SYSTEM_WIN32		Set if target system is "Windows"
##   CMAKETOOLS_TARGET_SYSTEM_LINUX     Set if target system is "Linux"
##   CMAKETOOLS_TARGET_SYSTEM_APPLE     Set if target system is "Apple"
##   CMAKETOOLS_TOOLCHAIN        		Name of used toolchain
##
## Configuration variables:
##   CMAKETOOLS_CONFIG_NO_INLINE_ASM    Is inline assembler code allowed? (no, if variable is defined)
##   CMAKETOOLS_CONFIG_NIGHTLY          Is this a nightly build? (true/false)
##   CMAKETOOLS_CONFIG_SUFFIX           Suffix that is added to all libraries (e.g. "sdk"  -> "libmylib-sdk")
##   CMAKETOOLS_CONFIG_DEBUG_SUFFIX     Suffix that is added to all debug project (e.g. "D" -> "libmylibD-sdk")
##   CMAKETOOLS_CONFIG_NAME				Configuration name (e.g. "Windows", "Linux", or "Linux-armv4")
##
## Project information:
##   CMAKETOOLS_PROJECT_NAME			Overall project name
##   CMAKETOOLS_PROJECT_VERSION_MAJOR   Major version number (e.g. "1"   for V1.2.5)
##   CMAKETOOLS_PROJECT_VERSION_MINOR   Minor version number (e.g. "2"   for V1.2.5)
##   CMAKETOOLS_PROJECT_VERSION_PATCH   Patch number         (e.g. "5"   for V1.2.5)
##   CMAKETOOLS_PROJECT_VERSION_RC      Release candidate    (e.g. "RC1" for V1.2.5 RC1)
##   CMAKETOOLS_PROJECT_VERSION_REV     Revision number
##   CMAKETOOLS_UPLOAD_LOCATION         Upload location for built packages
##
## Current project (General):
##   CMAKETOOLS_CURRENT_NAME            Name of current project (e.g. "mylib")
##   CMAKETOOLS_CURRENT_TARGET          Name of current target (e.g. "mylib", "Docs-mylib", "External-libXYZ")
##   CMAKETOOLS_CURRENT_EXT_DIR			Path to externals
##
## Current project (Apps):
##   CMAKETOOLS_CURRENT_SUFFIX			Suffix of current target (e.g. "sdk")
##   CMAKETOOLS_CURRENT_OUTPUT_NAME		Output name of current target (e.g. "libmylib.a")
##   CMAKETOOLS_CURRENT_SOURCES			Source list of current target
##   CMAKETOOLS_CURRENT_LIBS			External libraries list of current target
##   CMAKETOOLS_CURRENT_COMPILE_DEFS	Compile (preprocessor) definitions of current target
##   CMAKETOOLS_CURRENT_COMPILE_FLAGS	Compiler flags of current target
##   CMAKETOOLS_CURRENT_LINK_FLAGS		Linker flags of current target
##
## Current project (Externals):
##   CMAKETOOLS_CURRENT_SOURCE_DIR		Directory that contains the external project
##   CMAKETOOLS_CURRENT_DOWNLOAD_DIR	Directory into which files are downloaded
##   CMAKETOOLS_CURRENT_BUILD_DIR		Directory in which the sources are being compiled
##   CMAKETOOLS_CURRENT_DEST_DIR		Target directory for the project 
##   CMAKETOOLS_CURRENT_INCLUDE_DIR		Target directory for include files
##   CMAKETOOLS_CURRENT_LIB_DIR			Target directory for libraries
##   CMAKETOOLS_CURRENT_BUILT_FILE		If this file exist, external is built
##################################################


##################################################
## General macros 
##################################################

##################################################
## MACRO: cmaketools_debug_message
##
## Output a debug message (only visible if CMAKETOOLS_DEBUG is set) 
##################################################
macro(cmaketools_debug_message msg)
	if(CMAKETOOLS_DEBUG)
		message(STATUS ${msg})
	endif()
endmacro(cmaketools_debug_message msg)

##################################################
## MACRO: cmaketools_debug_variable
##
## Output the content of a variable as a debug message (only visible if CMAKETOOLS_DEBUG is set) 
##################################################
macro(cmaketools_debug_variable var)
	cmaketools_debug_message("${var} = ${${var}}")
endmacro(cmaketools_debug_variable var)

##################################################
## MACRO: make_windows_path
##
## Convert a path to Windows style 
##################################################
macro(make_windows_path pathname)
	string(REPLACE "/" "\\\\" ${pathname} "${${pathname}}")
endmacro(make_windows_path)

##################################################
## MACRO: copy_file
##
## Copy a file from one place to another 
##################################################
macro(copy_file src dest)
	# Copy file
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${src} ${dest})
endmacro(copy_file src dest)

##################################################
## MACRO: copy_files
##
## Copy files from one place to another using wildcards 
##################################################
macro(copy_files src dest)
	# Get path
	get_filename_component(path ${src} PATH)

	# Get exclude option
	set(exclude)
	if ("${ARGV2}" STREQUAL "EXCLUDE")
		set(exclude ${ARGV3})
	endif()

	# Find files
	file(GLOB_RECURSE files RELATIVE ${path} ${src})

	# Find files
	foreach(file ${files})
		# Get source and destination file
		set(src_file ${path}/${file})
		set(dst_file ${dest}/${file})

		# Check exclude expression
		set(copy 1)
		if(exclude)
			if(file MATCHES ${exclude})
				set(copy 0)
			endif()
		endif()

		# Process file
		if(copy EQUAL 1)
			# Create output directory
			get_filename_component(dst_path ${dst_file} PATH)
			file(MAKE_DIRECTORY ${dst_path})

			# Copy file
			execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${src_file} ${dst_file})
		endif()
	endforeach(file ${files})
endmacro(copy_files src dest)

##################################################
## MACRO: add_to_list
##
## Add variable to list 
##################################################
macro(add_to_list var)
	foreach(value ${ARGN})
		set(${var} ${${var}} ${value})
	endforeach()
endmacro(add_to_list var)

##################################################
## MACRO: remove_from_list
##
## Remove variable from list 
##################################################
macro(remove_from_list var)
	set(new_value "")
	string(REPLACE " " ";" oldvar "${var}")
	foreach(value ${${oldvar}})
		set(found 0)
		foreach(remove ${ARGN})
			if(value STREQUAL ${remove})
				set(found 1)
			endif()
		endforeach()
		if(NOT found)
			set(new_value ${new_value} ${value})
		endif()
	endforeach()
	set(${var} ${new_value})
endmacro(remove_from_list var)

##################################################
## MACRO: add_to_string
##
## Add variable to string 
##################################################
macro(add_to_string var)
	foreach(value ${ARGN})
		set(${var} "${${var}} ${value}")
	endforeach()
endmacro(add_to_string var)

##################################################
## MACRO: remove_from_string
##
## Remove variable from string 
##################################################
macro(remove_from_string var)
	set(new_value " ")
	foreach(value ${${var}})
		set(found 0)
		foreach(remove ${ARGN})
			if(value STREQUAL ${remove})
				set(found 1)
			endif()
		endforeach()
		if(NOT found)
			set(new_value "${new_value} ${value}")
		endif()
	endforeach()
	set(${var} "${new_value}")
endmacro(remove_from_string var)


##################################################
## CMakeTools initialization 
##################################################

# Activate this for global debug mode
#set(CMAKETOOLS_DEBUG 1)

# Get path to CMakeTools
get_filename_component(CMAKETOOLS_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
cmaketools_debug_variable(CMAKETOOLS_DIR)

# Add CMakeTools to CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKETOOLS_DIR}/Modules)
cmaketools_debug_variable(CMAKE_MODULE_PATH)

# Linux standalone: Set Linux RPATH to "$ORIGIN" so shared libraries are first searched
# within the directory of the executable (see http://www.cmake.org/Wiki/CMake_RPATH_handling)
# Type e.g. "objdump -x libPLCore.so" and have a look at "Dynamic Section"->"RPATH",
# should be "$ORIGIN" when this option is enabled
if (CMAKETOOLS_SET_RPATH_TO_ORIGIN)
	SET(CMAKE_SKIP_BUILD_RPATH				TRUE)		# TRUE for standalone
	SET(CMAKE_BUILD_WITH_INSTALL_RPATH		ON) 		# ON for standalone
	SET(CMAKE_INSTALL_RPATH					"$ORIGIN")	# NOT "." for the same directory, the executable is in!
	SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH	FALSE)
endif()

# Get host system
set(CMAKETOOLS_HOST_SYSTEM "")
set(CMAKETOOLS_HOST_SYSTEM_WIN32)
set(CMAKETOOLS_HOST_SYSTEM_LINUX)
set(CMAKETOOLS_HOST_SYSTEM_APPLE)
if(CMAKE_HOST_WIN32)
	set(CMAKETOOLS_HOST_SYSTEM			"Windows")
	set(CMAKETOOLS_HOST_SYSTEM_WIN32	"1")
elseif(CMAKE_HOST_APPLE)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(CMAKETOOLS_HOST_SYSTEM		"MacOSX")
	else()
		set(CMAKETOOLS_HOST_SYSTEM		"Apple")
	endif()
	set(CMAKETOOLS_HOST_SYSTEM_APPLE	"1")
elseif(CMAKE_HOST_UNIX)
	set(CMAKETOOLS_HOST_SYSTEM			"Linux")
	set(CMAKETOOLS_HOST_SYSTEM_LINUX	"1")
endif()
cmaketools_debug_variable(CMAKETOOLS_HOST_SYSTEM)
cmaketools_debug_variable(CMAKETOOLS_HOST_SYSTEM_WIN32)
cmaketools_debug_variable(CMAKETOOLS_HOST_SYSTEM_LINUX)
cmaketools_debug_variable(CMAKETOOLS_HOST_SYSTEM_APPLE)

# Get target system
set(CMAKETOOLS_TARGET_SYSTEM "")
set(CMAKETOOLS_TARGET_SYSTEM_WIN32)
set(CMAKETOOLS_TARGET_SYSTEM_LINUX)
set(CMAKETOOLS_TARGET_SYSTEM_APPLE)
if(WIN32)
	set(CMAKETOOLS_TARGET_SYSTEM		"Windows")
	set(CMAKETOOLS_TARGET_SYSTEM_WIN32	"1")
elseif(APPLE)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(CMAKETOOLS_TARGET_SYSTEM	"MacOSX")
	else()
		set(CMAKETOOLS_TARGET_SYSTEM	"Apple")
	endif()
	set(CMAKETOOLS_TARGET_SYSTEM_APPLE	"1")

	# We're reusing the Linux port
	set(CMAKETOOLS_TARGET_SYSTEM_LINUX	"1")
	set(LINUX							"1")
elseif(UNIX)
	set(CMAKETOOLS_TARGET_SYSTEM		"Linux")
	set(CMAKETOOLS_TARGET_SYSTEM_LINUX	"1")
	set(LINUX							"1")
endif()
cmaketools_debug_variable(CMAKETOOLS_TARGET_SYSTEM)
cmaketools_debug_variable(CMAKETOOLS_TARGET_SYSTEM_WIN32)
cmaketools_debug_variable(CMAKETOOLS_TARGET_SYSTEM_LINUX)
cmaketools_debug_variable(CMAKETOOLS_TARGET_SYSTEM_APPLE)

# Get config name
set(CMAKETOOLS_CONFIG_NAME ${CMAKETOOLS_TARGET_SYSTEM})
if(CMAKETOOLS_TOOLCHAIN)
	set(CMAKETOOLS_CONFIG_NAME "${CMAKETOOLS_CONFIG_NAME}-${CMAKETOOLS_TOOLCHAIN}")
endif()
cmaketools_debug_variable(CMAKETOOLS_CONFIG_NAME)

# Get target generator
set(CMAKETOOLS_GENERATOR ${CMAKE_GENERATOR})
cmaketools_debug_variable(CMAKETOOLS_GENERATOR)

# Check build type (Debug/Release, default to Release)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug/Release)")
endif(NOT CMAKE_BUILD_TYPE)
cmaketools_debug_variable(CMAKE_BUILD_TYPE)

# Set suffix based on build type
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKETOOLS_CONFIG_DEBUG_SUFFIX "D")
else()
	set(CMAKETOOLS_CONFIG_DEBUG_SUFFIX "")
endif()

# Find VC command line tools
find_package(VCTools)

# Find sfk
find_package(SFK)

# Find scp
find_package(SCP)

# Find diff and patch
find_package(Diff)

# Include platform files
if(WIN32)
	include(${CMAKETOOLS_DIR}/Platforms/WindowsMSVC.cmake)
elseif(LINUX)
	# Common settings
	include(${CMAKETOOLS_DIR}/Platforms/LinuxCommon.cmake)

	# Android NDK ("CMAKE_CXX_COMPILER_ID" matches also "GNU", so this test must come first)
	if(ANDROID)
		include(${CMAKETOOLS_DIR}/Platforms/LinuxNDK.cmake)

	# NaCL ("CMAKE_CXX_COMPILER_ID" matches also "GNU", so this test must come first)
	elseif(NACL)
		include(${CMAKETOOLS_DIR}/Platforms/LinuxNaCL.cmake)

	# GCC
	elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
		include(${CMAKETOOLS_DIR}/Platforms/LinuxGCC.cmake)

	# Clang
	elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
		include(${CMAKETOOLS_DIR}/Platforms/LinuxClang.cmake)

	# ?
	else()
		message(FATAL_ERROR "Unsupported compiler, use GNU, Clang or NDK")
	endif()
endif()
