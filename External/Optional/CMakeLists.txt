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
add_subdirectory(FMOD)
add_subdirectory(FMODEx)
add_subdirectory(Assimp)
add_subdirectory(OpenEXR)
add_subdirectory(xulrunnersdk)
add_subdirectory(SQLite)
add_subdirectory(PostgreSQL)
add_subdirectory(MySQL)
add_subdirectory(Bullet)
add_subdirectory(ODE)
add_subdirectory(OpenGLES2)
add_subdirectory(Cg)
add_subdirectory(Qt)
add_subdirectory(libRocket)
add_subdirectory(V8)
add_subdirectory(Python)
add_subdirectory(AngelScript)
if(WIN32)
	add_subdirectory(DirectX9)
	add_subdirectory(DirectX11)
	add_subdirectory(PhysX)
	add_subdirectory(Max2008)
	add_subdirectory(Max2009)
	add_subdirectory(Max2010)
	add_subdirectory(Max2011)
	add_subdirectory(Max2012)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(External External-Optional)
