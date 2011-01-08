##################################################
## Project
##################################################
define_external_project(OpenAL)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
	find_package(OpenAL)
	set(OPENAL_INCLUDE_DIRS ${OPENAL_INCLUDE_DIR} CACHE INTERNAL "")
	set(OPENAL_LIBRARIES ${OPENAL_LIBRARY} CACHE INTERNAL "")
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(OPENAL_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(OPENAL_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/OpenAL32.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(OPENAL_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libopenal.so CACHE INTERNAL "")
	endif()

	##################################################
	## Check
	##################################################
	external_check()

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

	##################################################
	## Clean
	##################################################
	external_clean()
endif()
