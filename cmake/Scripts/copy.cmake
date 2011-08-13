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
FILE(COPY ${COPY_SOURCE} DESTINATION ${COPY_DEST})

