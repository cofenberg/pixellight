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
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLDatabase/include
	${SQLITE_INCLUDE_DIRS}
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_BIN_DIR}/Lib
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLGeneral
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
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-SQLite PLGeneral PLCore PLDatabase)
add_dependencies(Base                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/SQLite/lib/libsqlite.so   "${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase/"
		)
	endif()
#endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLDatabase	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLDatabase	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 								COMPONENT SDK		PATTERN ".svn" EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLDatabase			COMPONENT Runtime
)

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(LINUX)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLDatabase/libsqlite.so
			DESTINATION ${PL_INSTALL_SHARED}						COMPONENT Runtime
		)
	endif()
#endif()
