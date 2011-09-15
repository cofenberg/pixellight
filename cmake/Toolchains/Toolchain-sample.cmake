#*********************************************************#
#*  File: Toolchain-sample.cmake                         *
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
