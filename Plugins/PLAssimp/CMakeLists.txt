##################################################
## Project
##################################################
define_project(PLAssimp)

##################################################
## Source files
##################################################
add_sources(
	src/PLAssimp.cpp
	src/AssimpMeshLoader.cpp
	# Common interchange formats (13 formats)
	src/MeshLoader/MeshLoaderCollada.cpp					# Collada ( .dae )
	src/MeshLoader/MeshLoaderBlender3D.cpp					# Blender 3D ( .blend )
	src/MeshLoader/MeshLoader3dsMax3DS.cpp					# 3ds Max 3DS ( .3ds )
	src/MeshLoader/MeshLoader3dsMaxASE.cpp					# 3ds Max ASE ( .ase )
	src/MeshLoader/MeshLoaderWavefrontObject.cpp			# Wavefront Object ( .obj )
	src/MeshLoader/MeshLoaderStanfordPolygonLibrary.cpp		# Stanford Polygon Library ( .ply )
	src/MeshLoader/MeshLoaderAutoCADDXF.cpp					# AutoCAD DXF ( .dxf )
	src/MeshLoader/MeshLoaderLightWave.cpp					# LightWave ( .lwo )
	src/MeshLoader/MeshLoaderModo.cpp						# Modo ( .lxo )
	src/MeshLoader/MeshLoaderStereolithography.cpp			# Stereolithography ( .stl )
	src/MeshLoader/MeshLoaderAC3D.cpp						# AC3D ( .ac )
	src/MeshLoader/MeshLoaderMilkshape3D.cpp				# Milkshape 3D ( .ms3d )
	src/MeshLoader/MeshLoaderTrueSpace.cpp					# TrueSpace ( .cob, .scn )
	# Game file formats (7 formats)
	src/MeshLoader/MeshLoaderValveModel.cpp					# Valve Model ( .smd, .vta )
	src/MeshLoader/MeshLoaderQuakeIMesh.cpp					# Quake I Mesh ( .mdl )
	src/MeshLoader/MeshLoaderQuakeIIMesh.cpp				# Quake II Mesh ( .md2 )
	src/MeshLoader/MeshLoaderQuakeIIIMesh.cpp				# Quake III Mesh ( .md3 )
	src/MeshLoader/MeshLoaderQuakeIIIBSP.cpp				# Quake III BSP ( .pk3 )
	src/MeshLoader/MeshLoaderReturnToCastleWolfenstein.cpp	# Return to Castle Wolfenstein ( .mdc )
	src/MeshLoader/MeshLoaderDoom3.cpp						# Doom 3 ( .md5* )
	# Other file formats (14 formats)
	src/MeshLoader/MeshLoaderDirectXX.cpp					# DirectX X ( .x )
	src/MeshLoader/MeshLoaderBlitzBasic3D.cpp				# BlitzBasic 3D ( .b3d )
	src/MeshLoader/MeshLoaderQuick3D.cpp					# Quick3D ( .q3d, .q3s )
	src/MeshLoader/MeshLoaderOgreXML.cpp					# Ogre XML ( .mesh.xml )
	src/MeshLoader/MeshLoaderIrrlichtMesh.cpp				# Irrlicht Mesh ( .irrmesh )
	src/MeshLoader/MeshLoaderIrrlichtScene.cpp				# Irrlicht Scene ( .irr )
	src/MeshLoader/MeshLoaderNeutralFileFormat.cpp			# Neutral File Format ( .nff )
	src/MeshLoader/MeshLoaderSense8WorldToolKit.cpp			# Sense8 WorldToolKit ( .nff )
	src/MeshLoader/MeshLoaderObjectFileFormat.cpp			# Object File Format ( .off )
	src/MeshLoader/MeshLoaderPovRAYRaw.cpp					# PovRAY Raw ( .raw )
	src/MeshLoader/MeshLoaderTerragenTerrain.cpp			# Terragen Terrain ( .ter )
	src/MeshLoader/MeshLoader3DGameStudio.cpp				# 3D GameStudio ( .mdl )
	src/MeshLoader/MeshLoader3DGameStudioTerrain.cpp		# 3D GameStudio Terrain ( .hmp )
	src/MeshLoader/MeshLoaderIzwareNendo.cpp				# Izware Nendo ( .ndo )
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
	${ASSIMP_INCLUDE_DIRS}
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
	PLCore
	PLMath
	PLGraphics
	PLRenderer
	PLMesh
	PLScene
	${ASSIMP_LIBRARIES}
)

##################################################
## Preprocessor definitions
##################################################
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
		PLATFORM_WINDOWS
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
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_BIN_DIR}/Runtime/Plugins/PLScene)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	External-Assimp PLCore PLMath PLGraphics PLRenderer PLMesh PLScene)
add_dependencies(Plugins                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/Runtime/Plugins/PLScene"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime/Plugins/PLScene"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/Runtime/Plugins/PLScene"
	)
endif()

if(LINUX)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_EXT_DIR}/Assimp/lib/libassimp.so.2			"${PL_BIN_DIR}/Runtime/Plugins/PLScene/"
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene	COMPONENT Runtime
)

# Plugin file
install(FILES ${PL_BIN_DIR}/Runtime/Plugins/PLScene/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_PLUGINS}/PLScene				COMPONENT Runtime
)


if(LINUX)
	install(FILES ${PL_BIN_DIR}/Runtime/Plugins/PLScene/libassimp.so.2
		DESTINATION ${PL_INSTALL_SHARED}						COMPONENT Runtime
	)
endif()
