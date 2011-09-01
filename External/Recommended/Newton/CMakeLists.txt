##################################################
## Project
##################################################
define_external_project(Newton)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for Newton?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(Newton)
#	set(NEWTON_INCLUDE_DIRS ${NEWTON_INCLUDE_DIR_NEWTON} CACHE INTERNAL "")
#	set(NEWTON_LIBRARIES ${NEWTON_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(NEWTON_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(NEWTON_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/newton.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(NEWTON_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libNewton.so CACHE INTERNAL "")
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

# [TODO] System libs possible for Newton?
#endif()
