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
# PLGraphics image formats
if(PL_PLUGIN_GRAPHICS_PNG)
	add_subdirectory(png)
endif()
if(PL_PLUGIN_GRAPHICS_JPG)
	add_subdirectory(jpg)
endif()
# Script backends
if(PL_PLUGIN_SCRIPT_LUA)
	add_subdirectory(Lua)
endif()
# PLRenderer backends
if(PL_PLUGIN_RENDERER_OPENGL)
	add_subdirectory(OpenGL)
endif()
if(APL_PLUGIN_RENDERER_OPENGL AND PL_PLUGIN_RENDERER_OPENGL_FONT) OR (PL_PLUGIN_RENDERER_OPENGLES2 AND PL_PLUGIN_RENDERER_OPENGLES2_FONT))
	add_subdirectory(freetype)
endif()
# PLPhysics backends
if(PL_PLUGIN_PHYSICS_NEWTON)
	add_subdirectory(Newton)
endif()
# PLSound backends
if(PL_PLUGIN_SOUND_OPENAL)
	add_subdirectory(OpenAL)
	add_subdirectory(libogg)
	add_subdirectory(libvorbis)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(External External-Recommended)
