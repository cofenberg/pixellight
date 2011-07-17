/*********************************************************\
 *  File: TextureBuffer1D.h                              *
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


#ifndef __PLRENDEREROPENGL_TEXTUREBUFFER1D_H__
#define __PLRENDEREROPENGL_TEXTUREBUFFER1D_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Types.h>
#include <PLRenderer/Renderer/TextureBuffer1D.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL 1D texture buffer resource
*/
class TextureBuffer1D : public PLRenderer::TextureBuffer1D {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDEREROPENGL_API virtual ~TextureBuffer1D();

		/**
		*  @brief
		*    Returns the OpenGL resource ID of the texture buffer
		*
		*  @return
		*    OpenGL resource ID of the texture buffer
		*/
		PLRENDEREROPENGL_API PLGeneral::uint32 GetOpenGLTexture() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] cImage
		*    Texture buffer image
		*  @param[in] nInternalFormat
		*    Desired internal texture buffer pixel format, if unknown use the format of the given image
		*  @param[in] nFlags
		*    Texture buffer flags (see EFlags)
		*
		*  @note
		*    - The image is assumed to be valid because it was already checked by the renderer texture buffer
		*      create function
		*/
		TextureBuffer1D(PLRenderer::Renderer &cRenderer, PLGraphics::Image &cImage, EPixelFormat nInternalFormat, PLGeneral::uint32 nFlags);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32 m_nOpenGLTexture;								/**< OpenGL texture ID */
		PLGeneral::uint32 m_nSamplerState[PLRenderer::Sampler::Number];	/**< Sampler states of this texture */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::TextureBuffer functions    ]
	//[-------------------------------------------------------]
	public:
		virtual bool Upload(PLGeneral::uint32 nMipmap, EPixelFormat nFormat, const void *pData, PLGeneral::uint8 nFace = 0);
		virtual bool Download(PLGeneral::uint32 nMipmap, EPixelFormat nFormat, void *pData, PLGeneral::uint8 nFace = 0);


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::TextureBuffer functions   ]
	//[-------------------------------------------------------]
	private:
		virtual bool MakeCurrent(PLGeneral::uint32 nStage);


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_TEXTUREBUFFER1D_H__
