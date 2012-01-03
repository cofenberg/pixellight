#*********************************************************#
#*  File: FindVorbis.cmake                               *
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


# - Find Vorbis
# Find the native Vorbis includes and library
#
#  LIBVORBIS_INCLUDE_DIRS - where to find vorbisfile.h, etc.
#  LIBVORBIS_LIBRARIES   - List of libraries when using libvorbis.

include (CheckLibraryExists)

find_path(LIBVORBIS_INCLUDE_DIRS vorbis/vorbisfile.h)
find_library(LIBVORBIS_LIBRARY NAMES vorbis)
find_library(LIBVORBISFILE_LIBRARY NAMES vorbisfile)

set(LIBVORBIS_LIBRARIES ${LIBVORBIS_LIBRARY} ${LIBVORBISFILE_LIBRARY} CACHE INTERNAL "")

# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Vorbis  DEFAULT_MSG  LIBVORBIS_LIBRARIES LIBVORBIS_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBVORBIS_LIBRARIES LIBVORBIS_INCLUDE_DIRS)

