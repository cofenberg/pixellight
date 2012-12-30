#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the “Software”), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## Project
##################################################
define_project(PLRendererD3D11)

##################################################
## Source files
##################################################
add_sources(
	src/PLRendererD3D11.cpp
	src/Renderer.cpp
	src/IndexBuffer.cpp
	src/VertexBuffer.cpp
	src/TextureBuffer1D.cpp
	src/TextureBuffer2D.cpp
	src/TextureBufferRectangle.cpp
	src/TextureBuffer3D.cpp
	src/TextureBufferCube.cpp
	src/SurfaceWindow.cpp
	src/SurfaceTextureBuffer.cpp
	src/OcclusionQuery.cpp
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
	${WIN32_USER32_LIB}
	${DIRECTX11_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLRENDERERD3D11_EXPORTS
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-DirectX11 PLCore PLMath PLGraphics PLRenderer)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} ${PL_LIB_DIR}
	)
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
