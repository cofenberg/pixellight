##################################################
## Project
##################################################
define_external_project(Qt)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	##################################################
	## Use system libraries
	##################################################
	# [TODO] Doesn't work when because the additional include paths gets added directly via the include_directories makro
	# when using QT_USE_FILE. Currently the Projects which needs Qt uses find_package(Qt4) and INCLUDE(${QT_USE_FILE}) directly when
	# CMAKETOOLS_USE_SYSTEM_LIBS is set
# 	find_package(Qt4)
# 	SET(QT_USE_QTGUI 1)
# 	# Add Qt CMake macros and variables
# 	# (QT_USE_FILE is a variable defined by FIND_PACKAGE(Qt4) that contains a path to CMake script)
# 	INCLUDE(${QT_USE_FILE})
# 	
# 	# The find module from cmake itself doesn't add the XXX_LIBRARIES var and XXX_INCLUDE_DIR var to the cache, which is the correct behaviour.
# 	# This vars should normaly only be visible within the cmake file in which the find module was called.
# 	# Otherwise the vars would be visible for all other projects if wanted or not
# 	# We want this, because this vars are used in other cmake files, which doesn't include this file, so we add the vars to the cache
# 	set(QT_LIBRARIES ${QT_LIBRARIES} CACHE INTERNAL "")
# 	set(QT_INCLUDE_DIRS ${QT_INCLUDES} CACHE INTERNAL "")
else()
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
endif()
