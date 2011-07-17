##################################################
## Project
##################################################
project(Docs)

##################################################
## Prerequisites
##################################################

# Create 'Doc' directory
file(MAKE_DIRECTORY ${PL_BIN_DIR}/Doc)

# Create temp dir
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Common)

# Copy file format samples
file(MAKE_DIRECTORY "${PL_BIN_DIR}/Doc/FileFormats")
copy_files("${CMAKE_SOURCE_DIR}/Docs/FileFormats/*.*" "${PL_BIN_DIR}/Doc/FileFormats")

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
add_subdirectory(CodingConventions)
add_subdirectory(PLFeatures)
add_subdirectory(PLGeneral)
add_subdirectory(PLCore)
add_subdirectory(PLMath)
add_subdirectory(PLGraphics)
add_subdirectory(PLScript)
add_subdirectory(PLDatabase)
add_subdirectory(PLGui)
add_subdirectory(PLInput)
add_subdirectory(PLRenderer)
add_subdirectory(PLMesh)
add_subdirectory(PLScene)
add_subdirectory(PLCompositing)
add_subdirectory(PLSound)
add_subdirectory(PLPhysics)
add_subdirectory(PLEngine)
add_subdirectory(PL3dsMaxSceneExport)
add_subdirectory(PixelLightAPI)
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
	DESTINATION ${PL_INSTALL_DOC}		COMPONENT Docs		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
