#*********************************************************#
#*  File: Toolchain-sample.cmake                         *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
## Toolchain sample
##################################################

# Toolchain name
set(CMAKETOOLS_TOOLCHAIN om)															# Set this to a simple name that you want to pass to maketool --toolchain <name>

# Target system
set(CMAKE_SYSTEM_NAME Linux)															# Name of target system
set(CMAKE_SYSTEM_VERSION 1)																# Version of target system (not so important)

# Toolchain
set(CMAKE_C_COMPILER     /usr/local/bin/cross/armv4t/bin/arm-cross-linux-gnueabi-gcc)	# Path to cross-compiler gcc
set(CMAKE_CXX_COMPILER   /usr/local/bin/cross/armv4t/bin/arm-cross-linux-gnueabi-g++)	# Path to cross-compiler g++
set(CMAKE_FIND_ROOT_PATH /usr/local/bin/cross/armv4t/root)								# Path to cross-compiled root system

# Configure parameters
set(CONFIGURE_PATH 		/usr/local/bin/cross/armv4t/bin)								# Path   for cross-compiling using configure
set(CONFIGURE_PREFIX 	/usr/local/bin/cross/armv4t/root)								# Prefix for cross-compiling using configure
set(CONFIGURE_HOST   	armv4t-cross-linux-gnueabi)										# Host   for cross-compiling using configure

# Don't use inline-assembler
set(CMAKETOOLS_CONFIG_NO_INLINE_ASM 1)													# Disable any inline assembler code as this is most probably incompatible with the target system

# Options 
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)											# Don't use any programs  from the host system
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)												# Don't use any libraries from the host system
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)												# Don't use any include   from the host system

# Remove this!
# Please set all of the variables above to values according to the toolchain you want to use and then delete this line
message(FATAL_ERROR "Please copy Toolchain-sample.cmake to a new file, configure your toolchain and remove the last line")
