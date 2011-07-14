##################################################
## Project
##################################################
define_project(SPARK_PL)

##################################################
## Source files
##################################################
add_sources(
	src/SPARK_PL.cpp
	src/Core/SPK_BufferHandler.cpp
	src/Core/SPK_DEF.cpp
	src/Core/SPK_Emitter.cpp
	src/Core/SPK_Factory.cpp
	src/Core/SPK_Group.cpp
	src/Core/SPK_Interpolator.cpp
	src/Core/SPK_Model.cpp
	src/Core/SPK_Modifier.cpp
	src/Core/SPK_Particle.cpp
	src/Core/SPK_Registerable.cpp
	src/Core/SPK_Renderer.cpp
	src/Core/SPK_System.cpp
	src/Core/SPK_Transformable.cpp
	src/Core/SPK_Vector3D.cpp
	src/Core/SPK_Zone.cpp
	src/Extensions/Emitters/SPK_NormalEmitter.cpp
	src/Extensions/Emitters/SPK_RandomEmitter.cpp
	src/Extensions/Emitters/SPK_SphericEmitter.cpp
	src/Extensions/Emitters/SPK_StraightEmitter.cpp
	src/Extensions/Modifiers/SPK_Collision.cpp
	src/Extensions/Modifiers/SPK_Destroyer.cpp
	src/Extensions/Modifiers/SPK_LinearForce.cpp
	src/Extensions/Modifiers/SPK_ModifierGroup.cpp
	src/Extensions/Modifiers/SPK_Obstacle.cpp
	src/Extensions/Modifiers/SPK_PointMass.cpp
	src/Extensions/Modifiers/SPK_Vortex.cpp
	src/Extensions/Zones/SPK_AABox.cpp
	src/Extensions/Zones/SPK_Line.cpp
	src/Extensions/Zones/SPK_Plane.cpp
	src/Extensions/Zones/SPK_Point.cpp
	src/Extensions/Zones/SPK_Ring.cpp
	src/Extensions/Zones/SPK_Sphere.cpp
	src/Extensions/Renderers/SPK_Oriented3DRendererInterface.cpp
	src/Extensions/Renderers/SPK_QuadRendererInterface.cpp
	src/PLSceneNodes/SNSystem.cpp
	src/PLSceneNodes/SNFire.cpp
	src/PLSceneNodes/SNBasicDemo.cpp
	src/PLSceneNodes/SNGalaxyDemo.cpp
	src/PLSceneNodes/SNGravitationDemo.cpp
	src/RenderingAPIs/PixelLight/SPK_PLBuffer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineTrailRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineTrailRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLLineTrailRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLPointRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLPointRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLPointRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLQuadRenderer.cpp
	src/RenderingAPIs/PixelLight/SPK_PLQuadRendererFixedFunctions.cpp
	src/RenderingAPIs/PixelLight/SPK_PLQuadRendererShaders.cpp
	src/RenderingAPIs/PixelLight/SPK_PLRenderer.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	include/SPARK_PL
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
	${CMAKE_SOURCE_DIR}/PLBase/PLCore/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMath/include
	${CMAKE_SOURCE_DIR}/PLBase/PLGraphics/include
	${CMAKE_SOURCE_DIR}/PLBase/PLRenderer/include
	${CMAKE_SOURCE_DIR}/PLBase/PLMesh/include
	${CMAKE_SOURCE_DIR}/PLBase/PLScene/include
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
	PLMesh
	PLScene
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	SPARK_PL_EXPORTS
	SPK_CORE_EXPORT
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/PLRuntime)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLGeneral PLCore PLMath PLGraphics PLRenderer PLMesh PLScene)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

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
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_BIN_DIR}/PLRuntime/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_SHARED}			COMPONENT Runtime
)
