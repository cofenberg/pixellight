##################################################
## Project
##################################################
project(Engine)

##################################################
## Prerequisites
##################################################

# Copy runtime data
file(MAKE_DIRECTORY "${PL_BIN_DIR}/PLRuntime/Data")
copy_files("${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Data/*.zip" "${PL_BIN_DIR}/PLRuntime/Data" EXCLUDE "\\\\.svn")

##################################################
## Target
##################################################
add_custom_target(Engine)

##################################################
## Projects
##################################################
add_subdirectory(PLRenderer)
add_subdirectory(PLInput)
add_subdirectory(PLMesh)
add_subdirectory(PLScene)
add_subdirectory(PLCompositing)
add_subdirectory(PLPhysics)
add_subdirectory(PLSound)
add_subdirectory(PLEngine)
if(PL_PLUGIN_RENDERER_NULL)
	add_subdirectory(PLRendererNull)
endif()
if(PL_PLUGIN_RENDERER_OPENGL)
	add_subdirectory(PLRendererOpenGL)
	if(PL_PLUGIN_RENDERER_OPENGLCG)
		add_subdirectory(PLRendererOpenGLCg)
	endif()
endif()
if(PL_PLUGIN_RENDERER_OPENGLES)
	add_subdirectory(PLRendererOpenGLES)
endif()
if(PL_PLUGIN_RENDERER_D3D9 AND WIN32)
	add_subdirectory(PLRendererD3D9)
endif()
if(PL_PLUGIN_RENDERER_D3D11 AND WIN32)
	add_subdirectory(PLRendererD3D11)
endif()
if(PL_PLUGIN_SOUND_NULL)
	add_subdirectory(PLSoundNull)
endif()
if(PL_PLUGIN_SOUND_OPENAL)
	add_subdirectory(PLSoundOpenAL)
endif()
if(PL_PLUGIN_SOUND_FMOD)
	add_subdirectory(PLSoundFMOD)
endif()
if(PL_PLUGIN_SOUND_FMODEX)
	add_subdirectory(PLSoundFMODEx)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Engine)

##################################################
## Install
##################################################

# Data
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/PLRuntime/Data
	DESTINATION ${PL_INSTALL_RUNTIME}		COMPONENT Runtime	REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)
