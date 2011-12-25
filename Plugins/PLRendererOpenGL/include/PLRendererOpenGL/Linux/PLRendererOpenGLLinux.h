/*********************************************************\
 *  File: PLRendererOpenGLLinux.h                        *
 *      Linux definitions for PLRendererOpenGL
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


#ifndef __PLRENDEREROPENGL_LINUX_H__
#define __PLRENDEREROPENGL_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCoreLinuxIncludes.h>
#include "../../../../../External/Recommended/OpenGL/gl.h"
#include "../../../../../External/Recommended/OpenGL/glu.h"
#include "../../../../../External/Recommended/OpenGL/glext.h"


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// We need to undefine some OS defines to avoid name conflicts... :(
#undef None
#undef Always
#undef Success

// Missing OpenGL definitions
#ifndef GL_ATI_texture_compression_3dc
	#define GL_ATI_texture_compression_3dc			1
	#define GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI	0x8837
#endif


#endif // __PLRENDEREROPENGL_LINUX_H__
