/*********************************************************\
 *  File: SurfaceTextureBuffer.h                         *
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


#ifndef __PLRENDEREROPENGL_SURFACETEXTUREBUFFER_H__
#define __PLRENDEREROPENGL_SURFACETEXTUREBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfaceTextureBuffer.h>
#include <PLRenderer/Renderer/ResourceHandler.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FrameBufferObject;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A OpenGL texture buffer renderer surface where we can render in
*/
class SurfaceTextureBuffer : public PLRenderer::SurfaceTextureBuffer {


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
		virtual ~SurfaceTextureBuffer();

		/**
		*  @brief
		*    Returns whether FBO is used or not
		*
		*  @return
		*    'true' if a FBO is used, else 'false'
		*/
		bool IsFBOUsed() const;

		/**
		*  @brief
		*    Sets a color render target
		*
		*  @param[in] nColorIndex
		*    Index of the color render target to set
		*  @param[in] pTextureBuffer
		*    Texture buffer to render in, can be a null pointer
		*/
		void SetColorRenderTarget(PLCore::uint8 nColorIndex, PLRenderer::TextureBuffer *pTextureBuffer);

		/**
		*  @brief
		*    Finishes the process
		*/
		void Finish();


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
		*  @param[in] cTextureBuffer
		*    Texture buffer bound to the this surface
		*  @param[in] nFlags
		*    Texture buffer surface flags (see EFlags)
		*  @param[in] nMaxColorTargets
		*    Maximum number of color render targets. This must be at least 1 - main renderer target color.
		*/
		SurfaceTextureBuffer(PLRenderer::Renderer &cRenderer, PLRenderer::TextureBuffer &cTexture,
							 PLCore::uint32 nFlags = Depth | Stencil, PLCore::uint8 nMaxColorTargets = 1);

		/*
		*  @brief
		*    Create a FBO
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool CreateFBO();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FrameBufferObject			*m_pFrameBufferObject;		/**< Nice frame buffer object, can be a null pointer */
		PLRenderer::ResourceHandler	 m_cTextureBufferHandler;	/**< Texture buffer to render in */
		PLCore::uint8			 	 m_nFace;					/**< Texture buffer face currently rendered in (cube map) */

		PLCore::List<PLRenderer::ResourceHandler*> m_lstTextureBufferHandler;


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::SurfaceTexture functions   ]
	//[-------------------------------------------------------]
	public:
		virtual PLRenderer::TextureBuffer *GetTextureBuffer() const override;
		virtual PLCore::uint8 GetTextureBufferFace() const override;
		virtual void TakeDepthBufferFromSurfaceTextureBuffer(PLRenderer::SurfaceTextureBuffer &cSurfaceTextureBuffer) override;


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Surface functions          ]
	//[-------------------------------------------------------]
	public:
		virtual PLMath::Vector2i GetSize() const override;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Surface functions         ]
	//[-------------------------------------------------------]
	private:
		virtual bool Init() override;
		virtual void DeInit() override;
		virtual bool MakeCurrent(PLCore::uint8 nFace = 0) override;
		virtual bool UnmakeCurrent() override;
		virtual bool Present() override;
		virtual void BackupDeviceData() override;
		virtual void RestoreDeviceData() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_SURFACETEXTUREBUFFER_H__
