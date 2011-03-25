##################################################
## Project
##################################################
define_project(PLRendererOpenGLCg)

##################################################
## Source files
##################################################
add_sources(
	src/PLRendererOpenGLCg.cpp
	src/ShaderLanguageCg.cpp
	src/VertexShaderCg.cpp
	src/GeometryShaderCg.cpp
	src/FragmentShaderCg.cpp
	src/ProgramCg.cpp
	src/ProgramAttributeCg.cpp
	src/ProgramUniformCg.cpp
	src/ShaderToolsCg.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRendererOpenGL/include
	${CG_INCLUDE_DIRS}
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
	PLGraphics
	PLMath
	PLRenderer
	PLRendererOpenGL
	${CG_OPENGL_LIBRARIES}
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_OPENGL32_LIB}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_libs(
		GL
	)
endif()

##################################################
## Preprocessor definitions
##################################################
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Cg PLGeneral PLCore PLMath PLGraphics PLRenderer PLRendererOpenGL)
add_dependencies(Engine                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLRenderer/cg.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLRenderer/cgGL.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/"
		)
	elseif(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/Cg/lib/libCg.so   "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/Cg/lib/libCgGL.so "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/"
		)
	endif()
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 								COMPONENT SDK		PATTERN ".svn" EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer			COMPONENT Runtime
)

# External dependencies, but only when not using system-libs
if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/cg.dll
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/cgGL.dll
			DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
		)
	elseif(LINUX)
		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/libCg.so
					  ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/libCgGL.so
			DESTINATION ${PL_INSTALL_SHARED}						COMPONENT Runtime
		)
	endif()
endif()

