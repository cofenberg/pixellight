#*********************************************************#
#*  File: Toolchain-om.cmake                             *
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
