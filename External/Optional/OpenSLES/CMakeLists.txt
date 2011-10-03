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
define_external_project(OpenSLES)

##################################################
## INCLUDES AND LIBRARIES
##################################################

# Build external
message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

##################################################
## Build external
##################################################
add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)

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
