##################################################
## Project
##################################################
project(Base)

##################################################
## Target
##################################################
add_custom_target(Base)

##################################################
## Projects
##################################################
add_subdirectory(PLGeneral)
add_subdirectory(PLCore)
add_subdirectory(PLGraphics)
add_subdirectory(PLMath)
add_subdirectory(PLDatabase)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Base)
