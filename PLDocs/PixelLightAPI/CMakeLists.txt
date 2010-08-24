##################################################
## Project
##################################################
cmaketools_doc_project(PixelLightAPI)

##################################################
## Prerequisites
##################################################

# Create footer file used within the PixelLight API documentation
configure_file("${CMAKE_SOURCE_DIR}/PLDocs/PixelLightAPI/footer.html.in" "${CMAKE_SOURCE_DIR}/PLDocs/PixelLightAPI/footer.html")

##################################################
## Doxygen documentation
##################################################
cmaketools_add_doxygen_docs(${CMAKETOOLS_CURRENT_TARGET} doxyfile.in)

##################################################
## Html help compiler
##################################################
cmaketools_add_chm_document(${CMAKETOOLS_CURRENT_TARGET} ${CMAKETOOLS_CURRENT_TARGET_HHP})

##################################################
## Dependencies
##################################################
add_dependencies(Docs Docs-PixelLightAPI)

##################################################
## Post-Build
##################################################

# CHM
if(CMAKETOOLS_CURRENT_TARGET_CHM)
	add_custom_command(TARGET Docs-${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_TARGET_CHM} "${PL_BIN_DIR}/Doc"
	)
endif()

##################################################
## Install
##################################################

# CHM
if(CMAKETOOLS_CURRENT_TARGET_CHM)
	install(FILES ${CMAKETOOLS_CURRENT_TARGET_CHM}
		DESTINATION ${PL_INSTALL_DOC}		COMPONENT Docs
	)
endif()
