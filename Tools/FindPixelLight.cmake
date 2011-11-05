#*********************************************************#
#*  File: FindPixelLight.cmake                           *
#*    Find PixelLight libraries and includes
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
#*********************************************************#


# This script searches for the PixelLight includes and libraries in the following order:
# 1. If PL_RUNTIME_BIN_DIR is set then this path is used
# 2. Search in the directory pointed to by the environment variable 'PL_RUNTIME'
# 3. Search in the directory pointed to by the registry key [HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK;Runtime]
# 4. Search in standard directories (e.g. /usr/lib, /usr/local/lib, /usr/include, /usr/local/include)
#
# Includes are searched in subdirectory Include/ first (for installed SDKs on Windows), then using the PixelLight source
# layout, e.g. Base/PLCore/include.
#
# Libraries are searched using a suffix "D" for debug builds, if that is not found, the search is repeated without the
# suffix (allowing for debug builds using a release version of the PixelLight libraries)


# General variables
# Name						Description								Example
# PL_ARCHBITSIZE			Target architecture & bitsize			"armeabi-v7a" (or "x86", "x64", "armeabi" etc.)
# PL_ROOT					PixelLight root directory				"/home/username/pixellight"
# PL_RUNTIME_DIR			PixelLight runtime directory			"/home/username/pixellight/Bin-Linux-ndk/Runtime"
# PL_RUNTIME_BIN_DIR		PixelLight runtime binary directory		"/home/username/pixellight/Bin-Linux-ndk/Runtime/armeabi-v7a"
# PL_RUNTIME_DATA_DIR		PixelLight runtime data directory		"/home/username/pixellight/Bin-Linux-ndk/Runtime/Data"
# PL_LIB_DIR				PixelLight library directory			"/home/username/pixellight/Bin-Linux-ndk/Lib/armeabi-v7a"
# PL_INCLUDE_DIR			PixelLight include directory			"/home/username/pixellight/Bin-Linux-ndk/Include"
# PL_SAMPLES_DIR			PixelLight samples directory			"/home/username/pixellight/Bin-Linux-ndk/Samples"
# PL_SAMPLES_BIN_DIR		PixelLight samples binary directory		"/home/username/pixellight/Bin-Linux-ndk/Samples/armeabi-v7a"
# PL_SAMPLES_DATA_DIR		PixelLight samples data directory		"/home/username/pixellight/Bin-Linux-ndk/Samples/Data"
# PL_TESTS_DIR				PixelLight tests directory				"/home/username/pixellight/Bin-Linux-ndk/Tests"
# PL_TESTS_BIN_DIR			PixelLight tests binary directory		"/home/username/pixellight/Bin-Linux-ndk/Tests/armeabi-v7a"
# PL_TESTS_DATA_DIR			PixelLight tests data directory			"/home/username/pixellight/Bin-Linux-ndk/Tests/Data"


# Includes
include(FindPackageHandleStandardArgs)

# Determine debug suffix
set(suffix "")
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(suffix "D")
endif()

# Read environment variable PL_RUNTIME, but only if PL_RUNTIME_BIN_DIR has not been provided by the outside world
if(NOT PL_RUNTIME_BIN_DIR OR PL_RUNTIME_BIN_DIR STREQUAL "")
	set(PL_RUNTIME_BIN_DIR $ENV{PL_RUNTIME})
	if(NOT PL_RUNTIME_BIN_DIR OR PL_RUNTIME_BIN_DIR STREQUAL "")
		# Read registry key
		get_filename_component(PL_RUNTIME_BIN_DIR "[HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK;Runtime]" ABSOLUTE)
	endif()
endif()

