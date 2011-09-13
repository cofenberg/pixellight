##################################################
## Project
##################################################
define_project(PLRendererOpenGLES2)

##################################################
## Source files
##################################################
add_sources(
	src/Context.cpp
	src/ContextRuntimeLinking.cpp
	src/IndexBuffer.cpp
	src/PLRendererOpenGLES2.cpp
	src/Renderer.cpp
	src/FrameBufferObject.cpp
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
)
if(PL_PLUGIN_RENDERER_OPENGLES2_FONT)
	add_sources(
		src/FontManager.cpp
		src/FontTexture.cpp
		src/FontGlyphTexture.cpp
	)
endif()

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/External/Optional/OpenGLES2/include/
)
if(PL_PLUGIN_RENDERER_OPENGLES2_FONT)
	add_include_directories(
		${FREETYPE_INCLUDE_DIRS}
	)
endif()

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
)
if(PL_PLUGIN_RENDERER_OPENGLES2_FONT)
	add_libs(
		${FREETYPE_LIBRARIES}
	)
endif()
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_GDI32_LIB}
	)
elseif(ANDROID)
	##################################################
	## Android
	##################################################
	add_libs(
		android	# Required for "ANativeWindow_setBuffersGeometry()"
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_libs(
		${LINUX_X11_LIBS}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLRENDEREROPENGLES2_EXPORTS
)
if(NOT PL_PLUGIN_RENDERER_OPENGLES2_FONT)
	add_compile_defs(
		DISABLE_FONT_SUPPORT
	)
endif()
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}		PLCore PLMath PLGraphics PLRenderer)
if(NOT PL_MOBILE)
	# No need for OpenGL ES 2.0 emulator external dependencies when building for a mobile device
	add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-OpenGLES2)
endif()
if(PL_PLUGIN_RENDERER_OPENGLES2_FONT)
	add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-freetype)
endif()
add_dependencies(Plugins							${CMAKETOOLS_CURRENT_TARGET})

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

# No need for system libraries because we dynamically linking at runtime against the EGL and OpenGL ES 2.0 dynamic libraries, this in here is optional emulator only
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/libEGL.dll	${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${PL_RUNTIME_BIN_GITDIR}/libGLESv2.dll	${PL_RUNTIME_BIN_DIR}
	)
elseif(LINUX AND NOT ANDROID)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenGLES2/lib/libEGL.so		${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/OpenGLES2/lib/libGLESv2.so	${PL_RUNTIME_BIN_DIR}
	)
endif()

##################################################
## Install
##################################################

if(LINUX)
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
endif()

# External dependencies: Due to legal issues, OpenGL ES 2.0 Emulator from ARM is not allowed to be included in the public PixelLight SDK
#	if(WIN32)
#		install(FILES ${PL_RUNTIME_BIN_DIR}/libEGL.dll
#					  ${PL_RUNTIME_BIN_DIR}/libGLESv2.dll
#			DESTINATION ${PL_INSTALL_RUNTIME_BIN}		COMPONENT Runtime
#		)
#	elseif(LINUX)
#		install(FILES ${PL_RUNTIME_BIN_DIR}/libEGL.so
#					  ${PL_RUNTIME_BIN_DIR}/libGLESv2.so
#			DESTINATION ${PL_INSTALL_RUNTIME_BIN}		COMPONENT Runtime
#		)
#	endif()
