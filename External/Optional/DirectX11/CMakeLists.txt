##################################################
## Project
##################################################
define_external_project(DirectX11)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for DirectX11?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(DirectX11)
#	set(DIRECTX11_INCLUDE_DIRS ${DIRECTX11_INCLUDE_DIR_DIRECTX11} CACHE INTERNAL "")
#	set(DIRECTX11_LIBRARIES ${DIRECTX11_LIBRARY} CACHE INTERNAL "")
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(DIRECTX11_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(DIRECTX11_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/dxgi.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/d3d11.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/d3dx11.lib CACHE INTERNAL "")
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

# [TODO] Systen libs possible for DirectX 11?
#endif()
