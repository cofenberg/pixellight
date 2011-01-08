##################################################
## Project
##################################################
define_project(PLImageLoaderEXR)

##################################################
## Source files
##################################################
add_sources(
	src/PLImageLoaderEXR.cpp
	src/ImageLoaderEXR.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${OPENEXR_INCLUDE_DIRS}
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
	PLMath
	PLGraphics
	${OPENEXR_LIBRARIES}
)


##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLIMAGELOADEREXR_EXPORTS
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
		PLATFORM_WINDOWS
		PLATFORM_WIN32
		HAVE_IOS_BASE
		HAVE_STL_LIMITS
		NOMINMAX
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
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLGraphics)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-OpenEXR PLGeneral PLCore PLMath PLGraphics)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLGraphics"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLGraphics"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLGraphics"
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLGraphics	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLGraphics	COMPONENT Runtime
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLGraphics/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLGraphics				COMPONENT Runtime
)
