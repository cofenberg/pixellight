##################################################
## Project
##################################################
define_external_project(FMODEx)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for FMODEx?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(FMODEx)
#	set(FMODEX_INCLUDE_DIRS ${FMODEX_INCLUDE_DIR_FMODEX} CACHE INTERNAL "")
#	set(FMODEX_LIBRARIES ${FMODEX_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(FMODEX_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(FMODEX_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/fmodex_vc.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(FMODEX_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libfmodex.so CACHE INTERNAL "")
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

# [TODO] System libs possible for FMODEx?
#endif()
