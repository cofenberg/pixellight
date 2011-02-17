##################################################
## Project
##################################################
define_project(PLScene)

##################################################
## Prerequisites
##################################################

# Create 'Plugins/PLScene' directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/PLRuntime/Plugins/PLScene)

##################################################
## Source files
##################################################
add_sources(
	src/Scene/SceneNodes/Console/SNConsoleBase.cpp
	src/Scene/SceneNodes/Console/ConsoleCommand.cpp
	src/Scene/SceneNodes/Console/SNConsole.cpp
	src/Scene/SceneNodes/Console/ConsoleDefaultCommands.cpp
	src/Scene/SceneNodes/Loader/SkinLoaderPL.cpp
	src/Scene/SceneNodes/Loader/SkyLoaderPL.cpp
	src/Scene/SceneNodes/Loader/SkinLoader.cpp
	src/Scene/SceneNodes/Loader/SkyLoader.cpp
	src/Scene/SceneNodes/Terrain/TerrainLoaderPL.cpp
	src/Scene/SceneNodes/Terrain/TerrainLoader.cpp
	src/Scene/SceneNodes/Terrain/GMMSurfaceLevel.cpp
	src/Scene/SceneNodes/Terrain/SNTerrain.cpp
	src/Scene/SceneNodes/Terrain/GMMSurfacePatch.cpp
	src/Scene/SceneNodes/Terrain/GMMSurface.cpp
	src/Scene/SceneNodes/Gui/SNGui.cpp
	src/Scene/SceneNodes/Gui/GraphicsPL.cpp
	src/Scene/SceneNodes/Gui/GuiPL.cpp
	src/Scene/SceneNodes/Gui/ImagePL.cpp
	src/Scene/SceneNodes/Gui/FontPL.cpp
	src/Scene/SceneNodes/Gui/WidgetPL.cpp
	src/Scene/SceneNodes/Gui/CursorPL.cpp
	src/Scene/SceneNodes/Gui/ClipBoardPL.cpp
	src/Scene/SceneNodes/SNLoadScreenBase.cpp
	src/Scene/SceneNodes/SNLoadScreenPL.cpp
	src/Scene/SceneNodes/SNLoadScreen.cpp
	src/Scene/SceneNodes/SNCoordinateAxis.cpp
	src/Scene/SceneNodes/SNLineGrid.cpp
	src/Scene/SceneNodes/SNString.cpp
	src/Scene/SceneNodes/SNEventArea.cpp
	src/Scene/SceneNodes/SNCoordinateAxisRotation.cpp
	src/Scene/SceneNodes/SNEngineInformation.cpp
	src/Scene/SceneNodes/SNText.cpp
	src/Scene/SceneNodes/SNText2D.cpp
	src/Scene/SceneNodes/SNText3D.cpp
	src/Scene/SceneNodes/SNKeyValue.cpp
	src/Scene/SceneNodes/SCRenderToTexture.cpp
	src/Scene/SceneNodes/SNHelper.cpp
	src/Scene/SceneNodes/SNUnknown.cpp
	src/Scene/SceneNodes/SCUnknown.cpp
	src/Scene/SceneNodes/SCMirror.cpp
	src/Scene/SceneNodes/SNLineBox.cpp
	src/Scene/SceneNodes/SNCoordinateAxis3D.cpp
	src/Scene/SceneNodes/SNSky.cpp
	src/Scene/SceneNodes/SNArea.cpp
	src/Scene/SceneNodes/SNBitmap.cpp
	src/Scene/SceneNodes/SNBitmap2D.cpp
	src/Scene/SceneNodes/SNBitmap3D.cpp
	src/Scene/SceneNodes/SNLine.cpp
	src/Scene/SceneNodes/SNPoint.cpp
	src/Scene/SceneNodes/SNMesh.cpp
	src/Scene/SceneNodeModifiers/SNMLookController.cpp
	src/Scene/SceneNodeModifiers/LookController.cpp
	src/Scene/SceneNodeModifiers/SNMMoveController.cpp
	src/Scene/SceneNodeModifiers/MoveController.cpp
	src/Scene/SceneNodeModifiers/SNMAnchor.cpp
	src/Scene/SceneNodeModifiers/SNMTransform.cpp
	src/Scene/SceneNodeModifiers/SNMPositionPath.cpp
	src/Scene/SceneNodeModifiers/SNMPositionMoveToTarget.cpp
	src/Scene/SceneNodeModifiers/SNMPositionLinearAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMPositionKeyframeAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMScaleKeyframeAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMRotationTarget.cpp
	src/Scene/SceneNodeModifiers/SNMRotationFixRoll.cpp
	src/Scene/SceneNodeModifiers/SNMRotationMoveDirection.cpp
	src/Scene/SceneNodeModifiers/SNMRotationLinearAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMRotationKeyframeAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMBillboard.cpp
	src/Scene/SceneNodeModifiers/SNMBillboardSpherical.cpp
	src/Scene/SceneNodeModifiers/SNMBillboardCylindrical.cpp
	src/Scene/SceneNodeModifiers/SNMMesh.cpp
	src/Scene/SceneNodeModifiers/SNMMeshMorph.cpp
	src/Scene/SceneNodeModifiers/SNMMeshJoint.cpp
	src/Scene/SceneNodeModifiers/SNMMeshUpdate.cpp
	src/Scene/SceneNodeModifiers/SNMMeshAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMMeshMorphBlink.cpp
	src/Scene/SceneNodeModifiers/SNMMeshMorphCameraNear.cpp
	src/Scene/SceneNodeModifiers/SNMDraw.cpp
	src/Scene/SceneNodeModifiers/SNMDrawRectangle.cpp
	src/Scene/SceneNodeModifiers/SNMKeyValue.cpp
	src/Scene/SceneNodeModifiers/SNMDeactivationOnTimeout.cpp
	src/Scene/SceneNodeModifiers/SNMOrbiting.cpp
	src/Scene/SceneNodeModifiers/SNMOrbitingController.cpp
	src/Scene/SceneNodeModifiers/OrbitingController.cpp
	src/Scene/SceneNodeModifiers/SNMUnknown.cpp
	src/Scene/SceneNodeModifiers/SNMCameraZoom.cpp
	src/Scene/SceneNodeModifiers/SNMCameraZoomController.cpp
	src/Scene/SceneNodeModifiers/CameraZoomController.cpp
	src/Scene/SceneNodeModifiers/SNMPositionRandomAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMScaleRandomAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMLightRandomAnimation.cpp
	src/Scene/SceneLoader/SceneLoader.cpp
	src/Scene/SceneLoader/SceneLoaderPL.cpp
	src/Scene/SceneQueries/SQAABoundingBox.cpp
	src/Scene/SceneQueries/SQPlaneSet.cpp
	src/Scene/SceneQueries/SQEnumerate.cpp
	src/Scene/SceneQueries/SQSphere.cpp
	src/Scene/SceneQueries/SQLine.cpp
	src/Scene/SceneQueries/SQPoint.cpp
	src/Scene/SceneQueries/SQByName.cpp
	src/Scene/SceneQueries/SQByClassName.cpp
	src/Scene/SceneHierarchies/SHList.cpp
	src/Scene/SceneHierarchies/SHKdTree.cpp
	src/Scene/SceneHierarchyNode.cpp
	src/Scene/SceneContainer.cpp
	src/Scene/SceneNodeHandler.cpp
	src/Scene/SNPortal.cpp
	src/Scene/SNCellPortal.cpp
	src/Scene/SNAntiPortal.cpp
	src/Scene/SNEffectLight.cpp
	src/Scene/SceneNode.cpp
	src/Scene/SCCell.cpp
	src/Scene/SNFog.cpp
	src/Scene/SPScene.cpp
	src/Scene/SNProjectiveSpotLight.cpp
	src/Scene/SNSpotLight.cpp
	src/Scene/SNProjectivePointLight.cpp
	src/Scene/SceneHierarchyNodeItem.cpp
	src/Scene/SceneQueryManager.cpp
	src/Scene/SNLight.cpp
	src/Scene/SceneContext.cpp
	src/Scene/SceneQueryHandler.cpp
	src/Scene/SNPointLight.cpp
	src/Scene/SceneNodeModifier.cpp
	src/Scene/SNSphereFog.cpp
	src/Scene/SNCamera.cpp
	src/Scene/SceneQuery.cpp
	src/Scene/SNDirectionalLight.cpp
	src/Scene/SceneHierarchy.cpp
	src/Visibility/SQCull.cpp
	src/Visibility/VisManager.cpp
	src/Visibility/VisNode.cpp
	src/Visibility/VisContainer.cpp
	src/Visibility/VisPortal.cpp
	src/Compositing/SceneRendererLoaderPL.cpp
	src/Compositing/SceneRendererLoader.cpp
	src/Compositing/SceneRenderer.cpp
	src/Compositing/SceneRendererHandler.cpp
	src/Compositing/SceneRendererManager.cpp
	src/Compositing/SceneRendererPass.cpp
	src/PLScene.cpp
	src/Config.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLGui/PLGui/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLInput/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLEngine/PLMesh/include
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
	PLGui
	PLInput
	PLRenderer
	PLMesh
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_ADVAPI32_LIB}
		${WIN32_WINMM_LIB}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLSCENE_EXPORTS
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

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLGeneral PLGraphics PLCore PLMath PLGui PLInput PLRenderer PLMesh)
add_dependencies(Engine                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}		COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		PATTERN ".svn" EXCLUDE
)
