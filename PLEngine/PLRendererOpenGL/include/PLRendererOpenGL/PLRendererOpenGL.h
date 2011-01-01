/*********************************************************\
 *  File: PLRendererOpenGL.h                             *
 *      Main header file of this project
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


#ifndef __PLRENDEREROPENGL_PLRENDEREROPENGL_H__
#define __PLRENDEREROPENGL_PLRENDEREROPENGL_H__
#pragma once


/**
*  @mainpage PLRendererOpenGL
*
*  @section intro_sec Introduction
*
*  This is the PLRendererOpenGL API reference.
*/


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLRendererOpenGL/PLRendererOpenGLWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLRendererOpenGL/PLRendererOpenGLLinux.h"
#endif


//[-------------------------------------------------------]
//[ OpenGL extensions                                     ]
//[-------------------------------------------------------]
#ifndef GL_AMD_vertex_shader_tessellator
	#define GL_AMD_vertex_shader_tessellator 1
	#define GL_SAMPLER_BUFFER_AMD				0x9001
	#define GL_INT_SAMPLER_BUFFER_AMD			0x9002
	#define GL_UNSIGNED_INT_SAMPLER_BUFFER_AMD	0x9003
	#define GL_DISCRETE_AMD						0x9006
	#define GL_CONTINUOUS_AMD					0x9007
	#define GL_TESSELLATION_MODE_AMD			0x9004
	#define GL_TESSELLATION_FACTOR_AMD			0x9005
	#ifdef GL_GLEXT_PROTOTYPES
		GLAPI void APIENTRY glTessellationFactorAMD (GLfloat);
		GLAPI void APIENTRY glTessellationModeAMD   (GLenum);
	#endif /* GL_GLEXT_PROTOTYPES */
	typedef void (APIENTRYP PFNGLTESSELLATIONFACTORAMDPROC) (GLfloat param);
	typedef void (APIENTRYP PFNGLTESSELLATIONMODEAMDPROC)   (GLenum pname);
#endif


#endif // __PLRENDEREROPENGL_PLRENDEREROPENGL_H__
