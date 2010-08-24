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
add_subdirectory(DirectX9)
add_subdirectory(FMOD)
add_subdirectory(FMODEx)
add_subdirectory(PhysX)
add_subdirectory(Max2008)
add_subdirectory(Max2009)
add_subdirectory(Max2010)
add_subdirectory(lib3ds)
add_subdirectory(OpenEXR)
add_subdirectory(xulrunnersdk)
add_subdirectory(SQLite)
add_subdirectory(PostgreSQL)
add_subdirectory(MySQL)
add_subdirectory(ODE)
add_subdirectory(OpenGLES)

##################################################
## Dependencies
##################################################
add_dependencies(External External-Optional)
