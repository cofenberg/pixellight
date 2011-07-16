##################################################
## Project
##################################################
project(External-Base)

##################################################
## Target
##################################################
add_custom_target(External-Base)

##################################################
## Projects
##################################################
add_subdirectory(jpg)
add_subdirectory(pcre)
add_subdirectory(png)
add_subdirectory(zlib)
if(WIN32)
	add_subdirectory(VC2010)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(External External-Base)
