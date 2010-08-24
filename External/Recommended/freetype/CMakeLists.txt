##################################################
## Project
##################################################
define_external_project(freetype)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
	find_package(Freetype)
	set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR_freetype2} ${FREETYPE_INCLUDE_DIR_ft2build} CACHE INTERNAL "")
	set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY} CACHE INTERNAL "")
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(FREETYPE_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(FREETYPE_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libfreetype.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(FREETYPE_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libfreetype.a CACHE INTERNAL "")
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
