##################################################
## Project
##################################################
define_external_project(libjpg)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
	find_package(JPEG)
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Base ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(JPEG_INCLUDE_DIR ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/jpg CACHE INTERNAL "")
	if(WIN32)
		set(JPEG_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libjpeg.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(JPEG_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libjpeg.a CACHE INTERNAL "")
	endif()

	##################################################
	## Check
	##################################################
	external_check()

	# Check if built file exists
	if(NOT EXISTS "${CMAKETOOLS_CURRENT_EXT_DIR}/${CMAKETOOLS_CURRENT_NAME}/built")
		##################################################
		## Fetch
		##################################################
		external_fetch()
		
		##################################################
		## Configure
		##################################################
		external_configure()
		
		##################################################
		## Build
		##################################################
		external_build()
		
		##################################################
		## Install
		##################################################
		external_install()
	endif()

	##################################################
	## Clean
	##################################################
	external_clean()
endif()
