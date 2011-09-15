#*********************************************************#
#*  File: FindOgg.cmake                                  *
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


# - Find Ogg
# Find the native Ogg includes and library
#
#  LIBOGG_INCLUDE_DIRS - where to find ogg.h, etc.
#  LIBOGG_LIBRARIES    - List of libraries when using libogg.

include (CheckLibraryExists)

find_path(LIBOGG_INCLUDE_DIRS ogg/ogg.h)

find_library(LIBOGG_LIBRARY NAMES ogg)

set(LIBOGG_LIBRARIES ${LIBOGG_LIBRARY} CACHE INTERNAL "")

# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Ogg  DEFAULT_MSG  LIBOGG_LIBRARY LIBOGG_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBOGG_LIBRARY LIBOGG_INCLUDE_DIRS)
