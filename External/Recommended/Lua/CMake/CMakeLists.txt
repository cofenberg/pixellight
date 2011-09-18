cmake_minimum_required(VERSION 2.8.3)


##################################################
## Project
##################################################
set(CURRENT_TARGET_NAME "lua")
project(${CURRENT_TARGET_NAME})


##################################################
## Includes
##################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


##################################################
## Source codes
##################################################
set(CURRENT_SRC
	src/lapi.c
	src/lauxlib.c
	src/lbaselib.c
	src/lcode.c
	src/ldblib.c
	src/ldebug.c
	src/ldo.c
	src/ldump.c
	src/lfunc.c
	src/lgc.c
	src/linit.c
	src/liolib.c

	# When building Lua (5.1.4) for Android, the compiler will tell you "error: 'struct lconv' has no member named 'decimal_point'"
	# -> To fix this, open "llex.c", search for "trydecpoint()", change "ls->decpoint = (cv ? cv->decimal_point[0] : '.');" into "ls->decpoint = '.';"
	#    and comment out the line "struct lconv *cv = localeconv();" (else you get "struct lconv *cv = localeconv();" when linking)
	src/llex.c

	src/lmathlib.c
	src/lmem.c
	src/loadlib.c
	src/lobject.c
	src/lopcodes.c
	src/loslib.c
	src/lparser.c
	src/lstate.c
	src/lstring.c
 	src/lstrlib.c
	src/ltable.c
	src/ltablib.c
	src/ltm.c
	src/lua.c
	src/luac.c
	src/lundump.c
	src/lvm.c
	src/lzio.c
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ffor-scope -fno-rtti -fno-exceptions -pipe -ffunction-sections -fdata-sections -ffast-math -Wnon-virtual-dtor -Wreorder -Wsign-promo -fvisibility=hidden -fvisibility-inlines-hidden -Wstrict-null-sentinel -Os -funroll-all-loops -fpeel-loops -ftree-vectorize")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--as-needed -Wl,--gc-sections -Wl,--no-undefined -Wl,--strip-all")
if(ANDROID)
	set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-rpath-link=${ANDROID_NDK_SYSROOT}/usr/lib/ -L${ANDROID_NDK_SYSROOT}/usr/lib/")
endif()
add_library(${CURRENT_TARGET_NAME} STATIC ${CURRENT_SRC})
target_link_libraries(${CURRENT_TARGET_NAME} ${CURRENT_SHARED_LIBRARIES})
set_target_properties(${CURRENT_TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS "__STDC_INT64__")
