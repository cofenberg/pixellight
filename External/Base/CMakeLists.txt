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
add_subdirectory(pcre)
if(PL_CORE_ZIP OR PL_PLUGIN_GRAPHICS_PNG)
	# It's highly recommended to enable ZIP support
	add_subdirectory(zlib)
endif()
if(WIN32)
	add_subdirectory(VC2010)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(External External-Base)
