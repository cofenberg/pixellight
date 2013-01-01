#*********************************************************#
#*  File: Toolchain-nacl.cmake                           *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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


# Required environment variable: NACL_PATH -> Path to the pepper API, example: c:/nacl_sdk/pepper_18


##################################################
## Toolchain for building with NaCL toolchain
##################################################

# Macro from the Android CMake toolchain file
#  See home page: http://code.google.com/p/android-cmake/
macro( __INIT_VARIABLE var_name )
 set( __test_path 0 )
 foreach( __var ${ARGN} )
  if( __var STREQUAL "PATH" )
   set( __test_path 1 )
   break()
  endif()
 endforeach()
 if( __test_path AND NOT EXISTS "${${var_name}}" )
  unset( ${var_name} CACHE )
 endif()
 if( "${${var_name}}" STREQUAL "" )
  set( __values 0 )
  foreach( __var ${ARGN} )
   if( __var STREQUAL "VALUES" )
    set( __values 1 )
   elseif( NOT __var STREQUAL "PATH" )
    set( __obsolete 0 )
    if( __var MATCHES "^OBSOLETE_.*$" )
     string( REPLACE "OBSOLETE_" "" __var "${__var}" )
     set( __obsolete 1 )
    endif()
    if( __var MATCHES "^ENV_.*$" )
     string( REPLACE "ENV_" "" __var "${__var}" )
     set( __value "$ENV{${__var}}" )
    elseif( DEFINED ${__var} )
     set( __value "${${__var}}" )
    else()
     if( __values )
      set( __value "${__var}" )
     else()
      set( __value "" )
     endif()
    endif()
    if( NOT "${__value}" STREQUAL "" )
     if( __test_path )
      if( EXISTS "${__value}" )
       set( ${var_name} "${__value}" )
       if( __obsolete )
        message( WARNING "Using value of obsolete variable ${__var} as initial value for ${var_name}. Please note, that ${__var} can be completely removed in future versions of the toolchain." )
       endif()
       break()
      endif()
     else()
      set( ${var_name} "${__value}" )
       if( __obsolete )
        message( WARNING "Using value of obsolete variable ${__var} as initial value for ${var_name}. Please note, that ${__var} can be completely removed in future versions of the toolchain." )
       endif()
      break()
     endif()
    endif()
   endif()
  endforeach()
  unset( __value )
  unset( __values )
  unset( __obsolete )
 endif()
 unset( __test_path )
endmacro()

# Detect current host platform
__INIT_VARIABLE(NACL_PATH PATH ENV_NACL_PATH)
set(TOOL_OS_SUFFIX "")
if(CMAKE_HOST_APPLE)
	# [TODO] Implement me
elseif(CMAKE_HOST_WIN32)
	set(NACL_HOST		win_x86_glibc)
	set(NACL_TAG		i686-nacl)
	set(TOOL_OS_SUFFIX	".exe")
elseif( CMAKE_HOST_UNIX )
	# [TODO] Implement me
else()
	message(FATAL_ERROR "Cross-compilation on your platform is not supported by this CMake toolchain")
endif()

# Toolchain name
set(CMAKETOOLS_TOOLCHAIN nacl)

# Target system
set(CMAKE_SYSTEM_NAME		Linux)
set(CMAKE_SYSTEM_VERSION	1)
set(NACL					True)

# Toolchain
set(CMAKE_ASM_COMPILER		${NACL_PATH}/toolchain/${NACL_HOST}/bin/${NACL_TAG}-as${TOOL_OS_SUFFIX})
set(CMAKE_C_COMPILER		${NACL_PATH}/toolchain/${NACL_HOST}/bin/${NACL_TAG}-gcc-4.4.3${TOOL_OS_SUFFIX})
set(CMAKE_CXX_COMPILER		${NACL_PATH}/toolchain/${NACL_HOST}/bin/${NACL_TAG}-c++${TOOL_OS_SUFFIX})
set(CMAKE_FIND_ROOT_PATH	${NACL_PATH}/toolchain/${NACL_HOST}/nacl)

# Don't use inline-assembler
set(CMAKETOOLS_CONFIG_NO_INLINE_ASM 1)

# Options 
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Internal options
set(CMAKE_SYSTEM_PROCESSOR	x86)
set(PL_NATIVE_PLPROJECT		0)
set(CMAKETOOLS_MINIMAL		1)
set(PL_MOBILE				0)
