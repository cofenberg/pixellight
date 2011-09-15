#*********************************************************#
#*  File: FindSFK.cmake                                  *
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


# Find sfk (file command tools)
#
# Output variables:
#
#   SFK_FOUND      - set if sfk was found
#   SFK_EXECUTABLE - path to sfk executable

# Search for sfk
set(SFK_EXECUTABLE)
find_program(SFK_EXECUTABLE NAMES sfk.exe PATHS ${CMAKE_SOURCE_DIR}/cmake/UsedTools/sfk)
if(SFK_EXECUTABLE)
	set(SFK_FOUND ON)
else()
	set(SFK_FOUND OFF)
endif()

# Check if sfk has been found
message(STATUS "Looking for sfk...")
if(SFK_FOUND)
	message(STATUS "Looking for sfk... - found ${SFK_EXECUTABLE}")
else()
	message(STATUS "Looking for sfk... - NOT found")
endif()

# Mark variables as advanced
mark_as_advanced(SFK_EXECUTABLE SFK_FOUND)
