##################################################
## Project
##################################################
define_external_project(Bullet)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for Bullet?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(BULLET)
#	set(BULLET_INCLUDE_DIRS ${BULLET_INCLUDE_DIR_BULLET} CACHE INTERNAL "")
#	set(BULLET_LIBRARIES ${BULLET_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(BULLET_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/Bullet CACHE INTERNAL "")
	if(WIN32)
		set(BULLET_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/BulletDynamics.lib
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/BulletCollision.lib
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/LinearMath.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(BULLET_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libBulletDynamics.a
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/libBulletCollision.a
							 ${CMAKETOOLS_CURRENT_LIB_DIR}/libLinearMath.a CACHE INTERNAL "")
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

# [TODO] System libs possible for Newton?
#endif()
