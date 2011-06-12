##################################################
## Project
##################################################
project(Base)

##################################################
## Target
##################################################
add_custom_target(Base)

##################################################
## Projects
##################################################
add_subdirectory(PLGeneral)
add_subdirectory(PLCore)
add_subdirectory(PLGraphics)
add_subdirectory(PLMath)
add_subdirectory(PLDatabase)
if(PL_PLUGIN_DATABASE_NULL)
	add_subdirectory(PLDatabaseNull)
endif()
if(PL_PLUGIN_DATABASE_MYSQL)
	add_subdirectory(PLDatabaseMySQL)
endif()
if(PL_PLUGIN_DATABASE_POSTGRESQL)
	add_subdirectory(PLDatabasePostgreSQL)
endif()
if(PL_PLUGIN_DATABASE_SQLITE)
	add_subdirectory(PLDatabaseSQLite)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(PixelLight Base)
