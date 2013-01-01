/*********************************************************\
 *  File: SurfaceWindow.cpp                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Log/Log.h>
#include <PLCore/System/SystemWindows.h>
#include "PLRendererD3D11/Renderer.h"
#include "PLRendererD3D11/SurfaceWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererD3D11 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceWindow::~SurfaceWindow()
{
	DeInit();
}

/**
*  @brief
*    Returns the DXGI swap chain
*/
IDXGISwapChain *SurfaceWindow::GetDXGISwapChain() const
{
	return m_pDXGISwapChain;
}

/**
*  @brief
*    Returns the D3D11 texture 2D back buffer
*/
ID3D11Texture2D *SurfaceWindow::GetD3D11Texture2DBackBuffer() const
{
	return m_pD3D11Texture2DBackBuffer;
}

/**
*  @brief
*    Returns the D3D11 render target view
*/
ID3D11RenderTargetView *SurfaceWindow::GetD3D11RenderTargetView() const
{
	return m_pD3D11RenderTargetView;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindow::SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, bool bFullscreen) :
	PLRenderer::SurfaceWindow(cHandler, nNativeWindowHandle, bFullscreen),
	m_pDXGISwapChain(nullptr),
	m_pD3D11Texture2DBackBuffer(nullptr),
	m_pD3D11RenderTargetView(nullptr)
{
	// Initialize data
	ZeroMemory(&m_sDXGISwapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	// Init
	Init();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceWindow functions    ]
//[-------------------------------------------------------]
bool SurfaceWindow::GetGamma(float &fRed, float &fGreen, float &fBlue) const
{
	// Error!
	return false;
}

bool SurfaceWindow::SetGamma(float fRed, float fGreen, float fBlue)
{
	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceWindow::GetSize() const
{
	if (GetNativeWindowHandle()) {
		#ifdef WIN32
			RECT sRect;
			GetClientRect(reinterpret_cast<HWND>(GetNativeWindowHandle()), &sRect);
			return Vector2i(sRect.right, sRect.bottom);
		#endif
	} else {
		return Vector2i::Zero;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindow::Init()
{
	// Get the D3D11 renderer instance and the relevant pointers
	Renderer      &cRenderer     = static_cast<Renderer&>(GetRenderer());
	IDXGIFactory1 *pDXGIFactory1 = cRenderer.GetDXGIFactory1();
	ID3D11Device  *pD3D11Device  = cRenderer.GetD3D11Device();
	if (pDXGIFactory1 && pD3D11Device) {
		// [TODO] VSync and fullscreen support
		// Fill DXGI swap chain description
		const Vector2i vWindowSize = GetSize();
		m_sDXGISwapChainDescription.BufferDesc.Width					= vWindowSize.x;
		m_sDXGISwapChainDescription.BufferDesc.Height					= vWindowSize.y;
		m_sDXGISwapChainDescription.BufferDesc.RefreshRate.Numerator	= 60;
		m_sDXGISwapChainDescription.BufferDesc.RefreshRate.Denominator	= 1;
		m_sDXGISwapChainDescription.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	//	m_sDXGISwapChainDescription.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;	// [TODO] For fullscreen
	//	m_sDXGISwapChainDescription.BufferDesc.Scaling					= DXGI_MODE_SCALING_STRETCHED;					// [TODO] For fullscreen
		m_sDXGISwapChainDescription.SampleDesc.Count					= 1;
		m_sDXGISwapChainDescription.SampleDesc.Quality					= 0;
		m_sDXGISwapChainDescription.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		m_sDXGISwapChainDescription.BufferCount							= 1;
		m_sDXGISwapChainDescription.OutputWindow						= reinterpret_cast<HWND>(GetNativeWindowHandle());
		m_sDXGISwapChainDescription.Windowed							= TRUE;
		m_sDXGISwapChainDescription.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
		m_sDXGISwapChainDescription.Flags								= 0;

		// Create the swap chain
		HRESULT hResult = pDXGIFactory1->CreateSwapChain(pD3D11Device, &m_sDXGISwapChainDescription, &m_pDXGISwapChain);
		if (SUCCEEDED(hResult)) {
			// Get the 2D back buffer texture
			hResult = m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&m_pD3D11Texture2DBackBuffer));
			if (SUCCEEDED(hResult)) {
				// Get the back buffer description
				D3D11_TEXTURE2D_DESC sD3D11Texture2DDescription;
				m_pD3D11Texture2DBackBuffer->GetDesc(&sD3D11Texture2DDescription);

				// Create the render target view
				D3D11_RENDER_TARGET_VIEW_DESC sD3D11RenderTargetViewDescription;
				ZeroMemory(&sD3D11RenderTargetViewDescription, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
				sD3D11RenderTargetViewDescription.Format				= sD3D11Texture2DDescription.Format;
				sD3D11RenderTargetViewDescription.ViewDimension			= D3D11_RTV_DIMENSION_TEXTURE2D;
				sD3D11RenderTargetViewDescription.Texture2D.MipSlice	= 0;
				hResult = pD3D11Device->CreateRenderTargetView(m_pD3D11Texture2DBackBuffer, &sD3D11RenderTargetViewDescription, &m_pD3D11RenderTargetView);

				// Done
				return SUCCEEDED(hResult);
			} else {
				// Error!
				PL_LOG(Error, "D3D11: Failed to get the 2D back buffer texture: " + SystemWindows::ErrorCodeToString(hResult))
			}
		} else {
			// Error!
			PL_LOG(Error, "D3D11: Failed to create swap chain: " + SystemWindows::ErrorCodeToString(hResult))
		}
	}

	// Error!
	return false;
}

void SurfaceWindow::DeInit()
{
	// If this is the current render target, make the main window to the new current one
	Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
	if (cRenderer.GetRenderTarget() == this)
		cRenderer.SetRenderTarget(nullptr);

	// Cleanup
	if (m_pD3D11RenderTargetView) {
		m_pD3D11RenderTargetView->Release();
		m_pD3D11RenderTargetView = nullptr;
	}
	if (m_pD3D11Texture2DBackBuffer) {
		m_pD3D11Texture2DBackBuffer->Release();
		m_pD3D11Texture2DBackBuffer = nullptr;
	}
	if (m_pDXGISwapChain) {
		m_pDXGISwapChain->Release();
		m_pDXGISwapChain = nullptr;
	}
}

bool SurfaceWindow::MakeCurrent(uint8 nFace)
{
	// Done
	return true;
}

bool SurfaceWindow::UnmakeCurrent()
{
	// Done
	return true;
}

bool SurfaceWindow::Present()
{
	return m_pDXGISwapChain ? SUCCEEDED(m_pDXGISwapChain->Present(GetRenderer().GetSwapInterval(), 0)) : false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D11
