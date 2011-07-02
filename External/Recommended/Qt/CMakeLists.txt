##################################################
## Project
##################################################
define_external_project(Qt)

##################################################
## INCLUDES AND LIBRARIES
##################################################
# [TODO] Systen libs possible for Qt?
#if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
#	find_package(QT)
#else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(QT_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/Qt/ CACHE INTERNAL "")
	if(WIN32)
		set(QT_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/QtCore4.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/QtGui4.lib CACHE INTERNAL "")
	elseif(LINUX)
		set(QT_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libQtCore4.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libQtGui4.so CACHE INTERNAL "")
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
# [TODO] Systen libs possible for Qt?
#endif()
