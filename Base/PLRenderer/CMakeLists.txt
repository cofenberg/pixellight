#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
define_project(PLRenderer)

##################################################
## Source files
##################################################
add_sources(
	src/PLRenderer.cpp
	src/RendererContext.cpp
	src/SPDefault.cpp
	src/SPPreview.cpp
	src/Renderer/Renderer.cpp
	src/Renderer/FixedFunctions.cpp
	src/Renderer/FixedFunctionsRenderStates.cpp
	src/Renderer/FixedFunctionsTextureStageStates.cpp
	src/Renderer/DrawHelpers.cpp
	src/Renderer/Parameters.cpp
	src/Renderer/RenderStates.cpp
	src/Renderer/SamplerStates.cpp
	src/Renderer/Resource.cpp
	src/Renderer/ResourceHandler.cpp
	src/Renderer/Buffer.cpp
	src/Renderer/VertexBuffer.cpp
	src/Renderer/IndexBuffer.cpp
	src/Renderer/UniformBuffer.cpp
	src/Renderer/TextureBuffer.cpp
	src/Renderer/TextureBuffer1D.cpp
	src/Renderer/TextureBuffer2D.cpp
	src/Renderer/TextureBuffer2DArray.cpp
	src/Renderer/TextureBufferRectangle.cpp
	src/Renderer/TextureBuffer3D.cpp
	src/Renderer/TextureBufferCube.cpp
	src/Renderer/Surface.cpp
	src/Renderer/SurfaceHandler.cpp
	src/Renderer/SurfaceWindow.cpp
	src/Renderer/SurfaceWindowHandler.cpp
	src/Renderer/SurfaceTextureBuffer.cpp
	src/Renderer/SurfacePainter.cpp
	src/Renderer/OcclusionQuery.cpp
	src/Renderer/ShaderLanguage.cpp
	src/Renderer/Shader.cpp
	src/Renderer/VertexShader.cpp
	src/Renderer/TessellationControlShader.cpp
	src/Renderer/TessellationEvaluationShader.cpp
	src/Renderer/GeometryShader.cpp
	src/Renderer/FragmentShader.cpp
	src/Renderer/Program.cpp
	src/Renderer/ProgramGenerator.cpp
	src/Renderer/ProgramAttribute.cpp
	src/Renderer/ProgramUniform.cpp
	src/Renderer/ProgramUniformBlock.cpp
	src/Renderer/Font.cpp
	src/Renderer/FontTexture.cpp
	src/Renderer/FontManager.cpp
	src/Renderer/FontGlyph.cpp
	src/Renderer/FontGlyphTexture.cpp
	src/Renderer/Backend/RendererBackend.cpp
	src/Renderer/Backend/FontManagerBackend.cpp
	src/Renderer/Backend/DrawHelpersBackend.cpp
	src/Renderer/Backend/DrawHelpersBackendShaders.cpp
	src/Renderer/Backend/DrawHelpersBackendFixedFunctions.cpp
	src/Texture/Creator/TextureCreatorHorizonMap3D.cpp
	src/Texture/Creator/TextureCreatorBlank2D.cpp
	src/Texture/Creator/TextureCreatorTurbulence3D.cpp
	src/Texture/Creator/TextureCreatorASCII3D.cpp
	src/Texture/Creator/TextureCreator.cpp
	src/Texture/Creator/TextureCreatorNormalizationCubeMap.cpp
	src/Texture/Creator/TextureCreatorAngleCubeMap.cpp
	src/Texture/Creator/TextureCreatorRandom2D.cpp
	src/Texture/Creator/TextureCreatorSpot2D.cpp
	src/Texture/TextureAniLoaderPL.cpp
	src/Texture/TextureAniLoader.cpp
	src/Texture/SPTexturePreview.cpp
	src/Texture/TextureHandler.cpp
	src/Texture/AniInfoManager.cpp
	src/Texture/Texture.cpp
	src/Texture/AniInfoHandler.cpp
	src/Texture/TextureAni.cpp
	src/Texture/AniInfo.cpp
	src/Texture/TextureManager.cpp
	src/Effect/EffectLoaderPL.cpp
	src/Effect/EffectLoader.cpp
	src/Effect/EffectPassLayer.cpp
	src/Effect/SPEffectPreview.cpp
	src/Effect/EffectPass.cpp
	src/Effect/EffectManager.cpp
	src/Effect/EffectHandler.cpp
	src/Effect/EffectTechnique.cpp
	src/Effect/Effect.cpp
	src/Material/MaterialLoaderPL.cpp
	src/Material/MaterialLoader.cpp
	src/Material/Parameter.cpp
	src/Material/Material.cpp
	src/Material/SPMaterialPreview.cpp
	src/Material/MaterialManager.cpp
	src/Material/ParameterManager.cpp
	src/Material/MaterialHandler.cpp
	src/Animation/Animation.cpp
	src/Animation/AnimationBase.cpp
	src/Animation/AnimationEvent.cpp
	src/Animation/AnimationHandler.cpp
	src/Animation/AnimationInfo.cpp
	src/Animation/AnimationManager.cpp
	src/Application/RendererApplication.cpp
	src/Application/Config.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
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
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLRENDERER_EXPORTS
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics)
add_dependencies(Base							${CMAKETOOLS_CURRENT_TARGET})

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
