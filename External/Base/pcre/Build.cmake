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
		external_run_nmake("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/pcre-8.12/Makefile" "${CMAKETOOLS_CURRENT_BUILD_DIR}/build/pcre-8.12" "pcre")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		external_run_make2("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/pcre-8.12")
	endif()
endif()

# Done
external_build_done()
