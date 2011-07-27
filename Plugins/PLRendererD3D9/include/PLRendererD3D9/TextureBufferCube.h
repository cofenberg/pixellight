/*********************************************************\
 *  File: TextureBufferCube.h                            *
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


#ifndef __PLRENDERERD3D9_TEXTUREBUFFERCUBE_H__
#define __PLRENDERERD3D9_TEXTUREBUFFERCUBE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/TextureBufferCube.h>
#include "PLRendererD3D9/PLRendererD3D9.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Direct3D 9 cube texture buffer resource
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
		*    Returns the Direct3D 9 texture
		*
		*  @return
		*    The Direct3D 9 texture, can be a null pointer
		*/
		LPDIRECT3DCUBETEXTURE9 GetD3D9Texture() const;


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
		TextureBufferCube(PLRenderer::Renderer &cRenderer, PLGraphics::Image &cImage, EPixelFormat nInternalFormat, PLCore::uint32 nFlags);

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
		TextureBufferCube(PLRenderer::Renderer &cRenderer, PLCore::uint32 nSize, EPixelFormat nInternalFormat, PLCore::uint32 nFlags);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		LPDIRECT3DCUBETEXTURE9 m_pD3D9Texture;	/**< Direct3D 9 texture, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::TextureBuffer functions    ]
	//[-------------------------------------------------------]
	public:
		virtual bool Upload(PLCore::uint32 nMipmap, EPixelFormat nFormat, const void *pData, PLCore::uint8 nFace = 0) override;
		virtual bool Download(PLCore::uint32 nMipmap, EPixelFormat nFormat, void *pData, PLCore::uint8 nFace = 0) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::TextureBuffer functions   ]
	//[-------------------------------------------------------]
	private:
		virtual bool MakeCurrent(PLCore::uint32 nStage) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLCore::uint8 **ppBackup) override;
		virtual void RestoreDeviceData(PLCore::uint8 **ppBackup) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_TEXTUREBUFFERCUBE_H__
