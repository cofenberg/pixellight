/*********************************************************\
 *  File: SurfaceWindow.h                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERERD3D11_SURFACE_WINDOW_H__
#define __PLRENDERERD3D11_SURFACE_WINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfaceWindow.h>
#include "PLRendererD3D11/PLRendererD3D11.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D11 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A D3D11 window renderer surface where we can render in
*/
class SurfaceWindow : public PLRenderer::SurfaceWindow {


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
		virtual ~SurfaceWindow();

		/**
		*  @brief
		*    Returns the DXGI swap chain
		*
		*  @return
		*    The DXGI swap chain, can be a null pointer
		*/
		IDXGISwapChain *GetDXGISwapChain() const;

		/**
		*  @brief
		*    Returns the D3D11 texture 2D back buffer
		*
		*  @return
		*    The D3D11 texture 2D back buffer, can be a null pointer
		*/
		ID3D11Texture2D *GetD3D11Texture2DBackBuffer() const;

		/**
		*  @brief
		*    Returns the D3D11 render target view
		*
		*  @return
		*    The D3D11 render target view, can be a null pointer
		*/
		ID3D11RenderTargetView *GetD3D11RenderTargetView() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHandler
		*    Renderer surface handler this surface is assigned with (MUST be valid!)
		*  @param[in] nNativeWindowHandle
		*    Handle to the native window the renderer surface is assigned with
		*  @param[in] bFullscreen
		*    Fullscreen mode?
		*/
		SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, PLCore::handle nNativeWindowHandle, bool bFullscreen = false);


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::SurfaceWindow functions    ]
	//[-------------------------------------------------------]
	public:
		virtual bool GetGamma(float &fRed, float &fGreen, float &fBlue) const override;
		virtual bool SetGamma(float fRed = 1.0f, float fGreen = 1.0f, float fBlue = 1.0f) override;


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		IDXGISwapChain			*m_pDXGISwapChain;				/**< DXGI swap chain, can be a null pointer */
		DXGI_SWAP_CHAIN_DESC	 m_sDXGISwapChainDescription;	/**< DXGI swap chain description */
		ID3D11Texture2D			*m_pD3D11Texture2DBackBuffer;	/**< D3D11 texture 2D back buffer, can be a null pointer */
		ID3D11RenderTargetView	*m_pD3D11RenderTargetView;		/**< D3D11 render target view, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D11


#endif // __PLRENDERERD3D11_SURFACE_WINDOW_H__
