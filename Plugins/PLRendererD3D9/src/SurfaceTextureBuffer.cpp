/*********************************************************\
 *  File: SurfaceTextureBuffer.cpp                       *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/TextureBuffer2D.h"
#include "PLRendererD3D9/TextureBufferRectangle.h"
#include "PLRendererD3D9/TextureBufferCube.h"
#include "PLRendererD3D9/SurfaceTextureBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceTextureBuffer::~SurfaceTextureBuffer()
{
	// De-initialize
	DeInit();

	// Delete texture buffer
	if (m_cTextureBufferHandler.GetResource())
		delete m_cTextureBufferHandler.GetResource();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceTextureBuffer::SurfaceTextureBuffer(PLRenderer::Renderer &cRenderer, PLRenderer::TextureBuffer &cTextureBuffer, uint32 nFlags, uint8 nMaxColorTargets) :
	PLRenderer::SurfaceTextureBuffer(cRenderer, nFlags, nMaxColorTargets),
	m_pTextureSurface(nullptr),
	m_nFace(0)
{
	// Init data
	m_cTextureBufferHandler.SetResource(&cTextureBuffer);

	// Init
	Init();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceTextureBuffer functions ]
//[-------------------------------------------------------]
PLRenderer::TextureBuffer *SurfaceTextureBuffer::GetTextureBuffer() const
{
	return static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
}

uint8 SurfaceTextureBuffer::GetTextureBufferFace() const
{
	return m_nFace;
}

void SurfaceTextureBuffer::TakeDepthBufferFromSurfaceTextureBuffer(PLRenderer::SurfaceTextureBuffer &cSurfaceTextureBuffer)
{
	// Not implemented
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceTextureBuffer::GetSize() const
{
	// Return the size depending of the texture buffer type
	PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
	if (pTextureBuffer) {
		switch (pTextureBuffer->GetType()) {
			case PLRenderer::Resource::TypeTextureBuffer2D:
				return static_cast<PLRenderer::TextureBuffer2D*>(pTextureBuffer)->GetSize();

			// [TODO] TextureBufferRectangle currently not supported
//			case PLRenderer::Resource::TypeTextureBufferRectangle:
//				return static_cast<PLRenderer::TextureBufferRectangle*>(pTextureBuffer)->GetSize();

			case PLRenderer::Resource::TypeTextureBufferCube:
			{
				const uint32 nSize = static_cast<PLRenderer::TextureBufferCube*>(pTextureBuffer)->GetSize();
				return Vector2i(nSize, nSize);
			}
		}
	}

	// Error!
	return Vector2i::Zero;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceTextureBuffer::IsAPISwapY() const
{
	// Under D3D 9 we need to swap along the y axis. D3D is using a top-left corner,
	// OpenGL a bottom-left corner.
	return !IsSwapY();
}

bool SurfaceTextureBuffer::Init()
{
	// First de-initialize the old stuff
	DeInit();

	// Get renderer
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
	if (cRenderer.GetDevice()) {
		PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
		if (pTextureBuffer) {
			// Get API pixel format
			uint32 *pAPIPixelFormat = cRenderer.GetAPIPixelFormat(pTextureBuffer->GetFormat());
			if (pAPIPixelFormat) {
				// Check texture buffer type
				switch (pTextureBuffer->GetType()) {
					case PLRenderer::Resource::TypeTextureBuffer2D:
					{
						// Get texture surface
						LPDIRECT3DTEXTURE9 pD3D9Texture = static_cast<TextureBuffer2D*>(pTextureBuffer)->GetD3D9Texture();
						if (!pD3D9Texture || pD3D9Texture->GetSurfaceLevel(0, &m_pTextureSurface) != D3D_OK)
							return false; // Error!
						break;
					}

					case PLRenderer::Resource::TypeTextureBufferRectangle:
					{
						// Get texture surface
						LPDIRECT3DTEXTURE9 pD3D9Texture = static_cast<TextureBufferRectangle*>(pTextureBuffer)->GetD3D9Texture();
						if (!pD3D9Texture || pD3D9Texture->GetSurfaceLevel(0, &m_pTextureSurface) != D3D_OK)
							return false; // Error!
						break;
					}

					case PLRenderer::Resource::TypeTextureBufferCube:
						// m_pTextureSurface is set dynamically...
						break;

					default:
						return false; // Error!
				}

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

void SurfaceTextureBuffer::DeInit()
{
	if (m_pTextureSurface) {
		m_pTextureSurface->Release();
		m_pTextureSurface = nullptr;
	}
}

bool SurfaceTextureBuffer::MakeCurrent(uint8 nFace)
{
	// Get renderer
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
	if (cRenderer.GetDevice()) {
		// Begin scene
		PLRenderer::TextureBuffer *pTextureBuffer = static_cast<PLRenderer::TextureBuffer*>(m_cTextureBufferHandler.GetResource());
		if (pTextureBuffer) {
			if (pTextureBuffer->GetType() == PLRenderer::Resource::TypeTextureBufferCube) {
				// Get the cube texture
				LPDIRECT3DCUBETEXTURE9 pD3D9Texture = static_cast<TextureBufferCube*>(pTextureBuffer)->GetD3D9Texture();
				if (!pD3D9Texture)
					return false; // Error!

				// Release the previous cube map surface
				if (m_pTextureSurface) {
					m_pTextureSurface->Release();
					m_pTextureSurface = nullptr;
				}

				// Get the cube map surface to render in
				if (pD3D9Texture->GetCubeMapSurface((D3DCUBEMAP_FACES)nFace, 0, &m_pTextureSurface) != D3D_OK)
					return false; // Error!
			}

			// Is there a render to surface?
			if (m_pTextureSurface) {
				// Set the render target
				return cRenderer.GetDevice()->SetRenderTarget(0, m_pTextureSurface) == D3D_OK;
			}
		}
	}

	// Error!
	return false;
}

bool SurfaceTextureBuffer::UnmakeCurrent()
{
	// Nothing to do here...
	return true;
}

bool SurfaceTextureBuffer::Present()
{
	// Nothing to do here...
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9
