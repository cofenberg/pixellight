##################################################
## Project
##################################################
define_external_project(OpenGLES2)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# No need for system libraries because we dynamically linking at runtime against the EGL and OpenGL ES 2.0 dynamic libraries

# Build external
message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

##################################################
## Build external
##################################################
add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)

# No need for OPENGLES2_INCLUDE_DIRS or OPENGLES2_LIBRARIES

##################################################
## Check
##################################################
external_check()

##################################################
## Fetch
##################################################
external_fetch()

##################################################
## Configure
##################################################
external_configure()

##################################################
## Build
##################################################
external_build()

##################################################
## Install
##################################################
external_install()

##################################################
## Clean
##################################################
external_clean()
