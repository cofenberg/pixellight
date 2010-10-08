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
add_subdirectory(TinyXML)
add_subdirectory(zlib)

##################################################
## Dependencies
##################################################
add_dependencies(External External-Base)
