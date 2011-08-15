##################################################
## Project
##################################################
define_project(PLRendererOpenGLES)

##################################################
## Source files
##################################################
add_sources(
	src/IndexBuffer.cpp
	src/PLRendererOpenGLES.cpp
	src/Renderer.cpp
	src/SurfaceTextureBuffer.cpp
	src/SurfaceWindow.cpp
	src/TextureBuffer2D.cpp
	src/TextureBuffer3D.cpp
	src/TextureBufferCube.cpp
	src/VertexBuffer.cpp
	src/ShaderLanguageGLSL.cpp
	src/VertexShaderGLSL.cpp
	src/FragmentShaderGLSL.cpp
	src/ProgramGLSL.cpp
	src/ProgramAttributeGLSL.cpp
	src/ProgramUniformGLSL.cpp
	src/ShaderToolsGLSL.cpp
	src/FontManager.cpp
	src/FontTexture.cpp
	src/FontGlyphTexture.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${OPENGLES_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
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
	PLGraphics
	PLMath
	PLRenderer
	${OPENGLES_LIBRARIES}
	${FREETYPE_LIBRARIES}
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_GDI32_LIB}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_libs(
#		EGL
#		GLESv2
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLRENDEREROPENGLES_EXPORTS
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
		GLX_GLXEXT_PROTOTYPES
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/Runtime/Plugins/PLRenderer)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-OpenGLES External-freetype PLCore PLMath PLGraphics PLRenderer)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Runtime/Plugins/PLRenderer"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime/Plugins/PLRenderer"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime/Plugins/PLRenderer"
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
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/Plugins/PLRenderer/libEGL.dll	"${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/Runtime/Plugins/PLRenderer/libGLESv2.dll	"${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/"
		)
	elseif(LINUX)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenGLES/lib/libEGL.so   "${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/"
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenGLES/lib/libGLESv2.so "${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/"
		)
	endif()
#endif()

##################################################
## Install
##################################################

if(LINUX)
	# Library
	install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
		RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
		LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
		ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
	)

	# Include files
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
		DESTINATION ${PL_INSTALL_INCLUDE} 								COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
	)

	# Plugin file
	install(FILES ${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/${CMAKETOOLS_CURRENT_PLUGIN}
		DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer			COMPONENT Runtime
	)
endif()

# External dependencies, but only when not using system-libs
# Due to legal issues, OpenGL ES 2.0 Emulator from ARM is not allowed to be included in the public PixelLight SDK
# [TODO] However, the cmake projects are not only there to create SDKs! So find a solution for this...
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
#	if(WIN32)
#		install(FILES ${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/libEGL.dll
#					  ${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/libGLESv2.dll
#			DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer		COMPONENT Runtime
#		)
#	elseif(LINUX)
#		install(FILES ${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/libEGL.so
#					  ${PL_BIN_DIR}/Runtime/Plugins/PLRenderer/libGLESv2.so
#			DESTINATION ${PL_INSTALL_SHARED}		COMPONENT Runtime
#		)
#	endif()
#endif()
