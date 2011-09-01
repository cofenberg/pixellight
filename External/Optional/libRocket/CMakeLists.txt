##################################################
## Project
##################################################
define_external_project(libRocket)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for libRocket?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(LIBROCKT)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(LIBROCKET_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(LIBROCKET_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/RocketCore.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/RocketControls.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/RocketDebugger.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(LIBROCKET_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libRocketCore.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libRocketControls.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libRocketDebugger.so CACHE INTERNAL "")
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
# [TODO] System libs possible for libRocket?
#endif()
