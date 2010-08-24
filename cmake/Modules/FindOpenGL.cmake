# - Try to find OpenGL
# Once done this will define
#  
#  OPENGL_FOUND        - system has OpenGL
#  OPENGL_XMESA_FOUND  - system has XMESA
#  OPENGL_GLU_FOUND    - system has GLU
#  OPENGL_INCLUDE_DIR  - the GL include directory
#  OPENGL_LIBRARIES    - Link these to use OpenGL and GLU
#   
# If you want to use just GL you can use these values
#  OPENGL_gl_LIBRARY   - Path to OpenGL Library
#  OPENGL_glu_LIBRARY  - Path to GLU Library
#  
# On OSX default to using the framework version of opengl
# People will have to change the cache values of OPENGL_glu_LIBRARY 
# and OPENGL_gl_LIBRARY to use OpenGL with X11 on OSX

#=============================================================================
#CMake - Cross Platform Makefile Generator
#Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions
#are met:
#
#* Redistributions of source code must retain the above copyright
#  notice, this list of conditions and the following disclaimer.
#
#* Redistributions in binary form must reproduce the above copyright
#  notice, this list of conditions and the following disclaimer in the
#  documentation and/or other materials provided with the distribution.
#
#* Neither the names of Kitware, Inc., the Insight Software Consortium,
#  nor the names of their contributors may be used to endorse or promote
#  products derived from this software without specific prior written
#  permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#------------------------------------------------------------------------------
#
#The above copyright and license notice applies to distributions of
#CMake in source and binary form.  Some source files contain additional
#notices of original copyright by their contributors; see each source
#for details.  Third-party software packages supplied with CMake under
#compatible licenses provide their own copyright notices documented in
#corresponding subdirectories.
#
#------------------------------------------------------------------------------
#
#CMake was initially developed by Kitware with the following sponsorship:
#
# * National Library of Medicine at the National Institutes of Health
#   as part of the Insight Segmentation and Registration Toolkit (ITK).
#
# * US National Labs (Los Alamos, Livermore, Sandia) ASC Parallel
#   Visualization Initiative.
#
# * National Alliance for Medical Image Computing (NAMIC) is funded by the
#   National Institutes of Health through the NIH Roadmap for Medical Research,
#   Grant U54 EB005149.
#
# * Kitware, Inc.
#=============================================================================

IF (WIN32)
  IF (CYGWIN)

    FIND_PATH(OPENGL_INCLUDE_DIR GL/gl.h )

    FIND_LIBRARY(OPENGL_gl_LIBRARY opengl32 )

    FIND_LIBRARY(OPENGL_glu_LIBRARY glu32 )

  ELSE (CYGWIN)

    IF(BORLAND)
      SET (OPENGL_gl_LIBRARY import32 CACHE STRING "OpenGL library for win32")
      SET (OPENGL_glu_LIBRARY import32 CACHE STRING "GLU library for win32")
    ELSE(BORLAND)
      SET (OPENGL_gl_LIBRARY opengl32 CACHE STRING "OpenGL library for win32")
      SET (OPENGL_glu_LIBRARY glu32 CACHE STRING "GLU library for win32")
    ENDIF(BORLAND)

  ENDIF (CYGWIN)