# Get general variables
get_filename_component(PL_ARCHBITSIZE		"${PL_RUNTIME_BIN_DIR}"							NAME_WE)
get_filename_component(PL_ROOT				"${PL_RUNTIME_BIN_DIR}/../../.."				ABSOLUTE)
get_filename_component(PL_RUNTIME_BIN_DIR	"${PL_RUNTIME_BIN_DIR}"							ABSOLUTE)
get_filename_component(PL_RUNTIME_DIR		"${PL_RUNTIME_BIN_DIR}/.."						ABSOLUTE)
get_filename_component(PL_RUNTIME_DATA_DIR	"${PL_RUNTIME_DIR}/Data"						ABSOLUTE)
get_filename_component(PL_LIB_DIR			"${PL_RUNTIME_DIR}/../Lib/${PL_ARCHBITSIZE}"	ABSOLUTE)
get_filename_component(PL_INCLUDE_DIR		"${PL_RUNTIME_DIR}/../Include"					ABSOLUTE)
get_filename_component(PL_SAMPLES_DIR		"${PL_RUNTIME_DIR}/../Samples"					ABSOLUTE)
get_filename_component(PL_SAMPLES_BIN_DIR	"${PL_SAMPLES_DIR}/${PL_ARCHBITSIZE}"			ABSOLUTE)
get_filename_component(PL_SAMPLES_DATA_DIR	"${PL_SAMPLES_DIR}/Data"						ABSOLUTE)
get_filename_component(PL_TESTS_DIR			"${PL_RUNTIME_DIR}/../Tests"					ABSOLUTE)
get_filename_component(PL_TESTS_BIN_DIR		"${PL_TESTS_DIR}/${PL_ARCHBITSIZE}"				ABSOLUTE)
get_filename_component(PL_TESTS_DATA_DIR	"${PL_TESTS_DIR}/Data"							ABSOLUTE)
if(PL_ROOT)
	message(STATUS "Target architecture & bitsize: ${PL_ARCHBITSIZE}")
	message(STATUS "PixelLight root directory: ${PL_ROOT}")
	message(STATUS "PixelLight runtime directory: ${PL_RUNTIME_DIR}")
	message(STATUS "PixelLight runtime binary directory: ${PL_RUNTIME_BIN_DIR}")
	message(STATUS "PixelLight runtime data directory: ${PL_RUNTIME_DATA_DIR}")
	message(STATUS "PixelLight library directory: ${PL_LIB_DIR}")
	message(STATUS "PixelLight include directory: ${PL_INCLUDE_DIR}")
	message(STATUS "PixelLight samples directory: ${PL_SAMPLES_DIR}")
	message(STATUS "PixelLight samples binary directory: ${PL_SAMPLES_BIN_DIR}")
	message(STATUS "PixelLight samples data directory: ${PL_SAMPLES_DATA_DIR}")
	message(STATUS "PixelLight tests directory: ${PL_TESTS_DIR}")
	message(STATUS "PixelLight tests binary directory: ${PL_TESTS_BIN_DIR}")
	message(STATUS "PixelLight tests data directory: ${PL_TESTS_DATA_DIR}")
