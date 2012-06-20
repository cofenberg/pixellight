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


[TODO] Bring me into PixelLight form


cmake_minimum_required(VERSION 2.8.3)


##################################################
## Define the project
##################################################
set(CURRENT_TARGET_NAME PLVolumeRenderer)
project(${CURRENT_TARGET_NAME})


##################################################
## Find packages
##################################################
if(ANDROID)
	find_host_package(PixelLight)	# "find_package"-variant provided by "android.toolchain.cmake", required for PixelLight CMake variables like "PL_PLCORE_INCLUDE_DIR"
else()
	find_package(PixelLight REQUIRED)
endif()


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)				# The current source directory
include_directories(${PL_PLCORE_INCLUDE_DIR})							# PLCore headers
include_directories(${PL_PLMATH_INCLUDE_DIR})							# PLMath headers
include_directories(${PL_PLGRAPHICS_INCLUDE_DIR})						# PLGraphics headers
include_directories(${PL_PLRENDERER_INCLUDE_DIR})						# PLRenderer headers
include_directories(${PL_PLMESH_INCLUDE_DIR})							# PLMesh headers
include_directories(${PL_PLSCENE_INCLUDE_DIR})							# PLScene headers
include_directories(${PL_PLCOMPOSITING_INCLUDE_DIR})					# PLCompositing headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../PLVolume/include/)	# PLVolume


##################################################
## Source codes
##################################################
set(CURRENT_SRC
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
## Additional libraries
##################################################
add_libs(
	${PL_PLCORE_LIBRARY}
	${PL_PLMATH_LIBRARY}
	${PL_PLGRAPHICS_LIBRARY}
	${PL_PLRENDERER_LIBRARY}
	${PL_PLMESH_LIBRARY}
	${PL_PLSCENE_LIBRARY}
	${PL_PLCOMPOSITING_LIBRARY}
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
add_library(${CURRENT_TARGET_NAME} SHARED ${CURRENT_SRC})
target_link_libraries (${CURRENT_TARGET_NAME} ${libs})
set_project_properties(${CURRENT_TARGET_NAME})


##################################################
## Post-Build
##################################################
# Executable
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CURRENT_TARGET_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}"
)

# Plugin file
add_custom_command(TARGET ${CURRENT_TARGET_NAME}
	COMMAND "${PL_ROOT}/Bin/Tools/${PL_ARCHBITSIZE}/PLProject${CMAKE_EXECUTABLE_SUFFIX}" ${CMAKE_CURRENT_SOURCE_DIR} --output-path "${CMAKE_SOURCE_DIR}/Bin/${PL_ARCHBITSIZE}" --write-plugin
	WORKING_DIRECTORY ${dir}
)


##################################################
## Dependencies
##################################################
add_dependencies(${CURRENT_TARGET_NAME}	PLVolume)
