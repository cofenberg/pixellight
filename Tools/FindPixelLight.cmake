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
# 1. Search in the directory pointed to by the environment variable 'PL_RUNTIME'
# 2. Search in the directory pointed to by the registry key [HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK;Runtime]
# 3. Search in standard directories (e.g. /usr/lib, /usr/local/lib, /usr/include, /usr/local/include)
#
# Includes are searched in subdirectory Include/ first (for installed SDKs on Windows), then using the PixelLight source
# layout, e.g. Base/PLCore/include.
#
# Libraries are searched using a suffix "D" for debug builds, if that is not found, the search is repeated without the
# suffix (allowing for debug builds using a release version of the PixelLight libraries)


# Includes
INCLUDE(FindPackageHandleStandardArgs)


# Determine debug suffix
set(suffix "")
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(suffix "D")
endif()

# Read environment variable PL_RUNTIME
set(pl_runtime_env $ENV{PL_RUNTIME})
if(pl_runtime_env)
	set(pl_runtime_env_bin  "${pl_runtime_env}")
	set(pl_runtime_env_lib  "${pl_runtime_env}/../../Lib")
	set(pl_runtime_env_inc  "${pl_runtime_env}/../../Include")
	set(pl_runtime_env_base "${pl_runtime_env}/../../..")
endif()

# Read registry key
get_filename_component(pl_runtime_reg [HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK;Runtime] ABSOLUTE)
if(pl_runtime_reg)
	set(pl_runtime_reg_bin  "${pl_runtime_reg}")
	set(pl_runtime_reg_lib  "${pl_runtime_reg}/../../Lib")
	set(pl_runtime_reg_inc  "${pl_runtime_reg}/../../Include")
	set(pl_runtime_reg_base "${pl_runtime_reg}/../../..")
endif()


# Macro to determine if a specific PixelLight library is there
macro(_pixellight_find_lib varname header library basepath)
	# Include
	FIND_PATH(${varname}_INCLUDE_DIR 		${header}
				"${pl_runtime_env_inc}"
				"${pl_runtime_env_base}/${basepath}"
				"${pl_runtime_reg_inc}"
				"${pl_runtime_reg_base}/${basepath}"
	)

	# Library
	FIND_LIBRARY(${varname}_LIBRARY			${library}${suffix}
				"${pl_runtime_env_lib}"
				"${pl_runtime_env_bin}"
				"${pl_runtime_reg_lib}"
				"${pl_runtime_reg_bin}"
	)

	# Try without suffix
	if(NOT ${varname}_LIBRARY)
		FIND_LIBRARY(${varname}_LIBRARY		${library}
					"${pl_runtime_env_lib}"
					"${pl_runtime_env_bin}"
					"${pl_runtime_reg_lib}"
					"${pl_runtime_reg_bin}"
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
_pixellight_find_lib(PL_PLCOMPOSITING		PLCompositing/PLCompositing.h				PLCompositing		PLEngine/PLCompositing/include)
_pixellight_find_lib(PL_PLIRC				PLIRC/PLIRC.h								PLIRC				Plugins/PLIRC/include)
_pixellight_find_lib(PL_PLJABBER			PLJabber/PLJabber.h							PLJabber			Plugins/PLJabber/include)
_pixellight_find_lib(PL_PLGUIXMLTEXT		PLGuiXmlText/PLGuiXmlText.h					PLGuiXmlText		Plugins/PLGuiXmlText/include)
_pixellight_find_lib(PL_PLFRONTENDPLGUI		PLFrontendPLGui/PLFrontendPLGui.h			PLFrontendPLGui		Plugins/PLFrontendPLGui/include)
_pixellight_find_lib(PL_PLRENDEREROPENGLES2	PLRendererOpenGLES2/PLRendererOpenGLES2.h	PLRendererOpenGLES2	Plugins/PLRendererOpenGLES2/include)
_pixellight_find_lib(PL_PLSPARK_PL			SPARK_PL/SPARK_PL.h							SPARK_PL			Plugins/SPARK_PL/include)
_pixellight_find_lib(PL_PLSCRIPTBINDINGS	PLScriptBindings/PLScriptBindings.h			PLScriptBindings	Plugins/PLScriptBindings/include)
_pixellight_find_lib(PL_PLSCRIPTLUA			PLScriptLua/PLScriptLua.h					PLScriptLua			Plugins/PLScriptLua/include)
_pixellight_find_lib(PL_PLLIBROCKET			PLlibRocket/PLlibRocket.h					PLlibRocket			Plugins/PLlibRocket/include)


# libRocket
_pixellight_find_lib(PL_LIBROCKETCORE		Rocket/Core.h								RocketCore			"")
_pixellight_find_lib(PL_LIBROCKETCONTROLS	Rocket/Controls.h							RocketControls		"")
_pixellight_find_lib(PL_LIBROCKETDEBUGGER	Rocket/Debugger.h							RocketDebugger		"")


# Directories
FIND_PATH(PL_PLRUNTIME_DIR 	"Data"
			"${pl_runtime_env}/.."
			"${pl_runtime_reg}/.."
)
FIND_PATH(PL_PLSAMPLES_DIR 	"Data"
			"${pl_runtime_env}/../../Samples"
			"${pl_runtime_reg}/../../Samples"
)


# Set PixelLight_FOUND variable based on PLCore (we need at least that lib)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PixelLight DEFAULT_MSG 
                                  PL_PLCORE_LIBRARY PL_PLCORE_INCLUDE_DIR) 
