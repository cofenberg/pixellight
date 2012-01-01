#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
