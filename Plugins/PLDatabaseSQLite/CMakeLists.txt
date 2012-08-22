#*********************************************************#
#*  File: CMakeLists.txt                                 *
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
## Project
##################################################
define_project(PLDatabaseSQLite)

##################################################
## Source files
##################################################
add_sources(
	src/PLDatabaseSQLite.cpp
	src/Database.cpp
	src/DatabaseQuery.cpp
	src/DatabaseQueryResult.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLDatabase/include
	${SQLITE_INCLUDE_DIRS}
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
	PLDatabase
	${SQLITE_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLDATABASESQLITE_EXPORTS
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
    if(CMAKE_BUILD_TYPE MATCHES Debug)
		##################################################
		## Debug
		##################################################
		add_linker_flags(
			/NODEFAULTLIB:MSVCRTD					# Ignore libraries
		)
    elseif(CMAKE_BUILD_TYPE MATCHES Release)
		##################################################
		## Release
		##################################################
		add_linker_flags(
			/NODEFAULTLIB:MSVCRT					# Ignore libraries
		)
    endif()
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-SQLite PLCore PLDatabase)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)

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
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(LINUX)
		# Set COPY_SOURCE to files which should be copied (this variable is used by the "copy.cmake"-script)
		set(COPY_SOURCE ${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite3.so
						${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite3.so.0 
						${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite3.so.0.8.6 
		   )

		# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied into (this variable is used by the "copy.cmake"-script)
		set(COPY_DEST ${PL_RUNTIME_BIN_DIR})

		# Create the "copy_to_runtime.cmake"-file in the build directory of the current target (the configure file replaces the variable references with the value of the variable)
		configure_file("${CMAKETOOLS_DIR}/Scripts/copy.cmake" ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/copy_to_runtime.cmake)

		# Add custom command to call the created "copy_to_runtime.cmake"-file after the target was built
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET} COMMAND ${CMAKE_COMMAND} -P "copy_to_runtime.cmake")
	endif()
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

# Plugin file
install(FILES ${PL_RUNTIME_BIN_DIR}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_BIN}			COMPONENT Runtime
)

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(LINUX)
		# Copy shared libraries
		install(FILES	${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite3.so
						${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite3.so.0 
						${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite3.so.0.8.6
			DESTINATION ${PL_INSTALL_RUNTIME_BIN}		COMPONENT Runtime
		)
	endif()
endif()
