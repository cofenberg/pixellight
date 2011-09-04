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
		external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/libjpeg.lib" "${CMAKETOOLS_CURRENT_LIB_DIR}/")
	elseif(CMAKETOOLS_TARGET_SYSTEM_LINUX)
		external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/.libs/libjpeg.a" "${CMAKETOOLS_CURRENT_LIB_DIR}/")
	endif()

	# Copy headers
	external_makedir("${CMAKETOOLS_CURRENT_INCLUDE_DIR}/jpg")
	external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/jconfig.h" "${CMAKETOOLS_CURRENT_INCLUDE_DIR}/jpg/")
	external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/jmorecfg.h" "${CMAKETOOLS_CURRENT_INCLUDE_DIR}/jpg/")
	external_copy("${CMAKETOOLS_CURRENT_BUILD_DIR}/build/jpeg-8c/jpeglib.h" "${CMAKETOOLS_CURRENT_INCLUDE_DIR}/jpg/")

	# Copy readme and license
	external_copy("${CMAKETOOLS_CURRENT_SOURCE_DIR}/Readme.txt" ${CMAKETOOLS_CURRENT_DEST_DIR})
	external_copy("${CMAKETOOLS_CURRENT_SOURCE_DIR}/license.txt" ${CMAKETOOLS_CURRENT_DEST_DIR})

	# We're done, create the built file
	file(WRITE ${CMAKETOOLS_CURRENT_BUILT_FILE} "")

	# Pack the result
	external_install_pack()
endif()

# Done
external_install_done()
