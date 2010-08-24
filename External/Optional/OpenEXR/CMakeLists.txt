##################################################
## Project
##################################################
define_external_project(OpenEXR)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for OpenEXR?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(OPENEXR)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Optional ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	if(WIN32)
		if(MSVC71)
			set(VC_SUFFIX "VC7")
		else()
			set(VC_SUFFIX "VC8")
		endif()
		set(OPENEXR_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../${VC_SUFFIX}/include ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../${VC_SUFFIX}/include/Iex ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../${VC_SUFFIX}/include/IlmImf ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/../${VC_SUFFIX}/include/Imath CACHE INTERNAL "")
		set(OPENEXR_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/../${VC_SUFFIX}/lib/zlib.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../${VC_SUFFIX}/lib/Half.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../${VC_SUFFIX}/lib/Iex.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../${VC_SUFFIX}/lib/Imath.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../${VC_SUFFIX}/lib/IlmImf.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/../${VC_SUFFIX}/lib/IlmThread.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(OPENEXR_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR} CACHE INTERNAL "")
		set(OPENEXR_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libz.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libHalf.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libIex.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libImath.a ${CMAKETOOLS_CURRENT_LIB_DIR}/libIlmImf.a CACHE INTERNAL "")
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
# [TODO] Systen libs possible for OpenEXR?
#endif()
