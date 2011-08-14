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
		# Use nmake
		external_run_nmake2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/freetype-2.4.6")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		# Use make
		external_run_make2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/freetype-2.4.6")
	endif()
endif()

# Done
external_build_done()