ELSE (WIN32)

  IF (APPLE)

    FIND_LIBRARY(OPENGL_gl_LIBRARY OpenGL DOC "OpenGL lib for OSX")
    FIND_LIBRARY(OPENGL_glu_LIBRARY AGL DOC "AGL lib for OSX")
    FIND_PATH(OPENGL_INCLUDE_DIR OpenGL/gl.h DOC "Include for OpenGL on OSX")

  ELSE(APPLE)
    # Handle HP-UX cases where we only want to find OpenGL in either hpux64
    # or hpux32 depending on if we're doing a 64 bit build.
    IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
      SET(HPUX_IA_OPENGL_LIB_PATH /opt/graphics/OpenGL/lib/hpux32/)
    ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
      SET(HPUX_IA_OPENGL_LIB_PATH 
        /opt/graphics/OpenGL/lib/hpux64/
        /opt/graphics/OpenGL/lib/pa20_64)
    ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

    # The first line below is to make sure that the proper headers
    # are used on a Linux machine with the NVidia drivers installed.
    # They replace Mesa with NVidia's own library but normally do not
    # install headers and that causes the linking to
    # fail since the compiler finds the Mesa headers but NVidia's library.
    # Make sure the NVIDIA directory comes BEFORE the others.
    #  - Atanas Georgiev <atanas@cs.columbia.edu>

    FIND_PATH(OPENGL_INCLUDE_DIR GL/gl.h
      /usr/share/doc/NVIDIA_GLX-1.0/include
      /usr/openwin/share/include
      /opt/graphics/OpenGL/include /usr/X11R6/include
    )

    FIND_PATH(OPENGL_xmesa_INCLUDE_DIR GL/xmesa.h
      /usr/share/doc/NVIDIA_GLX-1.0/include
      /usr/openwin/share/include
      /opt/graphics/OpenGL/include /usr/X11R6/include
    )

    FIND_LIBRARY(OPENGL_gl_LIBRARY
      NAMES GL MesaGL
      PATHS /opt/graphics/OpenGL/lib
            /usr/openwin/lib
            /usr/shlib /usr/X11R6/lib
            ${HPUX_IA_OPENGL_LIB_PATH}
    )

    # On Unix OpenGL most certainly always requires X11.
    # Feel free to tighten up these conditions if you don't 
    # think this is always true.
    # It's not true on OSX.

    IF (OPENGL_gl_LIBRARY)
      IF(NOT X11_FOUND)
        INCLUDE(FindX11)
      ENDIF(NOT X11_FOUND)
      IF (X11_FOUND)
        IF (NOT APPLE)
          SET (OPENGL_LIBRARIES ${X11_LIBRARIES})
        ENDIF (NOT APPLE)
      ENDIF (X11_FOUND)
    ENDIF (OPENGL_gl_LIBRARY)

    FIND_LIBRARY(OPENGL_glu_LIBRARY
      NAMES GLU MesaGLU
      PATHS ${OPENGL_gl_LIBRARY}
            /opt/graphics/OpenGL/lib
            /usr/openwin/lib
            /usr/shlib /usr/X11R6/lib
    )

  ENDIF(APPLE)
ENDIF (WIN32)

SET( OPENGL_FOUND "NO" )
IF(OPENGL_gl_LIBRARY)

    IF(OPENGL_xmesa_INCLUDE_DIR)
      SET( OPENGL_XMESA_FOUND "YES" )
    ELSE(OPENGL_xmesa_INCLUDE_DIR)
      SET( OPENGL_XMESA_FOUND "NO" )
    ENDIF(OPENGL_xmesa_INCLUDE_DIR)

    SET( OPENGL_LIBRARIES  ${OPENGL_gl_LIBRARY} ${OPENGL_LIBRARIES})
    IF(OPENGL_glu_LIBRARY)
      SET( OPENGL_GLU_FOUND "YES" )
      SET( OPENGL_LIBRARIES ${OPENGL_glu_LIBRARY} ${OPENGL_LIBRARIES} )
    ELSE(OPENGL_glu_LIBRARY)
      SET( OPENGL_GLU_FOUND "NO" )
    ENDIF(OPENGL_glu_LIBRARY)

    SET( OPENGL_FOUND "YES" )

    # This deprecated setting is for backward compatibility with CMake1.4

    SET (OPENGL_LIBRARY ${OPENGL_LIBRARIES})

ENDIF(OPENGL_gl_LIBRARY)

# This deprecated setting is for backward compatibility with CMake1.4
SET(OPENGL_INCLUDE_PATH ${OPENGL_INCLUDE_DIR})

MARK_AS_ADVANCED(
  OPENGL_INCLUDE_DIR
  OPENGL_xmesa_INCLUDE_DIR
  OPENGL_glu_LIBRARY
  OPENGL_gl_LIBRARY
)
