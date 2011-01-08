##################################################
## Project
##################################################
define_external_project(xulrunnersdk)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for xulrunnersdk?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(XULRUNNERSDK)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(XULRUNNERSDK_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/plugin ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/nspr ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/java CACHE INTERNAL "")

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
# [TODO] Systen libs possible for xulrunnersdk?
#endif()
