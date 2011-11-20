/*********************************************************\
 *  File: Extensions.h                                   *
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


#ifndef __PLRENDEREROPENGLES2_EXTENSIONS_H__
#define __PLRENDEREROPENGLES2_EXTENSIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract OpenGL ES extensions base class
*
*  @note
*    - Extensions are only optional, so do always take into account that an extension may not be available
*/
class Extensions {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Extensions();


	//[-------------------------------------------------------]
	//[ Public virtual Extensions functions                   ]
	//[-------------------------------------------------------]
	public:
		///////////////////////////////////////////////////////////
		// Returns whether an extension is supported or not
		///////////////////////////////////////////////////////////
		// ARB
		virtual bool IsGL_ARB_draw_buffers() const = 0;
		// EXT
		virtual bool IsGL_EXT_texture_compression_s3tc() const = 0;
		virtual bool IsGL_EXT_texture_compression_dxt1() const = 0;
		virtual bool IsGL_EXT_texture_compression_latc() const = 0;
		virtual bool IsGL_EXT_texture_filter_anisotropic() const = 0;
		virtual bool IsGL_EXT_texture_array() const = 0;
		virtual bool IsGL_EXT_Cg_shader() const = 0;
		// AMD
		virtual bool IsGL_AMD_compressed_3DC_texture() const = 0;
		// NV
		virtual bool IsGL_NV_get_tex_image() const = 0;
		virtual bool IsGL_NV_fbo_color_attachments() const = 0;
		virtual bool IsGL_NV_read_buffer() const = 0;
		// OES
		virtual bool IsGL_OES_mapbuffer() const = 0;
		virtual bool IsGL_OES_element_index_uint() const = 0;
		virtual bool IsGL_OES_texture_3D() const = 0;
		virtual bool IsGL_OES_packed_depth_stencil() const = 0;
		virtual bool IsGL_OES_depth24() const = 0;
		virtual bool IsGL_OES_depth32() const = 0;
		// ANGLE
		virtual bool IsGL_ANGLE_framebuffer_blit() const = 0;
		virtual bool IsGL_ANGLE_framebuffer_multisample() const = 0;


	//[-------------------------------------------------------]
	//[ Protected methods                                     ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		Extensions();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Extensions(const Extensions &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Extensions &operator =(const Extensions &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


//[-------------------------------------------------------]
//[ Implementation includes                               ]
//[-------------------------------------------------------]
#include "PLRendererOpenGLES2/ExtensionsRuntimeLinking.h"	// Required in here because we define the OpenGL ES 2.0 extension functions for dynamic runtime linking


#endif // __PLRENDEREROPENGLES2_EXTENSIONS_H__
