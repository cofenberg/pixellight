##################################################
## Project
##################################################
define_project(PLRendererD3D9)

##################################################
## Source files
##################################################
add_sources(
	src/PLRendererD3D9.cpp
	src/Renderer.cpp
	src/FixedFunctions.cpp
	src/VertexBuffer.cpp
	src/IndexBuffer.cpp
	src/TextureBuffer1D.cpp
	src/TextureBuffer2D.cpp
	src/TextureBufferRectangle.cpp
	src/TextureBuffer3D.cpp
	src/TextureBufferCube.cpp
	src/SurfaceWindow.cpp
	src/SurfaceTextureBuffer.cpp
	src/OcclusionQuery.cpp
	src/FontManager.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${VCInstallDir}/PlatformSDK/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${DIRECTX9_INCLUDE_DIRS}
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
	PLMath
	PLGraphics
	PLRenderer
	${WIN32_USER32_LIB}
	${DIRECTX9_LIBRARIES}
	${CG_DIRECTX9_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	${WIN32_COMPILE_DEFS}
	PLRENDERERD3D9_EXPORTS
)

##################################################
## Compiler flags
##################################################
add_compile_flags(
	${WIN32_COMPILE_FLAGS}
)

##################################################
## Linker flags
##################################################
add_linker_flags(
	${WIN32_LINKER_FLAGS}
)

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-DirectX9 External-Cg PLGeneral PLCore PLMath PLGraphics PLRenderer)
add_dependencies(Engine                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer"
)

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
	if(WIN32)
		add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Plugins/PLRenderer/cgD3D9.dll "${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/"
		)
	endif()
#endif()

##################################################
## Install
##################################################

# [TODO] Not within the official SDK because it's currenly just a proof-of-concept

# Library
#install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
#	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
#	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
#	ARCHIVE DESTINATION ${PL_INSTALL_LIB}							COMPONENT SDK
#)

# Include files
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
#	DESTINATION ${PL_INSTALL_INCLUDE} 								COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
#)

# Plugin file
#install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/${CMAKETOOLS_CURRENT_PLUGIN}
#	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer			COMPONENT Runtime
#)

# External dependencies, but only when not using system-libs
# [TODO] Uncomment this as soon as there's support for system-libs
#if(NOT CMAKETOOLS_USE_SYSTEM_LIBS)
#	if(WIN32)
#		install(FILES ${PL_BIN_DIR}/PLRuntime/Plugins/PLRenderer/cgD3D9.dll
#			DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLRenderer	COMPONENT Runtime
#		)
#	endif()
#endif()