else()
	if(WIN32)
		message(STATUS "PixelLight not found - Possible solution: Set registry key \"[HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK;Runtime]\" (or \"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-SDK;Runtime]\" if you are using a 32 bit PixelLight on a 64 bit MS Windows) to e.g. \"C:\\PixelLight\\Bin\\Runtime\\x86"\")
	else()
		message(STATUS "PixelLight not found - Possible solution: Set environment variable \"PL_RUNTIME\" to e.g. \"/home/username/pixellight/Bin-Linux/Runtime/x86\"")
	endif()
endif()

# Macro to determine if a specific PixelLight library is there
macro(_pixellight_find_lib varname header library basepath)
	# Include
	FIND_PATH(${varname}_INCLUDE_DIR 		${header}
				"${PL_INCLUDE_DIR}"
				"${PL_ROOT}/${basepath}"
	)

	# Library
	FIND_LIBRARY(${varname}_LIBRARY			${library}${suffix}
				"${PL_RUNTIME_BIN_DIR}"
				"${PL_LIB_DIR}"
	)

	# Try without suffix
	if(NOT ${varname}_LIBRARY)
		FIND_LIBRARY(${varname}_LIBRARY		${library}
				"${PL_RUNTIME_BIN_DIR}"
				"${PL_LIB_DIR}"
		)
	endif()

	# Check if found
	if(${varname}_INCLUDE_DIR AND ${varname}_LIBRARY)
		SET(${varname}_FOUND 1)
	endif()
endmacro(_pixellight_find_lib varname header library basepath)


# Base
_pixellight_find_lib(PL_PLCORE		PLCore/PLCore.h			PLCore		Base/PLCore/include)
_pixellight_find_lib(PL_PLDATABASE	PLDatabase/PLDatabase.h	PLDatabase	Base/PLDatabase/include)
_pixellight_find_lib(PL_PLMATH		PLMath/PLMath.h			PLMath		Base/PLMath/include)
_pixellight_find_lib(PL_PLGRAPHICS	PLGraphics/PLGraphics.h	PLGraphics	Base/PLGraphics/include)
_pixellight_find_lib(PL_PLGUI		PLGui/PLGui.h			PLGui		Base/PLGui/include)
_pixellight_find_lib(PL_PLINPUT		PLInput/PLInput.h		PLInput		Base/PLInput/include)
_pixellight_find_lib(PL_PLRENDERER	PLRenderer/PLRenderer.h	PLRenderer	Base/PLRenderer/include)
_pixellight_find_lib(PL_PLMESH		PLMesh/PLMesh.h			PLMesh		Base/PLMesh/include)
_pixellight_find_lib(PL_PLSCENE		PLScene/PLScene.h		PLScene		Base/PLScene/include)
_pixellight_find_lib(PL_PLENGINE	PLEngine/PLEngine.h		PLEngine	Base/PLEngine/include)
_pixellight_find_lib(PL_PLPHYSICS	PLPhysics/PLPhysics.h	PLPhysics	Base/PLPhysics/include)
_pixellight_find_lib(PL_PLSOUND		PLSound/PLSound.h		PLSound		Base/PLSound/include)


# Plugins
_pixellight_find_lib(PL_PLASSIMP				PLAssimp/PLAssimp.h							PLAssimp				Plugins/PLAssimp/include)
_pixellight_find_lib(PL_PLCOMPOSITING			PLCompositing/PLCompositing.h				PLCompositing			PLEngine/PLCompositing/include)
# Database plugins
_pixellight_find_lib(PL_PLDATABASEMYSQL			PLDatabaseMySQL/PLDatabaseMySQL.h			PLDatabaseMySQL			Plugins/PLDatabaseMySQL/include)
_pixellight_find_lib(PL_PLDATABASENULL			PLDatabaseNull/PLDatabaseNull.h				PLDatabaseNull			Plugins/PLDatabaseNull/include)
_pixellight_find_lib(PL_PLDATABASEPOSTGRESQL	PLDatabasePostgreSQL/PLDatabasePostgreSQL.h	PLDatabasePostgreSQL	Plugins/PLDatabasePostgreSQL/include)
_pixellight_find_lib(PL_PLDATABASESQLITE		PLDatabaseSQLite/PLDatabaseSQLite.h			PLDatabaseSQLite		Plugins/PLDatabaseSQLite/include)
# Frontend plugins
_pixellight_find_lib(PL_PLFRONTENDACTIVEX		PLFrontendActiveX/PLFrontendActiveX.h		PLFrontendActiveX		Plugins/PLFrontendActiveX/include)
_pixellight_find_lib(PL_PLFRONTENDMOZILLA		PLFrontendMozilla/PLFrontendMozilla.h		PLFrontendMozilla		Plugins/PLFrontendMozilla/include)
_pixellight_find_lib(PL_PLFRONTENDNULL			PLFrontendNull/PLFrontendNull.h				PLFrontendNull			Plugins/PLFrontendNull/include)
_pixellight_find_lib(PL_PLFRONTENDOS			PLFrontendOS/PLFrontendOS.h					PLFrontendOS			Plugins/PLFrontendOS/include)
_pixellight_find_lib(PL_PLFRONTENDPLGUI			PLFrontendPLGui/PLFrontendPLGui.h			PLFrontendPLGui			Plugins/PLFrontendPLGui/include)
_pixellight_find_lib(PL_PLFRONTENDQT			PLFrontendQt/PLFrontendQt.h					PLFrontendQt			Plugins/PLFrontendQt/include)
# Misc plugins
_pixellight_find_lib(PL_PLGUIXMLTEXT			PLGuiXmlText/PLGuiXmlText.h					PLGuiXmlText			Plugins/PLGuiXmlText/include)
_pixellight_find_lib(PL_PLIMAGELOADEREXR		PLImageLoaderEXR/PLImageLoaderEXR.h			PLImageLoaderEXR		Plugins/PLImageLoaderEXR/include)
_pixellight_find_lib(PL_PLIRC					PLIRC/PLIRC.h								PLIRC					Plugins/PLIRC/include)
_pixellight_find_lib(PL_PLJABBER				PLJabber/PLJabber.h							PLJabber				Plugins/PLJabber/include)
_pixellight_find_lib(PL_PLLIBROCKET				PLlibRocket/PLlibRocket.h					PLlibRocket				Plugins/PLlibRocket/include)
_pixellight_find_lib(PL_PLPARTICLEGROUPS		PLParticleGroups/PLParticleGroups.h			PLParticleGroups		Plugins/PLParticleGroups/include)
# Physics plugins
_pixellight_find_lib(PL_PLPHYSICSBULLET			PLPhysicsBullet/PLPhysicsBullet.h			PLPhysicsBullet			Plugins/PLPhysicsBullet/include)
_pixellight_find_lib(PL_PLPHYSICSNEWTON			PLPhysicsNewton/PLPhysicsNewton.h			PLPhysicsNewton			Plugins/PLPhysicsNewton/include)
_pixellight_find_lib(PL_PLPHYSICSNULL			PLPhysicsNull/PLPhysicsNull.h				PLPhysicsNull			Plugins/PLPhysicsNull/include)
_pixellight_find_lib(PL_PLPHYSICSODE			PLPhysicsODE/PLPhysicsODE.h					PLPhysicsODE			Plugins/PLPhysicsODE/include)
_pixellight_find_lib(PL_PLPHYSICSPHYSX			PLPhysicsPhysX/PLPhysicsPhysX.h				PLPhysicsPhysX			Plugins/PLPhysicsPhysX/include)
# Misc plugins
_pixellight_find_lib(PL_PLPOSTPROCESSEFFECTS	PLPostProcessEffects/PLPostProcessEffects.h	PLPostProcessEffects	Plugins/PLPostProcessEffects/include)
# Renderer plugins
_pixellight_find_lib(PL_PLRENDERERD3D9			PLRendererD3D9/PLRendererD3D9.h				PLRendererD3D9			Plugins/PLRendererD3D9/include)
_pixellight_find_lib(PL_PLRENDERERD3D11			PLRendererD3D11/PLRendererD3D11.h			PLRendererD3D11			Plugins/PLRendererD3D11/include)
_pixellight_find_lib(PL_PLRENDERERNULL			PLRendererNull/PLRendererNull.h				PLRendererNull			Plugins/PLRendererNull/include)
_pixellight_find_lib(PL_PLRENDEREROPENGL		PLRendererOpenGL/PLRendererOpenGL.h			PLRendererOpenGL		Plugins/PLRendererOpenGL/include)
_pixellight_find_lib(PL_PLRENDEREROPENGLCG		PLRendererOpenGLCg/PLRendererOpenGLCg.h		PLRendererOpenGLCg		Plugins/PLRendererOpenGLCg/include)
_pixellight_find_lib(PL_PLRENDEREROPENGLES2		PLRendererOpenGLES2/PLRendererOpenGLES2.h	PLRendererOpenGLES2		Plugins/PLRendererOpenGLES2/include)
# Script plugins
_pixellight_find_lib(PL_PLSCRIPTANGELSCRIPT		PLScriptAngelScript/PLScriptAngelScript.h	PLScriptAngelScript		Plugins/PLScriptAngelScript/include)
_pixellight_find_lib(PL_PLSCRIPTBINDINGS		PLScriptBindings/PLScriptBindings.h			PLScriptBindings		Plugins/PLScriptBindings/include)
_pixellight_find_lib(PL_PLSCRIPTLUA				PLScriptLua/PLScriptLua.h					PLScriptLua				Plugins/PLScriptLua/include)
_pixellight_find_lib(PL_PLSCRIPTNULL			PLScriptNull/PLScriptNull.h					PLScriptNull			Plugins/PLScriptNull/include)
_pixellight_find_lib(PL_PLSCRIPTPHYTON			PLScriptPython/PLScriptPython.h				PLScriptPython			Plugins/PLScriptPython/include)
_pixellight_find_lib(PL_PLSCRIPTV8				PLScriptV8/PLScriptV8.h						PLScriptV8				Plugins/PLScriptV8/include)
# Sound plugins
_pixellight_find_lib(PL_PLSOUNDFMOD				PLSoundFMOD/PLSoundFMOD.h					PLSoundFMOD				Plugins/PLSoundFMOD/include)
_pixellight_find_lib(PL_PLSOUNDFMODEX			PLSoundFMODEx/PLSoundFMODEx.h				PLSoundFMODEx			Plugins/PLSoundFMODEx/include)
_pixellight_find_lib(PL_PLSOUNDNULL				PLSoundNull/PLSoundNull.h					PLSoundNull				Plugins/PLSoundNull/include)
_pixellight_find_lib(PL_PLSOUNDOPENAL			PLSoundOpenAL/PLSoundOpenAL.h				PLSoundOpenAL			Plugins/PLSoundOpenAL/include)
_pixellight_find_lib(PL_PLSOUNDOPENSLES			PLSoundOpenSLES/PLSoundOpenSLES.h			PLSoundOpenSLES			Plugins/PLSoundOpenSLES/include)
# Misc plugins
_pixellight_find_lib(PL_PLSPARK_PL				SPARK_PL/SPARK_PL.h							SPARK_PL				Plugins/SPARK_PL/include)


# Newton
_pixellight_find_lib(PL_NEWTON					Newton/Newton.h								Newton					"")


# libRocket
_pixellight_find_lib(PL_LIBROCKETCORE			Rocket/Core.h								RocketCore				"")
_pixellight_find_lib(PL_LIBROCKETCONTROLS		Rocket/Controls.h							RocketControls			"")
_pixellight_find_lib(PL_LIBROCKETDEBUGGER		Rocket/Debugger.h							RocketDebugger			"")


# FMOD Ex
_pixellight_find_lib(PL_FMODEX					FMODEx/FMODEx.h								fmodex					"")


# Set PixelLight_FOUND variable based on PLCore (we need at least that lib)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PixelLight DEFAULT_MSG 
                                  PL_PLCORE_LIBRARY PL_PLCORE_INCLUDE_DIR) 


# Android APK tool
if(ANDROID)
	include("${PL_ROOT}/cmake/Android/Apk.cmake")
endif()
