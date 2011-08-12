# helper script to copy files to a specific destination
# This is needed to copy symlinks under linux as symlinks. (cmake -E copy doesn't copy symlinks as symlinks)
# This command is put into a separate cmake script so that it can called to a specific moment
# because if the FILE command is listed in a CMakeLists.txt this command is immediately executed when the CmakeLists.txt is parsed from cmake
# To use this script put following code in a CMakeLists.txt which should use this script:
#	# Set COPY_SOURCE to files which should be copied. This var is used by the copy.cmake script
#	set(COPY_SOURCE <FilePaths to copy>)
#	# Set COPY_DEST to a directory to which the files in COPY_SOURCE should be copied. This var is used by the copy.cmake script
#	set(COPY_DEST <Destination>)
#	# create concrete cmake script file which can be executed from cmake
#	configure_file(<Path to this file> <DestinationPath>/<filename>) # e.g. the destination can be the build output directory
#	# add custom command to call the created after target was built
#	add_custom_command(TARGET <TargetName> COMMAND ${CMAKE_COMMAND} -P <DestinationPath>/<filename>)
# if the generated file is located in the build output directory you can simple use the filename as argument for the -P parameter
FILE(COPY ${COPY_SOURCE} DESTINATION ${COPY_DEST})