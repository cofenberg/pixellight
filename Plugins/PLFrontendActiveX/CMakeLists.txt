##################################################
## Project
##################################################
define_project(PLFrontendActiveX)

##################################################
## Prerequisites
##################################################
# Copy register.bat and unregister.bat
copy_files("${CMAKE_SOURCE_DIR}/Bin/BrowserPlugins/*.bat" "${PL_BIN_DIR}/BrowserPlugins")

##################################################
## Source files
##################################################
add_sources(
	src/dllmain.cpp
	src/PLFrontendActiveX.cpp
	src/PixelLightCtrl.cpp
	src/stdafx.cpp
	resource/PLFrontendActiveX.rc
	${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.c
	${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.h
)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.c PROPERTIES GENERATED TRUE)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/PLFrontendActiveX_i.h PROPERTIES GENERATED TRUE)

##################################################
## Include directories
##################################################
add_include_directories(
	src
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_CURRENT_BINARY_DIR}
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
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	${WIN32_COMPILE_DEFS}
	_ATL_DLL
)

##################################################
## Compiler flags
##################################################
add_compile_flags(
	${WIN32_COMPILE_FLAGS}
)
remove_compile_flags(
	/TP
)

##################################################
## Linker flags
##################################################
add_linker_flags(
	${WIN32_LINKER_FLAGS}
	/DEF:${CMAKE_CURRENT_SOURCE_DIR}/PLFrontendActiveX.def	# Use export definitions file
	/DYNAMICBASE
)

##################################################
## Build
##################################################
add_activex_interface(${CMAKETOOLS_CURRENT_TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/src/PLFrontendActiveX.idl
  OPTIONS /char signed /env win32 /Oicf /error stub_data
)
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/Runtime/Plugins/PLFrontend)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/BrowserPlugins"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/BrowserPlugins"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/BrowserPlugins"
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_BROWSER}				COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_BROWSER}				COMPONENT Runtime
)

# Plugin file
install(FILES ${PL_BIN_DIR}/Runtime/Plugins/PLFrontend/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLFrontend	COMPONENT Runtime
)

# register.bat and unregister.bat
install(FILES ${PL_BIN_DIR}/BrowserPlugins/register.bat
			  ${PL_BIN_DIR}/BrowserPlugins/unregister.bat
	DESTINATION ${PL_INSTALL_BROWSER}						COMPONENT Runtime
)
