##################################################
## Project
##################################################
define_external_project(libvorbis)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
	find_package(Vorbis)
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(LIBVORBIS_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
	if(WIN32)
		set(LIBVORBIS_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/vorbis_static.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/vorbisfile_static.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(LIBVORBIS_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libvorbis.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libvorbisfile.so CACHE INTERNAL "")
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
