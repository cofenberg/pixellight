##################################################
## Project
##################################################
include(${CMAKETOOLS_DIR}/External/Clean.cmake)

##################################################
## Clean
##################################################

# Delete 'tinyxml.patch-win32'
if(CMAKETOOLS_TARGET_SYSTEM_WIN32)
	external_remove("${CMAKETOOLS_CURRENT_SOURCE_DIR}/Files/tinyxml.patch-win32")
endif()
