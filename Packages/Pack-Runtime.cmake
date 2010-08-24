##################################################
## CPack configuration
##################################################
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
	##################################################
	## Package specific options
	##################################################
	set(CMAKE_MODULE_PATH		${CMAKE_SOURCE_DIR}/Packages/SDK)
	set(CPACK_PL_PACKAGE_PATH	${CMAKE_SOURCE_DIR}/Packages)
	if(MSVC90)
		# Microsoft Visual C++ 2008 Redistributable
		set(CPACK_PL_VC_FILE	"x86_Microsoft.VC90.CRT_1fc8b3b9a1e18e3b_9.0.21022.8_x-ww_d08d0375")
		set(CPACK_PL_VC_MESSAGE	"In order to install PixelLight on your computer, you will need the Microsoft Visual C++ 2008 Redestributable package. Do you want to install it now?")
		set(CPACK_PL_VC_REDIST	"VC9\\\\vcredist_x86.exe")
	endif()

	##################################################
	## Includes
	##################################################
	include(${CMAKETOOLS_DIR}/CMakeTools_Packs.cmake)

	##################################################
	## Package information
	##################################################
	set(CPACK_PACKAGE_NAME					"PixelLight-Runtime")
	set(CPACK_PACKAGE_VENDOR				"PixelLight")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY	"PixelLight Runtime")
	set(CPACK_PACKAGE_VERSION_MAJOR			"${CMAKETOOLS_PROJECT_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR			"${CMAKETOOLS_PROJECT_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH			"${CMAKETOOLS_PROJECT_VERSION_PATCH}")
	set(CPACK_RESOURCE_FILE_LICENSE			"${CMAKE_SOURCE_DIR}/Packages/Files/copyright.txt")
	set(CPACK_RESOURCE_FILE_README			"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_RESOURCE_FILE_WELCOME			"${CMAKE_SOURCE_DIR}/Packages/Files/welcome.txt")
	set(CPACK_PACKAGE_DESCRIPTION_FILE		"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_PACKAGE_ICON					"${CMAKE_SOURCE_DIR}/Packages/Files/pl_logo.bmp")
	set(CPACK_NSIS_DISPLAY_NAME				"PixelLight Runtime")
	set(CPACK_NSIS_INSTALLED_ICON_NAME		"bin\\\\InstallD.exe")
	set(CPACK_NSIS_HELP_LINK				"http://www.pixellight.org")
	set(CPACK_NSIS_URL_INFO_ABOUT			"http://www.pixellight.org")
	set(CPACK_NSIS_CONTACT					"contact@pixellight.org")
	if(WIN32)
		make_windows_path(CPACK_PACKAGE_ICON)
	endif()

	##################################################
	## Package name
	##################################################
	# Use name convention "PixelLight-MAJOR.MINOR.PATCH-RELEASE-SYSTEM-Package"
	set(CPACK_PACKAGE_FILE_NAME "PixelLight-${CMAKETOOLS_PROJECT_VERSION_MAJOR}.${CMAKETOOLS_PROJECT_VERSION_MINOR}.${CMAKETOOLS_PROJECT_VERSION_PATCH}-${CMAKETOOLS_PROJECT_VERSION_RELEASE}-${CMAKETOOLS_TARGET_SYSTEM}-Runtime")

	##################################################
	## Start menu icons
	##################################################
	set(CPACK_NSIS_CREATE_ICONS "")
	set(CPACK_NSIS_DELETE_ICONS "")

	##################################################
	## Extra install commands
	##################################################
	# Registry key
	if(CMAKETOOLS_CONFIG_SUFFIX)
		set(regkey "\\\"Software\\\\${CPACK_PACKAGE_VENDOR}\\\\${CPACK_PACKAGE_NAME}-${CMAKETOOLS_CONFIG_SUFFIX}\\\"")
	else()
		set(regkey "\\\"Software\\\\${CPACK_PACKAGE_VENDOR}\\\\${CPACK_PACKAGE_NAME}\\\"")
	endif()

	# Install
	set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
		WriteRegStr HKLM ${regkey} \\\"Runtime\\\" \\\"$INSTDIR\\\\Runtime\\\"
		Push \\\"$INSTDIR\\\\Runtime\\\"
		Call AddToPath
	")

	# Un-Install
	set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
		DeleteRegKey HKLM ${regkey}
		Push \\\"$INSTDIR\\\\Runtime\\\"
		Call un.RemoveFromPath
	")

	##################################################
	## Install files
	##################################################
	set(CPACK_INSTALL_CMAKE_PROJECTS		"${CMAKE_BINARY_DIR};PixelLight;Runtime;/")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY		"PixelLight-Runtime")
	set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY	"PixelLight-Runtime")

	##################################################
	## Set generator
	##################################################
	set(CPACK_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CPackConfig-PL_Runtime.cmake")
	if(WIN32)
		set(CPACK_GENERATOR		"NSIS")
		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.exe")
	elseif(LINUX)
		set(CPACK_GENERATOR		"TGZ")
		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.tar.gz")
	endif()

	##################################################
	## CPack
	##################################################
	include(CPack)
endif()

##################################################
## Package target
##################################################
add_custom_target(
	Pack-Runtime
	COMMAND ${CPACK_COMMAND} -C ${CMAKE_BUILD_TYPE} --config ${CMAKE_BINARY_DIR}/CPackConfig-PL_Runtime.cmake
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_target_properties(Pack-Runtime PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Dependencies
##################################################
add_dependencies(Pack-Runtime	PixelLight Docs)
add_dependencies(Pack			Pack-Runtime)

##################################################
## Post-Build
##################################################
add_custom_command(TARGET Pack-Runtime
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PL_BIN_DIR}/Packages"
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CPACK_OUTPUT_FILE} "${PL_BIN_DIR}/Packages"
)
