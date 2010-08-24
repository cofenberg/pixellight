/*********************************************************\
 *  File: TextureBufferCube.h                            *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDEREROPENGLES_TEXTUREBUFFERCUBE_H__
#define __PLRENDEREROPENGLES_TEXTUREBUFFERCUBE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <GLES2/gl2.h>
#include <PLRenderer/Renderer/TextureBufferCube.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES cube texture buffer resource
*/
class TextureBufferCube : public PLRenderer::TextureBufferCube {


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
		virtual ~TextureBufferCube();

		/**
		*  @brief
		*    Returns the OpenGL ES object of the texture buffer
		*
		*  @return
		*    OpenGL ES object of the texture buffer, no not delete the texture!
		*/
		GLuint GetOpenGLESTexture() const;


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
		*    Cube map image (image with 6 image parts)
		*  @param[in] nInternalFormat
		*    Desired internal texture buffer pixel format, if unknown use the format of the given image
		*  @param[in] nFlags
		*    Texture buffer flags (see EFlags)
		*
		*  @note
		*    - The image is assumed to be valid because it was already checked by the renderer texture buffer
		*      create function
		*/
		TextureBufferCube(PLRenderer::Renderer &cRenderer, PLGraphics::Image &cImage,
						  EPixelFormat nInternalFormat, PLGeneral::uint32 nFlags);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nSize
		*    Texture buffer image size
		*  @param[in] nInternalFormat
		*    Desired internal texture buffer pixel format
		*  @param[in] nFlags
		*    Texture buffer flags (see EFlags)
		*/
		TextureBufferCube(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nSize,
						  EPixelFormat nInternalFormat, PLGeneral::uint32 nFlags);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		GLuint m_nOpenGLESTexture;	/**< OpenGL ES texture, always valid! */


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


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_TEXTUREBUFFERCUBE_H__
