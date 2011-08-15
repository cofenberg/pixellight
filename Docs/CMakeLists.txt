##################################################
## Project
##################################################
project(Docs)

##################################################
## Prerequisites
##################################################

# Create 'Docs'-directory
set(PL_DOCS_DIR "${PL_BIN_DIR}/Docs")
file(MAKE_DIRECTORY ${PL_DOCS_DIR})

# Create temp dir
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Common)

# Copy file format samples
file(MAKE_DIRECTORY "${PL_DOCS_DIR}/FileFormats")
copy_files("${CMAKE_SOURCE_DIR}/Docs/FileFormats/*.*" "${PL_DOCS_DIR}/FileFormats")

# Create title file used within the PixelLight documentations
configure_file("${CMAKE_SOURCE_DIR}/Docs/Common/Title.tex.in" "${CMAKE_SOURCE_DIR}/Docs/Common/Title.tex")

##################################################
## Target
##################################################
add_custom_target(Docs)
set_target_properties(Docs PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

##################################################
## Projects
##################################################
add_subdirectory(Doc-Sample)
add_subdirectory(PixelLightFeatures)
add_subdirectory(PixelLightBase)
add_subdirectory(PixelLightAPI)
add_subdirectory(PixelLightCompositing)
add_subdirectory(PixelLightCodingConventions)
add_subdirectory(PixelLightScript)
add_subdirectory(PixelLight3dsMaxSceneExport)
if(WIN32)
	add_subdirectory(SDKBrowser)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Docs)

##################################################
## Install
##################################################

install(DIRECTORY ${CMAKE_SOURCE_DIR}/Docs/FileFormats
	DESTINATION ${PL_INSTALL_DOCS}		COMPONENT Docs		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
