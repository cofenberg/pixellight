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
#*********************************************************/


##################################################
## Project
##################################################
define_project(PLVolumeRenderer)

##################################################
## Source files
##################################################
add_sources(
	src/PLVolumeRenderer.cpp
	src/ShaderComposition.cpp
	src/ShaderCompositionID.cpp
	src/ShaderCompositor.cpp
	src/ShaderCompositorNull.cpp
	src/ShaderCompositorPC.cpp
	src/ShaderFunction.cpp
	src/SRPVolume.cpp
	#[-------------------------------------------------------]
	#[ 1.0 - Ray Setup                                       ]
	#[-------------------------------------------------------]
	src/RaySetup/ShaderFunctionRaySetup.cpp
	src/RaySetup/ShaderFunctionRaySetupNull.cpp
	src/RaySetup/ShaderFunctionRaySetupColorCube.cpp
	src/RaySetup/ShaderFunctionRaySetupBoundingBoxIntersection.cpp
	src/RaySetup/ShaderFunctionRaySetupHybrid.cpp
	#[-------------------------------------------------------]
	#[ 1.1 - Clip Ray                                        ]
	#[-------------------------------------------------------]
	src/ClipRay/ShaderFunctionClipRay.cpp
	src/ClipRay/ShaderFunctionClipRayNull.cpp
	src/ClipRay/ShaderFunctionClipRayTemplate.cpp
	src/ClipRay/ShaderFunctionClipRayPlane.cpp
	src/ClipRay/ShaderFunctionClipRayDepthTexture.cpp
	#[-------------------------------------------------------]
	#[ 1.2 - Jitter Position                                 ]
	#[-------------------------------------------------------]
	src/JitterPosition/ShaderFunctionJitterPosition.cpp
	src/JitterPosition/ShaderFunctionJitterPositionNull.cpp
	src/JitterPosition/ShaderFunctionJitterPositionStochastic.cpp
	src/JitterPosition/ShaderFunctionJitterPositionTrigonometric.cpp
	#[-------------------------------------------------------]
	#[ 2.0 - Ray Traversal                                   ]
	#[-------------------------------------------------------]
	src/RayTraversal/ShaderFunctionRayTraversal.cpp
	src/RayTraversal/ShaderFunctionRayTraversalNull.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDebug.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDebugRayStart.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDebugRayEnd.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDebugRayDirection.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDebugRayLength.cpp
	src/RayTraversal/ShaderFunctionRayTraversalIsosurface.cpp
	src/RayTraversal/ShaderFunctionRayTraversalMIP.cpp
	src/RayTraversal/ShaderFunctionRayTraversalGMIP.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDVRBackToFront.cpp
	src/RayTraversal/ShaderFunctionRayTraversalDVRFrontToBack.cpp
	src/RayTraversal/ShaderFunctionRayTraversalMIDA.cpp
	#[-------------------------------------------------------]
	#[ 2.1 - Clip Position                                   ]
	#[-------------------------------------------------------]
	src/ClipPosition/ShaderFunctionClipPosition.cpp
	src/ClipPosition/ShaderFunctionClipPositionNull.cpp
	src/ClipPosition/ShaderFunctionClipPositionTemplate.cpp
	src/ClipPosition/ShaderFunctionClipPositionBox.cpp
	src/ClipPosition/ShaderFunctionClipPositionEllipsoid.cpp
	src/ClipPosition/ShaderFunctionClipPositionVolumeTexture.cpp
	#[-------------------------------------------------------]
	#[ 2.2 - Reconstruction                                  ]
	#[-------------------------------------------------------]
	src/Reconstruction/ShaderFunctionReconstruction.cpp
	src/Reconstruction/ShaderFunctionReconstructionNull.cpp
	src/Reconstruction/ShaderFunctionReconstructionTriCubic.cpp
	src/Reconstruction/ShaderFunctionReconstructionTriCubicKernel.cpp
	#[-------------------------------------------------------]
	#[ 2.2 - Fetch Scalar                                    ]
	#[-------------------------------------------------------]
	src/FetchScalar/ShaderFunctionFetchScalar.cpp
	src/FetchScalar/ShaderFunctionFetchScalarNull.cpp
	src/FetchScalar/ShaderFunctionFetchScalarSampler2D.cpp
	src/FetchScalar/ShaderFunctionFetchScalarSampler2DArray.cpp
	src/FetchScalar/ShaderFunctionFetchScalarSampler3D.cpp
	#[-------------------------------------------------------]
	#[ 2.3 - Shading                                         ]
	#[-------------------------------------------------------]
	src/Shading/ShaderFunctionShading.cpp
	src/Shading/ShaderFunctionShadingNull.cpp
	src/Shading/ShaderFunctionShadingDebug.cpp
	src/Shading/ShaderFunctionShadingDebugScalar.cpp
	src/Shading/ShaderFunctionShadingDebugPosition.cpp
	src/Shading/ShaderFunctionShadingDebugClassification.cpp
	src/Shading/ShaderFunctionShadingDebugGradient.cpp
	src/Shading/ShaderFunctionShadingDebugNormal.cpp
	src/Shading/ShaderFunctionShadingDebugViewingDirection.cpp
	src/Shading/ShaderFunctionShadingDebugLightDirection.cpp
	src/Shading/ShaderFunctionShadingLighting.cpp
	src/Shading/ShaderFunctionShadingLightingThreshold.cpp
	#[-------------------------------------------------------]
	#[ 2.4 - Classification                                  ]
	#[-------------------------------------------------------]
	src/Classification/ShaderFunctionClassification.cpp
	src/Classification/ShaderFunctionClassificationNull.cpp
	src/Classification/ShaderFunctionClassificationThreshold.cpp
	src/Classification/ShaderFunctionClassificationTransferFunction.cpp
	src/Classification/ShaderFunctionClassificationTransferFunctionPreMultiplied.cpp
	src/Classification/ShaderFunctionClassificationPreIntegration.cpp
	#[-------------------------------------------------------]
	#[ 2.5 - Gradient                                        ]
	#[-------------------------------------------------------]
	src/Gradient/ShaderFunctionGradient.cpp
	src/Gradient/ShaderFunctionGradientNull.cpp
	src/Gradient/ShaderFunctionGradientForwardDifferences.cpp
	src/Gradient/ShaderFunctionGradientBackwardDifferences.cpp
	src/Gradient/ShaderFunctionGradientCentralDifferences.cpp
	src/Gradient/ShaderFunctionGradientCentralDifferences9.cpp
	#[-------------------------------------------------------]
	#[ 2.5 - Gradient Input                                  ]
	#[-------------------------------------------------------]
	src/GradientInput/ShaderFunctionGradientInput.cpp
	src/GradientInput/ShaderFunctionGradientInputNull.cpp
	src/GradientInput/ShaderFunctionGradientInputScalar.cpp
	src/GradientInput/ShaderFunctionGradientInputClassified.cpp
	#[-------------------------------------------------------]
	#[ 2.6 - Illumination                                    ]
	#[-------------------------------------------------------]
	src/Illumination/ShaderFunctionIllumination.cpp
	src/Illumination/ShaderFunctionIlluminationNull.cpp
	src/Illumination/ShaderFunctionIlluminationBlinnPhong.cpp
	src/Illumination/ShaderFunctionIlluminationCookTorrance.cpp
	src/Illumination/ShaderFunctionIlluminationLambertianReflection.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
	${CMAKE_SOURCE_DIR}/Base/PLScene/include
	${CMAKE_SOURCE_DIR}/Plugins/PLCompositing/include
	${CMAKE_SOURCE_DIR}/Plugins/PLVolume/include
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
	PLMath
	PLGraphics
	PLRenderer
	PLMesh
	PLScene
	PLCompositing
	PLVolume
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLVOLUMERENDERER_EXPORTS
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

if(LINUX OR APPLE)
	if(GCC_VERSION VERSION_LESS "4.5" OR Clang_VERSION VERSION_LESS "3.1")
		add_compile_defs(
			NO_LAMDA_EXPRESSION_SUPPORT
		)
	endif()
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
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer PLMesh PLScene PLCompositing PLVolume)
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
