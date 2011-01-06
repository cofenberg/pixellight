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


#ifndef __PLRENDERERD3D9_SURFACETEXTUREBUFFER_H__
#define __PLRENDERERD3D9_SURFACETEXTUREBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfaceTextureBuffer.h>
#include <PLRenderer/Renderer/ResourceHandler.h>
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
*    A Direct3D 9 texture buffer renderer surface where we can render in
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
		SurfaceTextureBuffer(PLRenderer::Renderer &cRenderer, PLRenderer::TextureBuffer &cTextureBuffer,
							 PLGeneral::uint32 nFlags = Depth | Stencil, PLGeneral::uint8 nMaxColorTargets = 1);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		LPDIRECT3DSURFACE9			m_pTextureSurface;			/**< Texture surface to render in, can be a null pointer */
		PLRenderer::ResourceHandler m_cTextureBufferHandler;	/**< Texture buffer to render in */
		PLGeneral::uint8			m_nFace;					/**< Texture buffer face currently rendered in (cube map) */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::SurfaceTextureBuffer functions ]
	//[-------------------------------------------------------]
	public:
		virtual PLRenderer::TextureBuffer *GetTextureBuffer() const;
		virtual PLGeneral::uint8 GetTextureBufferFace() const;
		virtual void TakeDepthBufferFromSurfaceTextureBuffer(PLRenderer::SurfaceTextureBuffer &cSurfaceTextureBuffer);


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Surface functions          ]
	//[-------------------------------------------------------]
	public:
		virtual PLMath::Vector2i GetSize() const;
		virtual bool IsAPISwapY() const;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Surface functions         ]
	//[-------------------------------------------------------]
	private:
		virtual bool Init();
		virtual void DeInit();
		virtual bool MakeCurrent(PLGeneral::uint8 nFace = 0);
		virtual bool UnmakeCurrent();
		virtual bool Present();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_SURFACETEXTUREBUFFER_H__
