#*********************************************************#
#*  File: copy.cmake                                     *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the “Software”), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


# Helper script to copy files to a specific destination. This is required in order to copy symlinks under Linux as symlinks (cmake -E copy doesn't copy symlinks as symlinks).

# Background: When the FILE command is listed in a "CMakeLists.txt"-file, the command is executed immediately as soon as CMake is parsing the "CMakeLists.txt"-file.
# Therefore, we have to put this command into a separate CMake script to enable the call at a specific moment.

# To use this script, put the following code in a "CMakeLists.txt"-file which should use this script:
#	# Set COPY_SOURCE to files which should be copied (this variable is used by the "copy.cmake"-script)
#	set(COPY_SOURCE <FilePaths to copy>)
#	# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied into (this variable is used by the "copy.cmake"-script)
#	set(COPY_DEST <Destination>)
#	# Create a concrete CMake script file which can be executed from CMake
#	configure_file(<Path to this file> <DestinationPath>/<filename>) # e.g. the destination can be the build output directory
#	# Add custom command to call the created file after target was built
#	add_custom_command(TARGET <TargetName> COMMAND ${CMAKE_COMMAND} -P <DestinationPath>/<filename>)
# If the generated file is located in the build output directory you can simple use the filename as argument for the -P parameter.
file(COPY ${COPY_SOURCE} DESTINATION ${COPY_DEST})

