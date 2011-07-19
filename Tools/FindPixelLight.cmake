##################################################
## FindPixelLight
##
## Find PixelLight libraries and includes
##################################################


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
	set(pl_runtime_env_lib  "${pl_runtime_env}/../Lib")
	set(pl_runtime_env_inc  "${pl_runtime_env}/../Include")
	set(pl_runtime_env_base "${pl_runtime_env}/../..")
endif()

# Read registry key
get_filename_component(pl_runtime_reg [HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK;Runtime] ABSOLUTE)
if(pl_runtime_reg)
	set(pl_runtime_reg_bin  "${pl_runtime_reg}")
	set(pl_runtime_reg_lib  "${pl_runtime_reg}/../Lib")
	set(pl_runtime_reg_inc  "${pl_runtime_reg}/../Include")
	set(pl_runtime_reg_base "${pl_runtime_reg}/../..")
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

# PLCore
_pixellight_find_lib(PL_PLCORE PLCore/PLCore.h PLCore Base/PLCore/include)
#message("PLCore include: ${PL_PLCORE_INCLUDE_DIR}")
#message("PLCore library: ${PL_PLCORE_LIBRARY}")

# PLGraphics
_pixellight_find_lib(PL_PLGRAPHICS PLGraphics/PLGraphics.h PLGraphics Base/PLGraphics/include)
#message("PLGraphics include: ${PL_PLGRAPHICS_INCLUDE_DIR}")
#message("PLGraphics library: ${PL_PLGRAPHICS_LIBRARY}")

# PLMath
_pixellight_find_lib(PL_PLMATH PLMath/PLMath.h PLMath Base/PLMath/include)
#message("PLMath include: ${PL_PLMATH_INCLUDE_DIR}")
#message("PLMath library: ${PL_PLMATH_LIBRARY}")

# PLDatabase
_pixellight_find_lib(PL_PLDATABASE PLDatabase/PLDatabase.h PLDatabase Base/PLDatabase/include)
#message("PLDatabase include: ${PL_PLDATABASE_INCLUDE_DIR}")
#message("PLDatabase library: ${PL_PLDATABASE_LIBRARY}")


# PLGui

# PLGui
_pixellight_find_lib(PL_PLGUI PLGui/PLGui.h PLGui PLGui/PLGui/include)
#message("PLGui include: ${PL_PLGUI_INCLUDE_DIR}")
#message("PLGui library: ${PL_PLGUI_LIBRARY}")


# PLEngine

# PLEngine
_pixellight_find_lib(PL_PLENGINE PLEngine/PLEngine.h PLEngine Base/PLEngine/include)
#message("PLEngine include: ${PL_PLENGINE_INCLUDE_DIR}")
#message("PLEngine library: ${PL_PLENGINE_LIBRARY}")

# PLCompositing
_pixellight_find_lib(PL_PLCOMPOSITING PLCompositing/PLCompositing.h PLCompositing PLEngine/PLCompositing/include)
#message("PLCompositing include: ${PL_PLCOMPOSITING_INCLUDE_DIR}")
#message("PLCompositing library: ${PL_PLCOMPOSITING_LIBRARY}")

# PLInput
_pixellight_find_lib(PL_PLINPUT PLInput/PLInput.h PLInput Base/PLInput/include)
#message("PLInput include: ${PL_PLINPUT_INCLUDE_DIR}")
#message("PLInput library: ${PL_PLINPUT_LIBRARY}")

# PLMesh
_pixellight_find_lib(PL_PLMESH PLMesh/PLMesh.h PLMesh Base/PLMesh/include)
#message("PLMesh include: ${PL_PLMESH_INCLUDE_DIR}")
#message("PLMesh library: ${PL_PLMESH_LIBRARY}")

# PLPhysics
_pixellight_find_lib(PL_PLPHYSICS PLPhysics/PLPhysics.h PLPhysics Base/PLPhysics/include)
#message("PLPhysics include: ${PL_PLPHYSICS_INCLUDE_DIR}")
#message("PLPhysics library: ${PL_PLPHYSICS_LIBRARY}")

# PLRenderer
_pixellight_find_lib(PL_PLRENDERER PLRenderer/PLRenderer.h PLRenderer Base/PLRenderer/include)
#message("PLRenderer include: ${PL_PLRENDERER_INCLUDE_DIR}")
#message("PLRenderer library: ${PL_PLRENDERER_LIBRARY}")

# PLScene
_pixellight_find_lib(PL_PLSCENE PLScene/PLScene.h PLScene Base/PLScene/include)
#message("PLScene include: ${PL_PLSCENE_INCLUDE_DIR}")
#message("PLScene library: ${PL_PLSCENE_LIBRARY}")

# PLSound
_pixellight_find_lib(PL_PLSOUND PLSound/PLSound.h PLSound Base/PLSound/include)
#message("PLSound include: ${PL_PLSOUND_INCLUDE_DIR}")
#message("PLSound library: ${PL_PLSOUND_LIBRARY}")


# Plugins

# PLIRC
_pixellight_find_lib(PL_PLIRC PLIRC/PLIRC.h PLIRC Plugins/PLIRC/include)
#message("PLIRC include: ${PL_PLIRC_INCLUDE_DIR}")
#message("PLIRC library: ${PL_PLIRC_LIBRARY}")

# PLJabber
_pixellight_find_lib(PL_PLJABBER PLJabber/PLJabber.h PLJabber Plugins/PLJabber/include)
#message("PLJabber include: ${PL_PLJABBER_INCLUDE_DIR}")
#message("PLJabber library: ${PL_PLJABBER_LIBRARY}")

# PLXmlText
_pixellight_find_lib(PL_PLXMLTEXT PLXmlText/PLXmlText.h PLXmlText Plugins/PLXmlText/include)
#message("PLXmlText include: ${PL_PLXMLTEXT_INCLUDE_DIR}")
#message("PLXmlText library: ${PL_PLXMLTEXT_LIBRARY}")


# Set PixelLight_FOUND variable based on PLCore (we need at least that lib)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PixelLight DEFAULT_MSG 
                                  PL_PLCORE_LIBRARY PL_PLCORE_INCLUDE_DIR) 
