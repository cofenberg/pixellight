##################################################
## Project
##################################################
project(External-Optional)

##################################################
## Target
##################################################
add_custom_target(External-Optional)

##################################################
## Projects
##################################################
if(PL_PLUGIN_ENGINE_ASSIMP)
	add_subdirectory(Assimp)
endif()
if(PL_PLUGIN_ENGINE_IMAGEEXR)
	add_subdirectory(OpenEXR)
endif()
if(PL_PLUGIN_ENGINE_LIBROCKET)
	add_subdirectory(libRocket)
endif()
# Script backends
if(PL_PLUGIN_SCRIPT_V8)
	add_subdirectory(V8)
endif()
if(PL_PLUGIN_SCRIPT_PYTHON)
	add_subdirectory(Python)
endif()
if(PL_PLUGIN_SCRIPT_ANGELSCRIPT)
	add_subdirectory(AngelScript)
endif()
# Frontend backends
if(PL_PLUGIN_FRONTEND_QT)
	add_subdirectory(Qt)
endif()
if(PL_PLUGIN_FRONTEND_MOZILLA)
	add_subdirectory(xulrunnersdk)
endif()
# PLDatabase backends
if(PL_PLUGIN_DATABASE_MYSQL)
	add_subdirectory(MySQL)
endif()
if(PL_PLUGIN_DATABASE_POSTGRESQL)
	add_subdirectory(PostgreSQL)
endif()
if(PL_PLUGIN_DATABASE_SQLITE)
	add_subdirectory(SQLite)
endif()
# PLRenderer backends
if(PL_PLUGIN_RENDERER_OPENGL AND PL_PLUGIN_RENDERER_OPENGLCG)
	add_subdirectory(Cg)
endif()
if(PL_PLUGIN_RENDERER_OPENGLES2)
	add_subdirectory(OpenGLES2)
endif()
if(PL_PLUGIN_RENDERER_D3D9)
	add_subdirectory(DirectX9)
endif()
if(PL_PLUGIN_RENDERER_D3D11)
	add_subdirectory(DirectX11)
endif()
# PLPhysics backends
if(PL_PLUGIN_PHYSICS_ODE)
	add_subdirectory(ODE)
endif()
if(PL_PLUGIN_PHYSICS_PHYSX)
	add_subdirectory(PhysX)
endif()
if(PL_PLUGIN_PHYSICS_BULLET)
	add_subdirectory(Bullet)
endif()
# PLSound backends
if(PL_PLUGIN_SOUND_FMOD)
	add_subdirectory(FMOD)
endif()
if(PL_PLUGIN_SOUND_FMODEX)
	add_subdirectory(FMODEx)
endif()
# Tools
if(PL_EXPORTER_3DSMAX_2008)
	add_subdirectory(Max2008)
endif()
if(PL_EXPORTER_3DSMAX_2009)
	add_subdirectory(Max2009)
endif()
if(PL_EXPORTER_3DSMAX_2010)
	add_subdirectory(Max2010)
endif()
if(PL_EXPORTER_3DSMAX_2011)
	add_subdirectory(Max2011)
endif()
if(PL_EXPORTER_3DSMAX_2012)
	add_subdirectory(Max2012)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(External External-Optional)
