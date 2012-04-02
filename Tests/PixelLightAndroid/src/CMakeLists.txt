cmake_minimum_required(VERSION 2.8.3)


##################################################
## Find packages
##################################################
find_host_package(PixelLight)	# "find_package"-variant provided by "android.toolchain.cmake", required for PixelLight CMake variables like "PL_PLCORE_INCLUDE_DIR"


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR})					# The current source directory
include_directories(${ANDROID_NDK}/sources/android/native_app_glue)	# For the "android_native_app_glue.h"-header include
include_directories(${PL_PLCORE_INCLUDE_DIR})						# PLCore headers
include_directories(${PL_PLFRONTENDOS_INCLUDE_DIR})					# PLFrontendOS headers


##################################################
## Source codes
##################################################
set(CURRENT_SRC
	${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
	AndroidMain.cpp
)


##################################################
## Shared libraries
##################################################
set(CURRENT_SHARED_LIBRARIES
# These are the external shared libraries which are always release builds
	# Newton
	${PL_NEWTON_LIBRARY}				# Required by "PLPhysicsNewton"
	# libRocket
	${PL_LIBROCKETCORE_LIBRARY}			# Required by "PLlibRocket"
	${PL_LIBROCKETCONTROLS_LIBRARY}		# Required by "PLlibRocket"
	${PL_LIBROCKETDEBUGGER_LIBRARY}		# Required by "PLlibRocket"
	# FMOD Ex
	${PL_FMODEX_LIBRARY}				# Required by "PLSoundFMODEx"
# These are the shared libraries which may be in release or debug build
	# Base
	${PL_PLCORE_LIBRARY}
	${PL_PLMATH_LIBRARY}
	${PL_PLGRAPHICS_LIBRARY}
	${PL_PLINPUT_LIBRARY}
	${PL_PLRENDERER_LIBRARY}
	${PL_PLMESH_LIBRARY}
	${PL_PLSCENE_LIBRARY}
	${PL_PLPHYSICS_LIBRARY}
	${PL_PLSOUND_LIBRARY}
	${PL_PLENGINE_LIBRARY}
	${PL_PLGUI_LIBRARY}					# Required by "71libRocket"
	# Plugins
	${PL_PLFRONTENDOS_LIBRARY}			# The PixelLight Android frontend
	${PL_PLRENDEREROPENGLES2_LIBRARY}
	${PL_PLCOMPOSITING_LIBRARY}
	${PL_PLSCRIPTBINDINGS_LIBRARY}		# Required by "40ScriptHelloWorld", "41ScriptGlobalVariables", "42ScriptFunctors", "43ScriptBindings", "44ScriptOOP"
	${PL_PLSCRIPTLUA_LIBRARY}			# *alternative* Required by "40ScriptHelloWorld", "41ScriptGlobalVariables", "42ScriptFunctors", "43ScriptBindings", "44ScriptOOP"
#	${PL_PLSCRIPTANGELSCRIPT_LIBRARY}	# *alternative* Required by "40ScriptHelloWorld", "41ScriptGlobalVariables", "42ScriptFunctors", "43ScriptBindings", "44ScriptOOP"
	${PL_PLSPARK_PL_LIBRARY}			# Required by "70SPARK"
	${PL_PLLIBROCKET_LIBRARY}			# Required by "71libRocket"
	${PL_PLPHYSICSNEWTON_LIBRARY}		# *alternative* Required by "62Physics", "63PhysicsRagdoll"
#	${PL_PLPHYSICSBULLET_LIBRARY}		# *alternative* Required by "62Physics", "63PhysicsRagdoll"
	${PL_PLSOUNDFMODEX_LIBRARY}			# *alternative* Required by "61Sound", "67Game2D"
#	${PL_PLASSIMP_LIBRARY}
	${PL_PLSOUNDOPENSLES_LIBRARY}		# Required by "61Sound"
	${PL_PLFRONTENDPLGUI_LIBRARY}		# Required by "66IngameGUI"
	# Application
	"${PL_TESTS_BIN_DIR}/libPLUnitTests${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib30Input${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib40ScriptHelloWorld${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib41ScriptGlobalVariables${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib42ScriptFunctors${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib43ScriptBindings${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib44ScriptOOP${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib50RendererTriangle${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib51RendererTexturing${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib52RendererMesh${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib54RendererRTT${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib60Scene${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib61Sound${suffix}.so"	# [TODO] Implement OpenSL ES for sound
	"${PL_SAMPLES_BIN_DIR}/lib62Physics${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib63PhysicsRagdoll${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib64Picking${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib66IngameGUI${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib67Game2D${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib70SPARK${suffix}.so"
	"${PL_SAMPLES_BIN_DIR}/lib71libRocket${suffix}.so"
)


##################################################
## Assets
##################################################
set(CURRENT_ASSETS
	"${PL_RUNTIME_DATA_DIR}/Standard.zip"
	"${PL_RUNTIME_DATA_DIR}/PLGui.zip"		# Required by "66IngameGUI"
	"${PL_RUNTIME_DATA_DIR}/SPARK_PL.zip"	# Required by "SPARK_PL"
	"${PL_SAMPLES_DATA_DIR}/*.*"			# Copy all sample data
)


##################################################
## Build
##################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ffor-scope -fno-rtti -fno-exceptions -pipe -ffunction-sections -fdata-sections -ffast-math -Wnon-virtual-dtor -Wreorder -Wsign-promo -fvisibility=hidden -fvisibility-inlines-hidden -Wstrict-null-sentinel -Os -funroll-all-loops -fpeel-loops -ftree-vectorize")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--as-needed -Wl,--gc-sections -Wl,--no-undefined -Wl,--strip-all -Wl,-rpath-link=${ANDROID_NDK_SYSROOT}/usr/lib/ -L${ANDROID_NDK_SYSROOT}/usr/lib/")
add_library(${CURRENT_TARGET_NAME} SHARED ${CURRENT_SRC})
target_link_libraries(${CURRENT_TARGET_NAME} log android ${CURRENT_SHARED_LIBRARIES})
set_target_properties(${CURRENT_TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS "__STDC_INT64__;LINUX;ANDROID")	# PLCore needs the preprocessor definitions "LINUX" and "ANDROID"


##################################################
## Post build
##################################################

# Copy the build shared library as well, can be release or debug build
set(CURRENT_SHARED_LIBRARIES
	${CURRENT_SHARED_LIBRARIES}
	"${LIBRARY_OUTPUT_PATH}/lib${CURRENT_TARGET_NAME}.so"
)

# Create Android apk file (macro from "<PixelLight>/cmake/Android/Apk.cmake")
android_create_apk("${CURRENT_TARGET_NAME}" "${CMAKE_BINARY_DIR}/apk" "${CURRENT_SHARED_LIBRARIES}" "${CURRENT_ASSETS}" "Data")
