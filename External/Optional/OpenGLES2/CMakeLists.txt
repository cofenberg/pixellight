##################################################
## Project
##################################################
define_external_project(OpenGLES2)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for OpenGL ES?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(OpenGLES2)
#	set(OPENGLES2_INCLUDE_DIRS ${OPENGLES2_INCLUDE_DIR_OPENGLES2} CACHE INTERNAL "")
#	set(OPENGLES2_LIBRARIES ${OPENGLES2_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(OPENGLES2_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(OPENGLES2_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libEGL.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/libGLESv2.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(OPENGLES2_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libEGL.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libGLESv2.so CACHE INTERNAL "")
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
