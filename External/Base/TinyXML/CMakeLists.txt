##################################################
## Project
##################################################
define_external_project(TinyXML)
set(CMAKETOOLS_TINYXML_SYSTEM_LIB "0" CACHE BOOL "Use system libraries or build own external libraries?")

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_TINYXML_SYSTEM_LIB)
	##################################################
	## Use system libraries
	##################################################
	find_package(TinyXML)
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Base ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(TINYXML_INCLUDE_DIR ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/TinyXML CACHE INTERNAL "")
	if(WIN32)
		set(TINYXML_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/tinyxml.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(TINYXML_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libtinyxml.a CACHE INTERNAL "")
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
