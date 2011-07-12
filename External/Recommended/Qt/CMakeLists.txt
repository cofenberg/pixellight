##################################################
## Project
##################################################
define_external_project(Qt)

##################################################
## INCLUDES AND LIBRARIES
##################################################
if(CMAKETOOLS_USE_SYSTEM_LIBS)
	# remove some Qt related variables from the cache
	# Without removing the variables from the cache FindQt4 won't search e.g. for the qmake again. But this is necessary when toggeling the CMAKETOOLS_USE_SYSTEM_LIBS variable
	# otherwise not the qmake and Qt libs are selected which are installed system wide.
	unset(QT_QMAKE_EXECUTABLE CACHE)
	unset(QT_LIBRARIES CACHE)
	unset(QT_INCLUDE_DIRS CACHE)
	unset(QT_BINARY_DIR CACHE)
	unset(QT_LIBRARY_DIR CACHE)
	##################################################
	## Use system libraries
	##################################################
	find_package(Qt4 REQUIRED)
	
	include(${QT_USE_FILE})
	
	# The find module from cmake itself doesn't add the XXX_LIBRARIES variable and XXX_INCLUDE_DIR variable to the cache, which is the correct behaviour.
	# This variables should normaly only be visible within the cmake file in which the find module was called.
	# Otherwise the variables would be visible for all other projects if wanted or not.
	# We want this, because this variables are used in other cmake files, which doesn't include this file, so we add the variables to the cache.
 	set(QT_LIBRARIES ${QT_LIBRARIES} CACHE INTERNAL "")
 	set(QT_INCLUDE_DIRS ${QT_INCLUDE_DIR} CACHE INTERNAL "")
else()
	# Build external
	message(STATUS "Using build script for external '${CMAKETOOLS_CURRENT_NAME}'")

	get_filename_component(QT_EXTERNAL_ABS "${CMAKETOOLS_CURRENT_LIB_DIR}/.." ABSOLUTE )
	set(QT_EXTERNAL_DIR ${QT_EXTERNAL_ABS} CACHE INTERNAL "")
	
	# Directory for Qt stuff directly within PL's Git repository
	set(LOCAL_QT_DIR "${CMAKE_SOURCE_DIR}/External/Recommended/Qt/${CMAKETOOLS_CONFIG_NAME}_${CMAKETOOLS_TARGET_ARCH}" CACHE INTERNAL "")

	##################################################
	## Build external
	##################################################
	add_dependencies(External-Recommended ${CMAKETOOLS_CURRENT_TARGET})
	add_dependencies(External-Clean ${CMAKETOOLS_CURRENT_TARGET}-Clean)
	set(QT_INCLUDE_DIRS ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/Qt/QtCore ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/Qt/QtGui ${CMAKETOOLS_CURRENT_INCLUDE_DIR}/Qt CACHE INTERNAL "")

	if(WIN32)
		set(QT_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/QtCore4.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/QtGui4.lib ${CMAKETOOLS_CURRENT_LIB_DIR}/qtmain.lib CACHE INTERNAL "")

		# Set "FindQt4.cmake"-variables
		set(QT_QMAKE_EXECUTABLE ${LOCAL_QT_DIR}/qmake.exe)	# Tell Qt were to find qmake
	elseif(LINUX)
		set(QT_LIBRARIES ${CMAKETOOLS_CURRENT_LIB_DIR}/libQtCore.so ${CMAKETOOLS_CURRENT_LIB_DIR}/libQtGui.so CACHE INTERNAL "")

		# Set "FindQt4.cmake"-variables
		set(QT_QMAKE_EXECUTABLE ${LOCAL_QT_DIR}/qmake)	# Tell Qt were to find qmake
	endif()

	# Set "FindQt4.cmake"-variables
	
	# unset QT_QMAKE_EXECUTABLE_LAST otherwise FindQt4.cmake triggers an query to qmake for the Qt library path.
	# The Qt library path is hardcoded into qmake, but we can't relay on the reported path of qmake because the harcoded path is absolut
	# and will always not match with the location of the Qt libs which are bundled with Pixellight as an External package
	unset(QT_QMAKE_EXECUTABLE_LAST CACHE)
	
	# We have to set following variables otherwise the FindQt4.cmake won't find either the executables uic, rcc, moc and the qt library path
	# The QT_INCLUDE_DIR path has also be set, because this var is an additional condition that FindQt4.cmake sets QT_FOUND to true
	set(QT_INCLUDE_DIR	${QT_EXTERNAL_DIR}/include/							)	# Path to "include" of Qt4
	set(QT_BINARY_DIR 	${LOCAL_QT_DIR}/									)	# Path to "bin" of Qt4
	set(QT_LIBRARY_DIR	${QT_EXTERNAL_DIR}/lib/								)	# Path to "lib" of Qt4
	# We have to set both QT_QTCORE_LIBRARY and QT_QTCORE_LIBRARY_RELEASE (we could also set QT_QTCORE_LIBRARY_DEBUG instead of QT_QTCORE_LIBRARY_RELEASE).
	# QT_QTCORE_LIBRARY is used to determine if qmake should be queried for the library path to the Qt libs (which has the problems described above why unsetting QT_QMAKE_EXECUTABLE_LAST).
	# QT_QTCORE_LIBRARY_RELEASE must be set because this var is used in FindQt4 to determine if the path to the Qt libs is found
	if(WIN32)
		set(QT_QTCORE_LIBRARY ${CMAKETOOLS_CURRENT_LIB_DIR}/QtCore4.lib		)	# Path to QtCore lib	
		set(QT_QTCORE_LIBRARY_RELEASE ${CMAKETOOLS_CURRENT_LIB_DIR}/QtCore4.lib)	# Path to QtCore lib (release version)
	elseif(LINUX)
		set(QT_QTCORE_LIBRARY ${CMAKETOOLS_CURRENT_LIB_DIR}/libQtCore.so		)	# Path to QtCore lib	
		set(QT_QTCORE_LIBRARY_RELEASE ${CMAKETOOLS_CURRENT_LIB_DIR}/libQtCore.so)	# Path to QtCore lib (release version)
	endif()
	
	
	
	# Find Qt4 libraries and set all required variables
	FIND_PACKAGE(Qt4 REQUIRED)
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
