#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
## Project
##################################################
define_project(PLlibRocket)

##################################################
## Source files
##################################################
add_sources(
	src/PLlibRocket.cpp
	src/libRocketAdapter.cpp
	src/RenderInterfacePL.cpp
	src/RenderInterfacePLShaders.cpp
	src/SystemInterfacePL.cpp
	src/FileInterfacePL.cpp
	src/SRPlibRocket.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	include/PLlibRocket
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${LIBROCKET_INCLUDE_DIRS}
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_LIB_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLCore
	PLMath
	PLGraphics
	PLRenderer
	PLMesh
	PLScene
	${LIBROCKET_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLLIBROCKET_EXPORTS
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_compile_defs(
		${LINUX_COMPILE_DEFS}
	)
endif()

##################################################
## Compiler flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_compile_flags(
		${WIN32_COMPILE_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_compile_flags(
		${LINUX_COMPILE_FLAGS}
	)
endif()

##################################################
## Linker flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_linker_flags(
		${WIN32_LINKER_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_linker_flags(
		${LINUX_LINKER_FLAGS}
	)
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-libRocket PLCore PLMath PLGraphics PLRenderer PLMesh PLScene)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)
if(WIN32)
	# Copy the libRocket dlls so that the user can use everything "out of the box"
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../bin/RocketCore.dll ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../bin/RocketControls.dll ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../bin/RocketDebugger.dll ${PL_RUNTIME_BIN_DIR}
	)
endif()

# Create relative symbolic links?
if(LINUX AND CMAKETOOLS_DETAILED_VERSION_INFORMATION)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} ${PL_LIB_DIR}
	)
endif()

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/RocketCore.dll ${PL_RUNTIME_BIN_DIR}
			COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/RocketControls.dll ${PL_RUNTIME_BIN_DIR}
			COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/RocketDebugger.dll ${PL_RUNTIME_BIN_DIR}
		)
	endif()
	if(LINUX)
		# Set COPY_SOURCE to files which should be copied (this variable is used by the "copy.cmake"-script)
		set(COPY_SOURCE ${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketCore.so
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketCore.so.1
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketCore.so.1.2.1
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketControls.so
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketControls.so.1
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketControls.so.1.2.1
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketDebugger.so
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketDebugger.so.1
						${LIBROCKET_INCLUDE_DIRS}/../lib/libRocketDebugger.so.1.2.1)

		# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied into (this variable is used by the "copy.cmake"-script)
		set(COPY_DEST ${PL_RUNTIME_BIN_DIR})

		# Create the "copy_to_runtime.cmake"-file in the build directory of the current target (the configure file replaces the variable references with the value of the variable)
		configure_file("${CMAKETOOLS_DIR}/Scripts/copy.cmake" ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/copy_to_runtime.cmake)

		# Add custom command to call the created "copy_to_runtime.cmake"-file after the target was built
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET} COMMAND ${CMAKE_COMMAND} -P "copy_to_runtime.cmake")
	endif()
#endif()

# Copy the libRocket libraries so that the user can use everything "out of the box"
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../lib/RocketCore.lib ${PL_LIB_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../lib/RocketControls.lib ${PL_LIB_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBROCKET_INCLUDE_DIRS}/../lib/RocketDebugger.lib ${PL_LIB_DIR}
	)
endif()
if(LINUX)
	# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied into (this variable is used by the "copy.cmake"-script)
	set(COPY_DEST ${PL_LIB_DIR})

	# Create the "copy_to_lib.cmake"-file in the build directory of the current target (the configure file replaces the variable references with the value of the variable)
	configure_file("${CMAKETOOLS_DIR}/Scripts/copy.cmake" ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/copy_to_lib.cmake)

	# Add custom command to call the created "copy_to_runtime.cmake"-file after target was built
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET} COMMAND ${CMAKE_COMMAND} -P "copy_to_lib.cmake")
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 				COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Copy the libRocket stuff into the SDK so that the user can use everything "out of the box"
install(DIRECTORY ${LIBROCKET_INCLUDE_DIRS}/Rocket
	DESTINATION ${PL_INSTALL_INCLUDE} 				COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
if(WIN32)
	install(FILES	${PL_RUNTIME_BIN_DIR}/RocketCore.dll
					${PL_RUNTIME_BIN_DIR}/RocketControls.dll
					${PL_RUNTIME_BIN_DIR}/RocketDebugger.dll
		DESTINATION ${PL_INSTALL_RUNTIME_BIN}		COMPONENT SDK
	)
	install(FILES	${PL_LIB_DIR}/RocketCore.lib
					${PL_LIB_DIR}/RocketControls.lib
					${PL_LIB_DIR}/RocketDebugger.lib
		DESTINATION ${PL_INSTALL_LIB}				COMPONENT SDK
	)
endif()
if(LINUX)
	install(FILES	${PL_RUNTIME_BIN_DIR}/libRocketCore.so
					${PL_RUNTIME_BIN_DIR}/libRocketCore.so.1
					${PL_RUNTIME_BIN_DIR}/libRocketCore.so.1.2.1
					${PL_RUNTIME_BIN_DIR}/libRocketControls.so
					${PL_RUNTIME_BIN_DIR}/libRocketControls.so.1
					${PL_RUNTIME_BIN_DIR}/libRocketControls.so.1.2.1
					${PL_RUNTIME_BIN_DIR}/libRocketDebugger.so
					${PL_RUNTIME_BIN_DIR}/libRocketDebugger.so.1
					${PL_RUNTIME_BIN_DIR}/libRocketDebugger.so.1.2.1
		DESTINATION ${PL_INSTALL_RUNTIME_BIN}		COMPONENT SDK
	)
endif()
