##################################################
## Project
##################################################
project(Pack)

##################################################
## Prerequisites
##################################################

# Create Packages directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Packages)

##################################################
## Target
##################################################
add_custom_target(Pack)
set_target_properties(Pack PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Packages
##################################################
include(Pack-SDK.cmake)
include(Pack-Runtime.cmake)
include(Pack-Docs.cmake)
