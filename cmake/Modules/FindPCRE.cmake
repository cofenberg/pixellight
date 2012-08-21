#*********************************************************#
#*  File: FindPCRE.cmake                                 *
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


# - Find PCRE
# Find the native PCRE includes and library
#
#  PCRE_INCLUDE_DIR - where to find pcre.h, etc.
#  PCRE_LIBRARIES   - List of libraries when using libpcre.
#  PCRE_FOUND       - True if pcre found.

if(PCRE_INCLUDE_DIR)
  # Already in cache, be silent
  set(PCRE_FIND_QUIETLY TRUE)
endif(PCRE_INCLUDE_DIR)

find_path(PCRE_INCLUDE_DIR pcre.h)

if(UNIX)
  set(PCRE_NAMES pcre pcreposix)
else()
  set(PCRE_NAMES pcre libpcre)
endif()
find_library(PCRE_LIBRARY NAMES ${PCRE_NAMES} )

# handle the QUIETLY and REQUIRED arguments and set PCRE_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCRE DEFAULT_MSG PCRE_LIBRARY PCRE_INCLUDE_DIR)

if(PCRE_FOUND)
  set(PCRE_LIBRARIES ${PCRE_LIBRARY} CACHE INTERNAL "")
else(PCRE_FOUND)
  set(PCRE_LIBRARIES CACHE INTERNAL "")
endif(PCRE_FOUND)

mark_as_advanced(PCRE_LIBRARY PCRE_INCLUDE_DIR)
