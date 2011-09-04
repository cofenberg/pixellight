##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Install.cmake)

##################################################
## Install
##################################################

# Check if built file exists
if(NOT EXISTS ${CMAKETOOLS_CURRENT_BUILT_FILE})
	# Copy libraries
	if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
		external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/projects/visualc71/Win32_LIB_Release/libpng.lib" "${CMAKETOOLS_CURRENT_LIB_DIR}/")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/.libs/libpng14.a" "${CMAKETOOLS_CURRENT_LIB_DIR}/libpng.a")
	endif()

	# Copy headers
	external_makedir("${CMAKETOOLS_CURRENT_INCLUDE_DIR}/png")
	external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/png.h" "${CMAKETOOLS_CURRENT_INCLUDE_DIR}/png/")
	external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/libpng-1.5.4/pngconf.h" "${CMAKETOOLS_CURRENT_INCLUDE_DIR}/png/")

	# Copy readme and license
	external_copy("${CMAKETOOLS_CURRENT_SOURCE_DIR}/Readme.txt" ${CMAKETOOLS_CURRENT_DEST_DIR})
	external_copy("${CMAKETOOLS_CURRENT_SOURCE_DIR}/LICENSE" ${CMAKETOOLS_CURRENT_DEST_DIR})

	# We're done, create the built file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILT_FILE} "")

	# Pack the result
	external_install_pack()
endif()

# Done
external_install_done()
