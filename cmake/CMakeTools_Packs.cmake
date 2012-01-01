#*********************************************************#
#*  File: CMakeTools_Packs.cmake                         *
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
## CMakeTools packages
##
## These macros can be used to build packages
## of your project
##################################################


##################################################
## CMakeTools packages initialization 
##################################################

# Reset CPack configuration
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
	set(CPACK_IGNORE_FILES "")
	set(CPACK_INSTALLED_DIRECTORIES "")
	set(CPACK_SOURCE_IGNORE_FILES "")
	set(CPACK_SOURCE_INSTALLED_DIRECTORIES "")
	set(CPACK_STRIP_FILES "")
	set(CPACK_SOURCE_TOPLEVEL_TAG "")
	set(CPACK_SOURCE_PACKAGE_FILE_NAME "")
endif()

# Find cpack executable
get_filename_component(CPACK_PATH ${CMAKE_COMMAND} PATH)
set(CPACK_COMMAND "${CPACK_PATH}/cpack")
