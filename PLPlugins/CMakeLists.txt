##################################################
## Project
##################################################
project(Plugins)

##################################################
## Target
##################################################
add_custom_target(Plugins)

##################################################
## Projects
##################################################
if(PL_PLUGIN_ENGINE_DEFAULTFF)
	add_subdirectory(PLDefaultFileFormats)
endif()
if(PL_PLUGIN_ENGINE_PARTICLEGROUPS)
	add_subdirectory(PLParticleGroups)
endif()
if(PL_PLUGIN_ENGINE_SPARK)
	add_subdirectory(SPARK_PL)
endif()
if(PL_PLUGIN_ENGINE_POSTPROCESS)
	add_subdirectory(PLPostProcessEffects)
endif()

# Currently only for windows
if(WIN32)
	add_subdirectory(PLPlugin)
	if(PL_PLUGIN_ENGINE_IMAGEEXR)
		add_subdirectory(PLImageLoaderEXR)
	endif()
	if(PL_BROWSER_PLUGIN_ACTIVEX)
		add_subdirectory(PLPluginActiveX)
	endif()
	if(PL_BROWSER_PLUGIN_MOZILLA)
		add_subdirectory(PLPluginMozilla)
	endif()
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Plugins)
