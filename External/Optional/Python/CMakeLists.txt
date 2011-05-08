##################################################
## Project
##################################################
define_external_project(Python)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for Python?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(PYTHON)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(PYTHON_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(PYTHON_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/python27.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(PYTHON_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libpython2.7.a CACHE INTERNAL "")
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
# [TODO] Systen libs possible for Python?
#endif()
