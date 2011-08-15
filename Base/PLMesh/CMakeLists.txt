##################################################
## Project
##################################################
define_project(PLMesh)

##################################################
## Source files
##################################################
add_sources(
	src/Creator/MeshCreatorTriangle.cpp
	src/Creator/MeshCreatorDome.cpp
	src/Creator/MeshCreatorCappedCylinder.cpp
	src/Creator/MeshCreatorFlashlight.cpp
	src/Creator/MeshCreatorPartialDisk.cpp
	src/Creator/MeshCreatorSphere.cpp
	src/Creator/MeshCreatorSuperEllipse.cpp
	src/Creator/MeshCreatorCylinder.cpp
	src/Creator/MeshCreatorQuad.cpp
	src/Creator/MeshCreatorDisk.cpp
	src/Creator/MeshCreatorTorus.cpp
	src/Creator/MeshCreatorBezierPatch.cpp
	src/Creator/MeshCreatorTeapot.cpp
	src/Creator/MeshCreatorCube.cpp
	src/Creator/MeshCreator.cpp
	src/Loader/MeshLoader.cpp
	src/Loader/MeshLoaderPL.cpp
	src/Loader/MeshLoaderPLXml.cpp
	src/Loader/MeshFile.cpp
	src/Loader/SkeletonAniLoader.cpp
	src/SPMeshPreview.cpp
	src/MeshMorphTarget.cpp
	src/JointHandler.cpp
	src/SkeletonHandler.cpp
	src/MeshLODLevel.cpp
	src/Joint.cpp
	src/MorphTargetAni.cpp
	src/JointState.cpp
	src/Weight.cpp
	src/MeshHandler.cpp
	src/Geometry.cpp
	src/MeshOctree.cpp
	src/VertexWeights.cpp
	src/MeshAnimationManager.cpp
	src/MeshAnimationManagerSoftware.cpp
	src/MeshAnimationManagerHardware.cpp
	src/JointAni.cpp
	src/SkeletonManager.cpp
	src/AnchorPoint.cpp
	src/Skeleton.cpp
	src/MeshManager.cpp
	src/Mesh.cpp
	src/PLMesh.cpp
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
)

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLMESH_EXPORTS
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLGraphics PLMath PLRenderer)
add_dependencies(Base                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib/${CMAKETOOLS_TARGET_ARCHBITSIZE}"
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
install(FILES ${PL_BIN_DIR}/Runtime/${CMAKETOOLS_TARGET_ARCHBITSIZE}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_SHARED}			COMPONENT Runtime
)
