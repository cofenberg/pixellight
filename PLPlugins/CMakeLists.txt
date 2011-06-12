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
add_subdirectory(PLScriptBindings)
if(PL_PLUGIN_ENGINE_DEFAULTFF)
	add_subdirectory(PLDefaultFileFormats)
endif()
if(PL_PLUGIN_ENGINE_PARTICLEGROUPS)
	add_subdirectory(PLParticleGroups)
endif()
if(PL_PLUGIN_ENGINE_SPARK)
	add_subdirectory(SPARK_PL)
endif()
if(PL_PLUGIN_ENGINE_LIBROCKET)
	add_subdirectory(libRocket_PL)
endif()
if(PL_PLUGIN_ENGINE_POSTPROCESS)
	add_subdirectory(PLPostProcessEffects)
endif()
# PLScript backends
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
if(PL_PLUGIN_PHYSICS_PHYSX AND WIN32)
	add_subdirectory(PLPhysicsPhysX)
endif()
# PLSound backends
if(PL_PLUGIN_SOUND_NULL)
	add_subdirectory(PLSoundNull)
endif()
if(PL_PLUGIN_SOUND_OPENAL)
	add_subdirectory(PLSoundOpenAL)
endif()
if(PL_PLUGIN_SOUND_FMOD)
	add_subdirectory(PLSoundFMOD)
endif()
if(PL_PLUGIN_SOUND_FMODEX)
	add_subdirectory(PLSoundFMODEx)
endif()

# Currently only for windows
if(WIN32)
	add_subdirectory(PLPlugin)
	if(PL_PLUGIN_ENGINE_IMAGEEXR)
		add_subdirectory(PLImageLoaderEXR)
	endif()
	if(PL_BROWSER_PLUGIN_ACTIVEX)
		add_subdirectory(PLPluginActiveX)
	endif()
	if(PL_BROWSER_PLUGIN_MOZILLA)
		add_subdirectory(PLPluginMozilla)
	endif()
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Plugins)
