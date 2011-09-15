#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#*********************************************************#


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
if((PL_PLUGIN_RENDERER_OPENGL AND PL_PLUGIN_RENDERER_OPENGL_FONT) OR (PL_PLUGIN_RENDERER_OPENGLES2 AND PL_PLUGIN_RENDERER_OPENGLES2_FONT))
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
