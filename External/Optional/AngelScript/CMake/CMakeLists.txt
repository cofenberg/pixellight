cmake_minimum_required(VERSION 2.8.3)


##################################################
## Project
##################################################
set(CURRENT_TARGET_NAME "angelscript")
project(${CURRENT_TARGET_NAME})


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include )


##################################################
## Source codes
##################################################
set(CURRENT_SRC
	../../source/as_atomic.cpp
	../../source/as_builder.cpp
	../../source/as_bytecode.cpp
	../../source/as_callfunc.cpp
	../../source/as_callfunc_arm.cpp
	../../source/as_callfunc_mips.cpp
	../../source/as_callfunc_ppc.cpp
	../../source/as_callfunc_ppc_64.cpp
	../../source/as_callfunc_sh4.cpp
	../../source/as_callfunc_x86.cpp
	../../source/as_callfunc_x64_gcc.cpp
	../../source/as_compiler.cpp
	../../source/as_context.cpp
	../../source/as_configgroup.cpp
	../../source/as_datatype.cpp
	../../source/as_generic.cpp
	../../source/as_gc.cpp
	../../source/as_globalproperty.cpp
	../../source/as_memory.cpp
	../../source/as_module.cpp
	../../source/as_objecttype.cpp
	../../source/as_outputbuffer.cpp
	../../source/as_parser.cpp
	../../source/as_restore.cpp
	../../source/as_scriptcode.cpp
	../../source/as_scriptengine.cpp
	../../source/as_scriptfunction.cpp
	../../source/as_scriptnode.cpp
	../../source/as_scriptobject.cpp
	../../source/as_string.cpp
	../../source/as_string_util.cpp
	../../source/as_thread.cpp
	../../source/as_tokenizer.cpp
	../../source/as_typeinfo.cpp
	../../source/as_variablescope.cpp 
)


##################################################
## Shared libraries
##################################################
set(CURRENT_SHARED_LIBRARIES
	# Not required in this project
)


##################################################
## Build
##################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ffor-scope -fno-rtti -fno-exceptions -pipe -ffunction-sections -fdata-sections -ffast-math -Wnon-virtual-dtor -Wreorder -Wsign-promo -Wstrict-null-sentinel -Os -funroll-all-loops -fpeel-loops -ftree-vectorize")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--as-needed -Wl,--gc-sections -Wl,--no-undefined -Wl,--strip-all")
if(ANDROID)
	set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-rpath-link=${ANDROID_NDK_SYSROOT}/usr/lib/ -L${ANDROID_NDK_SYSROOT}/usr/lib/")
endif()
add_library(${CURRENT_TARGET_NAME} STATIC ${CURRENT_SRC})
target_link_libraries(${CURRENT_TARGET_NAME} ${CURRENT_SHARED_LIBRARIES})
set_target_properties(${CURRENT_TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS "__STDC_INT64__;AS_MAX_PORTABILITY")
