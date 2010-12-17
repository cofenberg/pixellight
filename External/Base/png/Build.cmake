##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Build.cmake)

##################################################
## Build
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Build project
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		# Build vcproj
		external_vcproj_build("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.4.5/projects/visualc71/libpng.vcproj" "LIB Release")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use make
		external_run_make2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.4.5")
	endif()
endif()

# Done
external_build_done()
