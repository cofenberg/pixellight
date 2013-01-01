#*********************************************************#
#*  File: Toolchain-om.cmake                             *
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


##################################################
## Toolchain for building with OpenMoko toolchain
##################################################

# Toolchain name
set(CMAKETOOLS_TOOLCHAIN om)

# Target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)

# Toolchain
set(CMAKE_C_COMPILER     /workspace/projekte/oe/build/fso/cross/armv4t/bin/arm-angstrom-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER   /workspace/projekte/oe/build/fso/cross/armv4t/bin/arm-angstrom-linux-gnueabi-g++)
set(CMAKE_FIND_ROOT_PATH /workspace/projekte/oe/build/fso/staging/armv4t-angstrom-linux-gnueabi)

# Configure parameters
set(CONFIGURE_PATH 		/workspace/projekte/oe/build/fso/cross/armv4t/bin)
set(CONFIGURE_PREFIX 	/workspace/projekte/oe/build/fso/staging)
set(CONFIGURE_HOST   	arm-angstrom-linux-gnueabi)

# Don't use inline-assembler
set(CMAKETOOLS_CONFIG_NO_INLINE_ASM 1)

# Options 
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Internal options
set(CMAKETOOLS_TARGET_ARCH	"arm")
set(PL_NATIVE_PLPROJECT		0)
set(CMAKETOOLS_MINIMAL		1)
set(PL_MOBILE				1)
