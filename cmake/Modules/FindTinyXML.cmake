# - Find TinyXML
# Find the native TinyXML includes and library
#
#  TINYXML_INCLUDE_DIR - where to find tinyxml.h, etc.
#  TINYXML_LIBRARIES   - List of libraries when using tinyxml.

find_path(TINYXML_INCLUDE tinyxml.h)
set(TINYXML_INCLUDE_DIR ${TINYXML_INCLUDE} CACHE INTERNAL "")

find_library(TINYXML_LIBRARY NAMES libtinyxml.a)
set(TINYXML_LIBRARIES ${TINYXML_LIBRARY} CACHE INTERNAL "")
