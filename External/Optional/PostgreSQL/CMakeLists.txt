##################################################
## Project
##################################################
define_external_project(PostgreSQL)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for PostgreSQL?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(POSTGRESQL)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(POSTGRESQL_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(POSTGRESQL_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libpq.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(POSTGRESQL_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libpq.a CACHE INTERNAL "")
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
# [TODO] System libs possible for PostgreSQL?
#endif()
