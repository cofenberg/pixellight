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
set(CMAKETOOLS_MINIMAL	 1)
