##################################################
## Project
##################################################
define_project(PLCore)

##################################################
## Source files
##################################################
add_sources(
	src/PLCore.cpp
	src/Core.cpp
	src/Base/Class.cpp
	src/Base/ClassImpl.cpp
	src/Base/ClassReal.cpp
	src/Base/ClassDummy.cpp
	src/Base/ClassManager.cpp
	src/Base/MemberDesc.cpp
	src/Base/Module.cpp
	src/Base/Object.cpp
	src/Base/Event/DynEvent.cpp
	src/Base/Event/DynEventHandler.cpp
	src/Base/Event/EventDesc.cpp
	src/Base/Event/EventHandlerDesc.cpp
	src/Base/Func/ConstructorDesc.cpp
	src/Base/Func/DynFunc.cpp
	src/Base/Func/DynParams.cpp
	src/Base/Func/FuncDesc.cpp
	src/Base/Tools/ParamsParser.cpp
	src/Base/Tools/ParamsParserXml.cpp
	src/Base/TypeInfo/DynTypeInfo.cpp
	src/Base/Var/DynVar.cpp
	src/Base/Var/VarDesc.cpp
	src/Config/Config.cpp
	src/Config/ConfigLoader.cpp
	src/Config/ConfigLoaderPL.cpp
	src/Config/CoreConfigGroup.cpp
	src/Tools/Loadable.cpp
	src/Tools/LoadableManager.cpp
	src/Tools/LoadableType.cpp
	src/Tools/Loader.cpp
	src/Tools/Chunk.cpp
	src/Tools/ChunkLoader.cpp
	src/Tools/ChunkLoaderPL.cpp
	src/Tools/ChunkLoaderPLXml.cpp
	src/Tools/Localization.cpp
	src/Tools/LocalizationGroup.cpp
	src/Tools/LocalizationText.cpp
	src/Tools/LocalizationLoader.cpp
	src/Tools/LocalizationLoaderPL.cpp
	src/Application/ApplicationContext.cpp
	src/Application/ConsoleApplication.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/PLBase/PLGeneral/include
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_BIN_DIR}/Lib
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLGeneral
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLCORE_EXPORTS
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_compile_defs(
		${LINUX_COMPILE_DEFS}
	)
endif()

##################################################
## Compiler flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_compile_flags(
		${WIN32_COMPILE_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_compile_flags(
		${LINUX_COMPILE_FLAGS}
	)
endif()

##################################################
## Linker flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_linker_flags(
		${WIN32_LINKER_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_linker_flags(
		${LINUX_LINKER_FLAGS}
	)
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLGeneral)
add_dependencies(Base                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} "${PL_BIN_DIR}/PLRuntime"
)
if(LINUX)
	# Create relative symbolic links
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY "${PL_BIN_DIR}/PLRuntime"
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_SHARED}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}		COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 			COMPONENT SDK		PATTERN ".svn" EXCLUDE
)


##################################################
## Build static library
##################################################
if(NOT LINUX)
	remove_compile_defs(PLCORE_EXPORTS)
endif()
remove_libs(PLGeneral)
add_libs(PLGeneralStat)
add_compile_defs(PLGENERAL_STATIC PLCORE_STATIC)
build_library(${CMAKETOOLS_CURRENT_TARGET}Stat STATIC)

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_PROJECT}Stat	PLGeneralStat External-zlib External-libpcre)
add_dependencies(Base                       		${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Static library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} "${PL_BIN_DIR}/Lib"
)
