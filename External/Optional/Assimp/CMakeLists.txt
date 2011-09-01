##################################################
## Project
##################################################
define_external_project(Assimp)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for Assimp?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(ASSIMP)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(ASSIMP_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(ASSIMP_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/assimp.lib CACHE INTERNAL "")
	elseif(LINUX)
		# Under Linux, only a dynamic library is currently buildable by the build system of Assimp
		set(ASSIMP_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libassimp.so CACHE INTERNAL "")
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
# [TODO] System libs possible for Assimp?
#endif()
