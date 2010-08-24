##################################################
## Project
##################################################
define_external_project(DirectX9)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for DirectX9?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(DirectX9)
#	set(DIRECTX9_INCLUDE_DIRS ${DIRECTX9_INCLUDE_DIR_DIRECTX9} CACHE INTERNAL "")
#	set(DIRECTX9_LIBRARIES ${DIRECTX9_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(DIRECTX9_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(DIRECTX9_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/d3d9.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/d3dx9.lib CACHE INTERNAL "")
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

# [TODO] Systen libs possible for DirectX 9?
#endif()
