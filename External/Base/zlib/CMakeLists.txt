##################################################
## Project
##################################################
define_external_project(zlib)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# Android hasn't that many public shared libraries on it's system, but zlib is there, so do always use the system version to save memory
# (just in case you may say "Why the heck don't you use "CMAKETOOLS_USE_SYSTEM_LIBS" in the first place?" -> right now, "CMAKETOOLS_USE_SYSTEM_LIBS"
#  means "use system library or just fail", to fail is no option just because we want to use this single system library in here... maybe when
#  using "CMAKETOOLS_USE_SYSTEM_LIBS" there should be a fallback in case there's no such system library?)
if(CMAKETOOLS_USE_SYSTEM_LIBS OR ANDROID)
	##################################################
	## Use system libraries
	##################################################
	find_package(ZLIB)

	# The find module from cmake itself doesn't add the XXX_LIBRARIES var and XXX_INCLUDE_DIR var to the cache, which is the correct behaviour.
	# This vars should normaly only be visible within the cmake file in which the find module was called.
	# Otherwise the vars would be visible for all other projects if wanted or not
	# We want this, because this vars are used in other cmake files, which doesn't include this file, so we add the vars to the cache
	set(ZLIB_LIBRARIES ${ZLIB_LIBRARIES} CACHE INTERNAL "")
	set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR} CACHE INTERNAL "")
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Base ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(ZLIB_INCLUDE_DIR ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/zlib CACHE INTERNAL "")
	if(WIN32)
		set(ZLIB_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/zlib.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(ZLIB_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libz.a CACHE INTERNAL "")
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
endif()
