##################################################
## Project
##################################################
define_external_project(AngelScript)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for AngelScript?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(ANGELSCRIPT)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(ANGELSCRIPT_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(ANGELSCRIPT_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/angelscript.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(ANGELSCRIPT_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libangelscript.a CACHE INTERNAL "")
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
# [TODO] Systen libs possible for AngelScript?
#endif()
