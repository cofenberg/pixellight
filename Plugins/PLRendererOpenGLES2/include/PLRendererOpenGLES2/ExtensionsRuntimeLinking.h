/*********************************************************\
 *  File: ExtensionsRuntimeLinking.h                     *
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


#ifndef __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
#define __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLRendererOpenGLES2/Extensions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES 2.0 extensions runtime linking
*/
class ExtensionsRuntimeLinking : public Extensions {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ExtensionsRuntimeLinking();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ExtensionsRuntimeLinking();

		/**
		*  @brief
		*    Initialize the supported extensions
		*
		*  @note
		*    - Do only call this method if the EGL functions initialization was successful ("glGetString()" is used)
		*      and there's an active render context
		*/
		void Init();


	//[-------------------------------------------------------]
	//[ Public virtual Extensions functions                   ]
	//[-------------------------------------------------------]
	public:
		///////////////////////////////////////////////////////////
		// Returns whether an extension is supported or not
		///////////////////////////////////////////////////////////
		// EXT
		virtual bool IsGL_EXT_texture_compression_s3tc() const override;
		virtual bool IsGL_EXT_texture_compression_latc() const override;
		virtual bool IsGL_EXT_texture_filter_anisotropic() const override;
		// AMD
		virtual bool IsGL_AMD_compressed_3DC_texture() const override;
		// OES
		virtual bool IsGL_OES_element_index_uint() const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// EXT
		bool m_bGL_EXT_texture_compression_s3tc;
		bool m_bGL_EXT_texture_compression_latc;
		bool m_bGL_EXT_texture_filter_anisotropic;
		// AMD
		bool m_bGL_AMD_compressed_3DC_texture;
		// OES
		bool m_bGL_OES_element_index_uint;


};


//[-------------------------------------------------------]
//[ EXT definitions                                       ]
//[-------------------------------------------------------]
// GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT		0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT	0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT	0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT	0x83F3

// GL_EXT_texture_compression_latc
#define GL_COMPRESSED_LUMINANCE_LATC1_EXT				0x8C70
#define GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT		0x8C71
#define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT			0x8C72
#define GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT	0x8C73

// GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF


//[-------------------------------------------------------]
//[ AMD definitions                                       ]
//[-------------------------------------------------------]
// GL_AMD_compressed_3DC_texture
#define GL_3DC_X_AMD	0x87F9
#define GL_3DC_XY_AMD	0x87FA


//[-------------------------------------------------------]
//[ OES definitions                                       ]
//[-------------------------------------------------------]
// GL_OES_element_index_uint
#define GL_UNSIGNED_INT	0x1405


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_EXTENSIONSRUNTIMELINKING_H__
