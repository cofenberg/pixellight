##################################################
## Project
##################################################
project(SDKTools)

##################################################
## Target
##################################################
add_custom_target(SDKTools)

##################################################
## Projects
##################################################
add_subdirectory(PLProject)
add_subdirectory(PLUpgrade)
if(WIN32)
	add_subdirectory(PLInstall)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight SDKTools)
