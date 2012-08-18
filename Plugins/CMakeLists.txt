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
#*********************************************************#


##################################################
## Project
##################################################
project(Plugins)

##################################################
## Target
##################################################
add_custom_target(Plugins)

##################################################
## Projects
##################################################
if(PL_PLUGIN_ENGINE_COMPOSITING)
	add_subdirectory(PLCompositing)
endif()
if(PL_PLUGIN_ENGINE_SCRIPTBINDINGS)
	add_subdirectory(PLScriptBindings)
endif()
if(PL_PLUGIN_NETWORK_IRC)
	add_subdirectory(PLIRC)
endif()
if(PL_PLUGIN_NETWORK_JABBER)
	add_subdirectory(PLJabber)
endif()
if(PL_PLGUI AND PL_PLUGIN_GUI_XMLTEXT)
	add_subdirectory(PLGuiXmlText)
endif()
if(PL_PLUGIN_ENGINE_ASSIMP)
	add_subdirectory(PLAssimp)
endif()
if(PL_PLUGIN_ENGINE_IMAGEEXR)
	add_subdirectory(PLImageLoaderEXR)
endif()
if(PL_PLUGIN_ENGINE_PARTICLEGROUPS)
	add_subdirectory(PLParticleGroups)
endif()
if(PL_PLUGIN_ENGINE_SPARK)
	add_subdirectory(SPARK_PL)
endif()
if(PL_PLUGIN_ENGINE_LIBROCKET)
	add_subdirectory(PLlibRocket)
endif()
if(PL_PLUGIN_ENGINE_POSTPROCESS)
	add_subdirectory(PLPostProcessEffects)
endif()
if(PL_PLUGIN_ENGINE_NATURE)
	add_subdirectory(PLNature)
endif()
# Script backends
if(PL_PLUGIN_SCRIPT_NULL)
	add_subdirectory(PLScriptNull)
endif()
if(PL_PLUGIN_SCRIPT_LUA)
	add_subdirectory(PLScriptLua)
endif()
if(PL_PLUGIN_SCRIPT_V8)
	add_subdirectory(PLScriptV8)
endif()
if(PL_PLUGIN_SCRIPT_PYTHON)
	add_subdirectory(PLScriptPython)
endif()
if(PL_PLUGIN_SCRIPT_ANGELSCRIPT)
	add_subdirectory(PLScriptAngelScript)
endif()
# Frontend backends
if(PL_PLUGIN_FRONTEND_NULL)
	add_subdirectory(PLFrontendNull)
endif()
if(PL_PLUGIN_FRONTEND_OS)
	add_subdirectory(PLFrontendOS)
endif()
if(PL_PLGUI AND PL_PLUGIN_FRONTEND_PLGUI)
	add_subdirectory(PLFrontendPLGui)
endif()
if(PL_PLUGIN_FRONTEND_QT)
	add_subdirectory(PLFrontendQt)
endif()
if(PL_PLUGIN_FRONTEND_ACTIVEX)
	add_subdirectory(PLFrontendActiveX)
endif()
if(PL_PLUGIN_FRONTEND_MOZILLA)
	add_subdirectory(PLFrontendMozilla)
endif()
# PLDatabase backends
if(PL_PLUGIN_DATABASE_NULL)
	add_subdirectory(PLDatabaseNull)
endif()
if(PL_PLUGIN_DATABASE_MYSQL)
	add_subdirectory(PLDatabaseMySQL)
endif()
if(PL_PLUGIN_DATABASE_POSTGRESQL)
	add_subdirectory(PLDatabasePostgreSQL)
endif()
if(PL_PLUGIN_DATABASE_SQLITE)
	add_subdirectory(PLDatabaseSQLite)
endif()
# PLRenderer backends
if(PL_PLUGIN_RENDERER_NULL)
	add_subdirectory(PLRendererNull)
endif()
if(PL_PLUGIN_RENDERER_OPENGL)
	add_subdirectory(PLRendererOpenGL)
	if(PL_PLUGIN_RENDERER_OPENGLCG)
		add_subdirectory(PLRendererOpenGLCg)
	endif()
endif()
if(PL_PLUGIN_RENDERER_OPENGLES2)
	add_subdirectory(PLRendererOpenGLES2)
endif()
if(PL_PLUGIN_RENDERER_D3D9)
	add_subdirectory(PLRendererD3D9)
endif()
if(PL_PLUGIN_RENDERER_D3D11)
	add_subdirectory(PLRendererD3D11)
endif()
# PLPhysics backends
if(PL_PLUGIN_PHYSICS_NULL)
	add_subdirectory(PLPhysicsNull)
endif()
if(PL_PLUGIN_PHYSICS_NEWTON)
	add_subdirectory(PLPhysicsNewton)
endif()
if(PL_PLUGIN_PHYSICS_ODE)
	add_subdirectory(PLPhysicsODE)
endif()
if(PL_PLUGIN_PHYSICS_PHYSX)
	add_subdirectory(PLPhysicsPhysX)
endif()
if(PL_PLUGIN_PHYSICS_BULLET)
	add_subdirectory(PLPhysicsBullet)
endif()
# PLSound backends
if(PL_PLUGIN_SOUND_NULL)
	add_subdirectory(PLSoundNull)
endif()
if(PL_PLUGIN_SOUND_OPENAL)
	add_subdirectory(PLSoundOpenAL)
endif()
if(PL_PLUGIN_SOUND_OPENSLES)
	add_subdirectory(PLSoundOpenSLES)
endif()
if(PL_PLUGIN_SOUND_FMOD)
	add_subdirectory(PLSoundFMOD)
endif()
if(PL_PLUGIN_SOUND_FMODEX)
	add_subdirectory(PLSoundFMODEx)
endif()
# PLVolume
if(PL_PLUGIN_VOLUME)
	add_subdirectory(PLVolume)
	if(PL_PLUGIN_VOLUME_RENDERER)
		add_subdirectory(PLVolumeRenderer)
	endif()
	if(PL_PLUGIN_VOLUME_GUI AND PL_PLUGIN_FRONTEND_QT)
		add_subdirectory(PLVolumeGui)
	endif()
	if(PL_PLUGIN_VOLUME_LOADER_PVM)
		add_subdirectory(PLVolumeLoaderPVM)
	endif()
	if(PL_PLUGIN_VOLUME_LOADER_DICOM_GDCM)
		add_subdirectory(PLVolumeLoaderDICOM_GDCM)
	endif()
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Plugins)
