##################################################
## Project
##################################################
define_external_project(FMOD)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for FMOD?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(FMOD)
#	set(FMOD_INCLUDE_DIRS ${FMOD_INCLUDE_DIR_FMOD} CACHE INTERNAL "")
#	set(FMOD_LIBRARIES ${FMOD_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(FMOD_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(FMOD_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/fmodvc.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(FMOD_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libfmod-3.75.so CACHE INTERNAL "")
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

# [TODO] System libs possible for FMOD?
#endif()
