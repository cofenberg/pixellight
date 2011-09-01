##################################################
## Project
##################################################
define_external_project(PhysX)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] System libs possible for PhysX?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(PhysX)
#	set(PHYSX_INCLUDE_DIRS ${PHYSX_INCLUDE_DIR_PHYSX} CACHE INTERNAL "")
#	set(PHYSX_LIBRARIES ${PHYSX_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(PHYSX_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/PhysX/Foundation/include ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/PhysX/Physics/include ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/PhysX/PhysXLoader/include CACHE INTERNAL "")
	if(WIN32)
		set(PHYSX_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/PhysXLoader.lib CACHE INTERNAL "")
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

# [TODO] System libs possible for PhysX?
#endif()
