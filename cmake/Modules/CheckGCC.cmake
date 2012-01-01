#*********************************************************#
#*  File: CheckGCC.cmake                                 *
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
## CheckGCC
##
## Additional checks for the GCC compiler
##
##
## Variables:
##   CMAKETOOLS_GCC_VISIBILITY_FLAG     Set if GCC has the visibility flag available (http://gcc.gnu.org/wiki/Visibility)
##   CMAKETOOLS_GCC_CPP0X_FLAG          Set if GCC has the experimental support for the upcoming ISO C++ standard C++0x (see http://gcc.gnu.org/gcc-4.6/cxx0x_status.html), now known as C++11
##################################################


##################################################
## Includes
##################################################
INCLUDE (CheckCXXSourceCompiles)


##################################################
## Macro: Check if GCC visibility flag is available
##################################################
macro(cmaketools_check_cxx_visibility_flag var)
	set(SAFE_CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}")
	set(CMAKE_REQUIRED_DEFINITIONS "-fvisibility=hidden -fvisibility-inlines-hidden")
	set(CODE "__attribute__ ((visibility(\"default\"))) void testfunc(){} int main() {return 0;}")
	check_cxx_source_compiles("${CODE}" ${var})
	set(CMAKE_REQUIRED_DEFINITIONS "${SAFE_CMAKE_REQUIRED_DEFINITIONS}")
endmacro(cmaketools_check_cxx_visibility_flag)


##################################################
## Macro: Check if GCC C++0x flag is available
##################################################
macro(cmaketools_check_cxx_cpp0x_flag var)
	set(SAFE_CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}")
	set(CMAKE_REQUIRED_DEFINITIONS "-std=c++0x")
	set(CODE "void testfunc(void *pointer){} int main() {testfunc(nullptr);return 0;}")
	check_cxx_source_compiles("${CODE}" ${var})
	set(CMAKE_REQUIRED_DEFINITIONS "${SAFE_CMAKE_REQUIRED_DEFINITIONS}")
endmacro(cmaketools_check_cxx_cpp0x_flag)


##################################################
## Check GCC compatibilities
##################################################

# Check GCC visibility and C++0x flag
if(CMAKE_COMPILER_IS_GNUCXX)
	# Check GCC visibility flag
	cmaketools_check_cxx_visibility_flag(CMAKETOOLS_GCC_VISIBILITY_FLAG)
	if(CMAKETOOLS_GCC_VISIBILITY_FLAG)
		ADD_DEFINITIONS(-fvisibility=hidden -fvisibility-inlines-hidden -DHAVE_VISIBILITY_ATTR)
		message(STATUS "GCC has visibility flag")
	endif()

	# Check GCC C++0x flag
	cmaketools_check_cxx_cpp0x_flag(CMAKETOOLS_GCC_CPP0X_FLAG)
	if(CMAKETOOLS_GCC_CPP0X_FLAG)
		ADD_DEFINITIONS(-std=c++0x)
		message(STATUS "GCC has C++0x flag")
	endif()
endif(CMAKE_COMPILER_IS_GNUCXX)