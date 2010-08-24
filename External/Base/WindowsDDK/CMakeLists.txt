##################################################
## Project
##################################################
define_external_project(WindowsDDK)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for WindowsDDK?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(WindowsDDK)
#	set(WINDOWSDDK_INCLUDE_DIRS ${WINDOWSDDK_INCLUDE_DIR_WINDOWSDDK} CACHE INTERNAL "")
#	set(WINDOWSDDK_LIBRARIES ${WINDOWSDDK_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Base ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(WINDOWSDDK_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(WINDOWSDDK_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/hid.lib CACHE INTERNAL "")
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

# [TODO] Systen libs possible for WindowsDDK?
#endif()
