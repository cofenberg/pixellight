##################################################
## Project
##################################################
cmaketools_doc_project(SDKBrowser)

##################################################
## Prerequisites
##################################################

# Create title file used within the PixelLight SDK browser
configure_file("${CMAKE_SOURCE_DIR}/Docs/SDKBrowser/index.html.in" "${CMAKE_SOURCE_DIR}/Docs/SDKBrowser/index.html")

##################################################
## Html help compiler
##################################################
cmaketools_add_chm_document(${CMAKETOOLS_CURRENT_TARGET} index.hhp)

##################################################
## Dependencies
##################################################
add_dependencies(Docs Docs-SDKBrowser)

##################################################
## Post-Build
##################################################

# CHM
add_custom_command(TARGET Docs-${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_TARGET_CHM} "${PL_BIN_DIR}/Doc"
)

##################################################
## Install
##################################################

if(WIN32)
	# CHM
	install(FILES ${CMAKETOOLS_CURRENT_TARGET_CHM}
		DESTINATION ${PL_INSTALL_ROOT}		COMPONENT SDK
	)
endif()
