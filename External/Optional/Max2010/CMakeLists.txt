##################################################
## Project
##################################################
define_external_project(Max2010)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for Max2010?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(Max2010)
#	set(MAX2010_INCLUDE_DIRS ${MAX2010_INCLUDE_DIR_MAX2010} CACHE INTERNAL "")
#	set(MAX2010_LIBRARIES ${MAX2010_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(MAX2010_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(MAX2010_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/core.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/maxutil.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/bmm.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/geom.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/IGame.lib CACHE INTERNAL "")
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

# [TODO] Systen libs possible for Max2010?
#endif()
