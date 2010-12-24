##################################################
## Prerequisites
##################################################

# Create copyright file used within the PixelLight SDK installer
configure_file("${CMAKE_SOURCE_DIR}/Packages/Files/copyright.txt.in" "${CMAKE_SOURCE_DIR}/Packages/Files/copyright.txt")
configure_file("${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt.in" "${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
configure_file("${CMAKE_SOURCE_DIR}/Packages/Files/welcome.txt.in" "${CMAKE_SOURCE_DIR}/Packages/Files/welcome.txt")

##################################################
## CPack configuration
##################################################
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
	##################################################
	## Package specific options
	##################################################
	set(CMAKE_MODULE_PATH		${CMAKE_SOURCE_DIR}/Packages/SDK)
	set(CPACK_PL_PACKAGE_PATH	${CMAKE_SOURCE_DIR}/Packages)
	if(MSVC100)
		# Microsoft Visual C++ 2010 Redistributable
		set(CPACK_PL_VC_FILE	"x86_Microsoft.VC90.CRT_1fc8b3b9a1e18e3b_9.0.21022.8_x-ww_d08d0375") # [TODO] Update to VC10
		set(CPACK_PL_VC_MESSAGE	"In order to install PixelLight on your computer, you will need the Microsoft Visual C++ 2010 Redestributable package. Do you want to install it now?")
		set(CPACK_PL_VC_REDIST	"VC10\\\\vcredist_x86.exe")
	endif()

	##################################################
	## Includes
	##################################################
	include(${CMAKETOOLS_DIR}/CMakeTools_Packs.cmake)

	##################################################
	## Package information
	##################################################
	set(CPACK_PACKAGE_NAME					"PixelLight-SDK")
	set(CPACK_PACKAGE_VENDOR				"PixelLight") # No spaces allowed!
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY	"PixelLight Software Developer Kit - http://www.pixellight.org/")
	set(CPACK_PACKAGE_VERSION_MAJOR			"${CMAKETOOLS_PROJECT_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR			"${CMAKETOOLS_PROJECT_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH			"${CMAKETOOLS_PROJECT_VERSION_PATCH}")
	set(CPACK_PACKAGE_VERSION_RELEASE		"0") # The last one must be a number - too, because we're using something like 'R1', we just don't mention the last number in here...
	set(CPACK_PACKAGE_LEGAL					"Copyright (C) 2002-2010 by The PixelLight Team")
	set(CPACK_RESOURCE_FILE_LICENSE			"${CMAKE_SOURCE_DIR}/Packages/Files/copyright.txt")
	set(CPACK_RESOURCE_FILE_README			"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_RESOURCE_FILE_WELCOME			"${CMAKE_SOURCE_DIR}/Packages/Files/welcome.txt")
	set(CPACK_PACKAGE_DESCRIPTION_FILE		"${CMAKE_SOURCE_DIR}/Packages/Files/readme.txt")
	set(CPACK_PACKAGE_ICON					"${CMAKE_SOURCE_DIR}/Packages/Files/pl_logo.bmp")
	set(CPACK_NSIS_DISPLAY_NAME				"PixelLight SDK")
	set(CPACK_NSIS_INSTALLED_ICON_NAME		"bin\\\\InstallD.exe")
	set(CPACK_NSIS_HELP_LINK				"http://www.pixellight.org")
	set(CPACK_NSIS_URL_INFO_ABOUT			"http://www.pixellight.org")
	set(CPACK_NSIS_CONTACT					"contact@pixellight.org")
	if(WIN32)
		make_windows_path(CPACK_PACKAGE_ICON)
	endif()

	##################################################
	## Debian package information
	##################################################
	set(CPACK_DEBIAN_PACKAGE_NAME			"pixellight")
	set(CPACK_DEBIAN_PACKAGE_VERSION		"${CMAKETOOLS_PROJECT_VERSION_MAJOR}.${CMAKETOOLS_PROJECT_VERSION_MINOR}.${CMAKETOOLS_PROJECT_VERSION_PATCH}-${CMAKETOOLS_PROJECT_VERSION_RELEASE}")
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE	"all")
	set(CPACK_DEBIAN_PACKAGE_DEPENDS		"libzip1 (>= 0.9-3), libncurses5 (>= 5.7+20090803-2ubuntu3), libpcre3 (>= 7.8-3build1), libjpeg62 (>= 6b-15ubuntu1), libpng12-0 (>= 1.2.42-1ubuntu2.1), libxcursor1 (>= 1:1.1.10-1), libxext6 (>= 2:1.1.1-2), libdbus-1-3 (>= 1.2.16-2ubuntu4), libfreetype6 (>= 2.3.11-1ubuntu2.2), libopenal1 (>= 1:1.12.854-0ubuntu1~lucid1), libogg0 (>= 1.1.4~dfsg-2), libvorbisfile3 (>= 1.2.3-3ubuntu1), libxxf86vm1 (>= 1:1.1.0-2), libglu1-mesa (>= 7.7.1-1ubuntu3)")
	set(CPACK_DEBIAN_PACKAGE_MAINTAINER		"contact@pixellight.org")
	set(CPACK_DEBIAN_PACKAGE_DESCRIPTION	${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
	set(CPACK_DEBIAN_PACKAGE_SECTION		"devel")
	set(CPACK_DEBIAN_PACKAGE_PRIORITY		"optional")
#	set(CPACK_DEBIAN_PACKAGE_RECOMMENDS 	"")
#	set(CPACK_DEBIAN_PACKAGE_SUGGESTS	 	"")
	set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA	"")

	##################################################
	## Package name
	##################################################
	# Use name convention "PixelLight-MAJOR.MINOR.PATCH-RELEASE-SYSTEM-Package"
	set(CPACK_PACKAGE_FILE_NAME "PixelLight-${CMAKETOOLS_PROJECT_VERSION_MAJOR}.${CMAKETOOLS_PROJECT_VERSION_MINOR}.${CMAKETOOLS_PROJECT_VERSION_PATCH}-${CMAKETOOLS_PROJECT_VERSION_RELEASE}-${CMAKETOOLS_TARGET_SYSTEM}-SDK")

	##################################################
	## Start menu icons
	##################################################
	# Add icons
	set(CPACK_NSIS_CREATE_ICONS " 
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\SDK-Browser.lnk\\\" \\\"$INSTDIR\\\\SDKBrowser.chm\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Website.lnk\\\" \\\"http://www.pixellight.org/\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\ReleaseNotes.lnk\\\" \\\"$INSTDIR\\\\ReleaseNotes.txt\\\"
		CreateDirectory \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemos.sln.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\PLDemos.sln\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoRendererTriangle.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoRendererTriangle${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoRendererTexturing.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoRendererTexturing${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoMeshTeapot.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoMeshTeapot${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoRendererRTT.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoRendererRTT${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoRendererMultiView.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoRendererMultiView${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoSimpleScene.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoSimpleScene${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoPhysicsBasic.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoPhysicsBasic${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoPhysicsRagdoll.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoPhysicsRagdoll${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoNetworkChat.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoNetworkChat${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoSoundBasic.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoSoundBasic${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoPostProcess.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoPostProcess${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemo2DGame.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemo2DGame${PROJECT_SUFFIX}.exe\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Demos\\\\PLDemoIngameGUI.lnk\\\" \\\"$INSTDIR\\\\Demos\\\\Bin\\\\PLDemoIngameGUI${PROJECT_SUFFIX}.exe\\\"
		CreateDirectory \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Tools\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Tools\\\\PLViewer.lnk\\\" \\\"$INSTDIR\\\\Tools\\\\Bin\\\\PLViewer\\\\PLViewer${PROJECT_SUFFIX}.exe\\\"
		CreateDirectory \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\CodingConventions.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\CodingConventions.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PL3dsMaxSceneExport.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PL3dsMaxSceneExport.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLCore.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLCore.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLDatabase.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLDatabase.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLScene.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLScene.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLCompositing.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLCompositing.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLEngine.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLEngine.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLFeatures.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLFeatures.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLGeneral.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLGeneral.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLGraphics.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLGraphics.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLGui.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLGui.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLInput.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLInput.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLMath.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLMath.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLMesh.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLMesh.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLNetwork.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLNetwork.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLPhysics.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLPhysics.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLRenderer.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLRenderer.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PLSound.pdf.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PLSound.pdf\\\"
		CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Documentation\\\\PixelLightAPI.chm.lnk\\\" \\\"$INSTDIR\\\\Doc\\\\PixelLightAPI.chm\\\"
	")

	# Delete icons
	set(CPACK_NSIS_DELETE_ICONS " 
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\SDK-Browser.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Website.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\ReleaseNotes.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemos.sln.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoRendererTriangle.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoRendererTexturing.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoMeshTeapot.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoRendererMultiView.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoRendererRTT.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoSimpleScene.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoPhysicsBasic.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoPhysicsRagdoll.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoNetworkChat.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoSoundBasic.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoPostProcess.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemo2DGame.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\\PLDemoIngameGUI.lnk\\\"
		RMDir  \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Demos\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Tools\\\\PLViewer.lnk\\\"
		RMDir  \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Tools\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\CodingConventions.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PL3dsMaxSceneExport.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLCore.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLDatabase.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLScene.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLCompositing.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLEngine.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLFeatures.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLGeneral.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLGraphics.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLGui.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLInput.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLMath.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLMesh.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLNetwork.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLPhysics.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLRenderer.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PLSound.pdf.lnk\\\"
		Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\\PixelLightAPI.chm.lnk\\\"
		RMDir  \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\Documentation\\\"
	")

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
		; Install registry key to the PixelLight SDK
		WriteRegStr HKLM ${regkey} \\\"Runtime\\\" \\\"$INSTDIR\\\\Runtime\\\"
		; Install PATH environment variable to the PixelLight SDK
		Push \\\"PATH\\\"
		Push \\\"A\\\"
		Push \\\"HKCU\\\"
		Push \\\"$INSTDIR\\\\Runtime\\\"
		Call EnvVarUpdate
	")

	# Un-Install
	set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
		; Un-Install registry key to the PixelLight SDK
		DeleteRegKey HKLM ${regkey}
		; Un-Install PATH environment variable to the PixelLight SDK
		Push \\\"PATH\\\"
		Push \\\"R\\\"
		Push \\\"HKCU\\\"
		Push \\\"$INSTDIR\\\\Runtime\\\"
		Call un.EnvVarUpdate
	")

	##################################################
	## Install files
	##################################################
	set(CPACK_INSTALL_CMAKE_PROJECTS		"${CMAKE_BINARY_DIR};PixelLight;SDK;/;${CMAKE_BINARY_DIR};PixelLight;Runtime;/;${CMAKE_BINARY_DIR};PixelLight;Docs;/")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY		"PixelLight-SDK")
	set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY	"PixelLight-SDK")

	##################################################
	## Set generator
	##################################################
	set(CPACK_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CPackConfig-PL_SDK.cmake")
	if(WIN32)
		set(CPACK_GENERATOR		"NSIS")
		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.exe")
	elseif(LINUX)
#		set(CPACK_GENERATOR		"TGZ")
#		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.tar.gz")
		set(CPACK_GENERATOR		"DEB")
		set(CPACK_OUTPUT_FILE	"${CPACK_PACKAGE_FILE_NAME}.deb")
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
	Pack-SDK
	COMMAND ${CPACK_COMMAND} -C ${CMAKE_BUILD_TYPE} --config ${CMAKE_BINARY_DIR}/CPackConfig-PL_SDK.cmake
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_target_properties(Pack-SDK PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Dependencies
##################################################
add_dependencies(Pack-SDK	PixelLight Docs)
add_dependencies(Pack		Pack-SDK)

##################################################
## Post-Build
##################################################
add_custom_command(TARGET Pack-SDK
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PL_BIN_DIR}/Packages"
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CPACK_OUTPUT_FILE} "${PL_BIN_DIR}/Packages"
)

