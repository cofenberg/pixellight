##################################################
## Project
##################################################
define_external_project(Lua)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for Lua?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(LUA)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(LUA_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(LUA_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/lua51.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(LUA_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/liblua.a CACHE INTERNAL "")
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
# [TODO] Systen libs possible for Lua?
#endif()
