##################################################
## Project
##################################################
project(External)

##################################################
## Target
##################################################
add_custom_target(External)
set_target_properties(External PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)
add_custom_target(External-Clean)
set_target_properties(External-Clean PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Projects
##################################################
add_subdirectory(Base)
add_subdirectory(Recommended)
add_subdirectory(Optional)

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight External)
