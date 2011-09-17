#*********************************************************#
#*  File: LinuxGCC.cmake                                 *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
## Linux/GCC platform definitions
##
## This file contains compiler and linker settings which are specific to the GCC compiler suit under Linux
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

# Check gcc compiler
include(${CMAKETOOLS_DIR}/Modules/CheckGCC.cmake)	# Adds e.g. visibility attribute (http://gcc.gnu.org/wiki/Visibility)

# Preprocessor definitions
set(LINUX_COMPILE_DEFS
	${LINUX_COMPILE_DEFS}
	GCC									# We are using the gcc/g++ compiler
)


##################################################
## Compiler flags
##################################################

set(LINUX_COMPILE_FLAGS
	${LINUX_COMPILE_FLAGS}
	-mtune=generic						# Produce code optimized for the most common IA32/AMD64/EM64T processors
	-msse3								# Use SSE3 instruction set / code might not run on CPUs with no sse3 instruction
	-Wstrict-null-sentinel				# Warn also about the use of an uncasted NULL as sentinel
)

if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
	set(LINUX_COMPILE_FLAGS
		${LINUX_COMPILE_FLAGS}
	#	-O3								# Very aggressive transformations, long compile times, but usally best runtime performance! (but also dramatically increased binary size, e.g. "libPLScene,so" is 4.5 MB when using -O3)
		-O2								# Balance speed and binary size (e.g. "libPLScene,so" is 2.8 MB)
	#	-Os								# Optimize for binary size (e.g. "libPLScene,so" is 2.1 MB when using -Os)
		-funroll-all-loops				# Perform the optimization of loop unrolling
		-fpeel-loops					# Peels the loops for that there is enough information that they do not roll much (from profile feedback)
		-ftree-vectorize				# Enable the vectorizer
		# The following flag usage is basing on information from http://software.intel.com/en-us/forums/showthread.php?t=66902
		--param max-unroll-times=4
		# The following flag usage is basing on information from http://developer.amd.com/documentation/articles/pages/Compiler-FlagDrivenPerformanceGains.aspx
		-fomit-frame-pointer			# Don't keep the frame pointer in a register for functions that don't need one
	)
endif()
