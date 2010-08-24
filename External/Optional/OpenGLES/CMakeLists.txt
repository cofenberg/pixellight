##################################################
## Project
##################################################
define_external_project(OpenGLES)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for OpenGL ES?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(OpenGLES)
#	set(OPENGLES_INCLUDE_DIRS ${OPENGLES_INCLUDE_DIR_OPENGLES} CACHE INTERNAL "")
#	set(OPENGLES_LIBRARIES ${OPENGLES_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(OPENGLES_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(OPENGLES_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libEGL.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/libGLESv2.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(OPENGLES_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libEGL.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libGLESv2.so CACHE INTERNAL "")
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

# [TODO] Systen libs possible for OpenGL ES?
#endif()
