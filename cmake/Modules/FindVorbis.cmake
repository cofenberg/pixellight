# - Find Vorbis
# Find the native Vorbis includes and library
#
#  LIBVORBIS_INCLUDE_DIRS - where to find vorbisfile.h, etc.
#  LIBVORBIS_LIBRARIES   - List of libraries when using libvorbis.

FIND_PATH(LIBVORBIS_INCLUDE_DIRS vorbisfile.h
  HINTS
  PATH_SUFFIXES include/vorbis include
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

FIND_LIBRARY(LIBVORBIS_LIBRARY 
  NAMES vorbis
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

FIND_LIBRARY(LIBVORBISFILE_LIBRARY 
  NAMES vorbisfile
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

set(LIBVORBIS_LIBRARIES ${LIBVORBIS_LIBRARY} ${LIBVORBISFILE_LIBRARY} CACHE INTERNAL "")

# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenAL  DEFAULT_MSG  LIBVORBIS_LIBRARIES LIBVORBIS_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBVORBIS_LIBRARIES LIBVORBIS_INCLUDE_DIRS)

