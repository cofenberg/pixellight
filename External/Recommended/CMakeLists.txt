##################################################
## Project
##################################################
project(External-Recommended)

##################################################
## Target
##################################################
add_custom_target(External-Recommended)

##################################################
## Projects
##################################################
add_subdirectory(OpenGL)
add_subdirectory(freetype)
add_subdirectory(OpenAL)
add_subdirectory(libogg)
add_subdirectory(libvorbis)
add_subdirectory(Newton)
add_subdirectory(Bullet)
add_subdirectory(Lua)
add_subdirectory(Qt)

##################################################
## Dependencies
##################################################
add_dependencies(External External-Recommended)
