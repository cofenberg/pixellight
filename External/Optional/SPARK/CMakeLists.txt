##################################################
## Project
##################################################
define_external_project(SPARK)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for SPARK?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(SPARK)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(SPARK_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(SPARK_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/SPARK.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(SPARK_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libSPARK_Engine_Core.a CACHE INTERNAL "")
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
# [TODO] Systen libs possible for SPARK?
#endif()
