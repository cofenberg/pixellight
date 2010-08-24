# - Find Ogg
# Find the native Ogg includes and library
#
#  LIBOGG_INCLUDE_DIRS - where to find ogg.h, etc.
#  LIBOGG_LIBRARIES    - List of libraries when using libogg.

FIND_PATH(LIBOGG_INCLUDE_DIRS ogg.h
  HINTS
  PATH_SUFFIXES include/ogg include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(LIBOGG_LIBRARIES 
  NAMES ogg
  HINTS
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Ogg  DEFAULT_MSG  LIBOGG_LIBRARIES LIBOGG_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBOGG_LIBRARIES LIBOGG_INCLUDE_DIRS)

