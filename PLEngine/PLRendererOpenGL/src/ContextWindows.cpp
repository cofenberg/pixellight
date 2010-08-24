/*********************************************************\
 *  File: ContextWindows.h                               *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Log/Log.h>
#include <PLGeneral/Container/Array.h>
#include <PLRenderer/Renderer/Types.h>
#include "PLRendererOpenGL/PLRendererOpenGLWindows.h"
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/ContextWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContextWindows::ContextWindows(Renderer &cRenderer, uint32 nMultisampleAntialiasingSamples) :
	m_pRenderer(&cRenderer),
	m_hDummyWindow(NULL),
	m_hDummyWindowDeviceContext(NULL),
	m_hDummyWindowRenderContext(NULL)
{
	// Setup and register the window class for the OpenGL dummy window
	WNDCLASS sWindowDummyClass;
	sWindowDummyClass.hInstance		= GetModuleHandle(NULL);
	sWindowDummyClass.lpszClassName	= TEXT("PLOpenGLDummyNativeWindow");
	sWindowDummyClass.lpfnWndProc	= DefWindowProc;
	sWindowDummyClass.style			= 0;
	sWindowDummyClass.hIcon			= NULL;
	sWindowDummyClass.hCursor		= NULL;
	sWindowDummyClass.lpszMenuName	= NULL;
	sWindowDummyClass.cbClsExtra	= 0;
	sWindowDummyClass.cbWndExtra	= 0;
	sWindowDummyClass.hbrBackground	= NULL;
	RegisterClass(&sWindowDummyClass);

	// Create the OpenGL dummy window
	m_hDummyWindow = CreateWindow(TEXT("PLOpenGLDummyNativeWindow"), TEXT("PFormat"), WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 8, 8, HWND_DESKTOP, NULL, GetModuleHandle(NULL), NULL);
	if (m_hDummyWindow != NULL) {
		// Get the device context of the OpenGL dummy window
		m_hDummyWindowDeviceContext = GetDC(m_hDummyWindow);
		if (m_hDummyWindowDeviceContext != NULL) {
			// Get the color depth of the deskop
			int nBits = 0;
			{
				HDC hDeskTopDC = GetDC(NULL);
				nBits = GetDeviceCaps(hDeskTopDC, BITSPIXEL);
				ReleaseDC(NULL, hDeskTopDC);
			}

			// Get the first best pixel format
			const PIXELFORMATDESCRIPTOR sPixelFormatDescriptor = {
				sizeof(PIXELFORMATDESCRIPTOR),					// Size of this pixel format descriptor
				1,												// Version number
				PFD_DRAW_TO_WINDOW |							// Format must support window
				PFD_SUPPORT_OPENGL |							// Format must support OpenGL
				PFD_DOUBLEBUFFER,								// Must support double buffering
				PFD_TYPE_RGBA,									// Request an RGBA format
				(UCHAR)nBits,									// Select our color depth
				0, 0, 0, 0, 0, 0,								// Color bits ignored
				0,												// No alpha buffer
				0,												// Shift bit ignored
				0,												// No accumulation buffer
				0, 0, 0, 0,										// Accumulation bits ignored
				(BYTE)cRenderer.GetCapabilities().nZBufferBits,	// Z-buffer (depth buffer)
				(BYTE)cRenderer.GetCapabilities().nStencilBits,	// Stencil buffer bits
				0,												// No auxiliary buffer
				PFD_MAIN_PLANE,									// Main drawing layer
				0,												// Reserved
				0, 0, 0											// Layer masks ignored
			};
			const int nPixelFormat = ChoosePixelFormat(m_hDummyWindowDeviceContext, &sPixelFormatDescriptor);
			if (nPixelFormat != 0) {
				// Set the pixel format
				SetPixelFormat(m_hDummyWindowDeviceContext, nPixelFormat, &sPixelFormatDescriptor);

				// Create a OpenGL render context
				m_hDummyWindowRenderContext = wglCreateContext(m_hDummyWindowDeviceContext);
				if (m_hDummyWindowRenderContext != NULL) {
					// Make the OpenGL render context to the current one
					wglMakeCurrent(m_hDummyWindowDeviceContext, m_hDummyWindowRenderContext);

					// Looks like the following is only required for multisample antialiasing
					if (nMultisampleAntialiasingSamples) {
						// This is somewhat stupied, but I don't see another solution... wglChoosePixelFormatARB etc. can only be received if
						// a OpenGL context was already loaded (probably delayed dll loading?)
						wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");
						wglChoosePixelFormatARB		 = (PFNWGLCHOOSEPIXELFORMATARBPROC)		wglGetProcAddress("wglChoosePixelFormatARB");
						if (wglGetPixelFormatAttribivARB && wglChoosePixelFormatARB) {
							// Search for a suitable pixel format
							int nAttribs[] = {
								WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
								WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
								WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
								WGL_COLOR_BITS_ARB,     nBits,
								WGL_DEPTH_BITS_ARB,     cRenderer.GetCapabilities().nZBufferBits,
								WGL_STENCIL_BITS_ARB,   cRenderer.GetCapabilities().nStencilBits,
								WGL_ACCUM_BITS_ARB,     0,
								WGL_SAMPLE_BUFFERS_ARB, nMultisampleAntialiasingSamples ? GL_TRUE : GL_FALSE,
								WGL_SAMPLES_ARB,        nMultisampleAntialiasingSamples,
								0,						0
							};
							int nPixelFormats[256];
							uint32 nPFormats = 0;
							int nBestFormat  = 0;
							int nBestSamples = 0;

							// Test through multiple color bits in case the desired value is not available
							int nCurrentBits = nBits;
							while (nCurrentBits && (!wglChoosePixelFormatARB(m_hDummyWindowDeviceContext, nAttribs, NULL, sizeof(nPixelFormats)/sizeof(int), nPixelFormats, &nPFormats) || !nPFormats)) {
								switch (nCurrentBits) {
									case 32:
										nCurrentBits = 24;
										break;

									case 24:
										nCurrentBits = 16;
										break;

									case 16:
									default:
										nCurrentBits = 0;
										break;
								}
								nAttribs[7] = nCurrentBits;	// Select our color depth
							}
							if (nPFormats) {
								int nMinDiff = 0x7FFFFFFF;
								int nAttrib  = WGL_SAMPLES_ARB;
								int nSamples;

								// Search for the pixel format with the closest number of multisample samples to the requested
								for (uint32 i=0; i<nPFormats; i++) {
									wglGetPixelFormatAttribivARB(m_hDummyWindowDeviceContext, nPixelFormats[i], 0, 1, &nAttrib, &nSamples);
									int nDiff = Math::Abs(nSamples - (int)nMultisampleAntialiasingSamples);
									if (nDiff < nMinDiff) {
										nMinDiff	 = nDiff;
										nBestFormat  = i;
										nBestSamples = nSamples;
									}
								}
							} else {
								// Use fallback
								nPixelFormats[0] = ChoosePixelFormat(m_hDummyWindowDeviceContext, &sPixelFormatDescriptor);
								if (!nPixelFormats[0]) { // Did Windows find a matching pixel format?
									// Error!
									return;
								}
							}

							// Enable multisampling
							if (nBestSamples > 0)
								glEnable(GL_MULTISAMPLE_ARB);

							// Set the pixel format... we can't set a pixel format if a pixel format was already set, so start all over again...
							wglMakeCurrent(NULL, NULL);
							wglDeleteContext(m_hDummyWindowRenderContext);
							ReleaseDC(m_hDummyWindow, m_hDummyWindowDeviceContext);
							DestroyWindow(m_hDummyWindow);
							m_hDummyWindow = CreateWindow(TEXT("PLOpenGLDummyNativeWindow"), TEXT("PFormat"), WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 8, 8, HWND_DESKTOP, NULL, GetModuleHandle(NULL), NULL);
							if (m_hDummyWindow != NULL) {
								m_hDummyWindowDeviceContext = GetDC(m_hDummyWindow);
								if (m_hDummyWindowDeviceContext != NULL) {
									SetPixelFormat(m_hDummyWindowDeviceContext, nPixelFormats[nBestFormat], &sPixelFormatDescriptor);
									m_hDummyWindowRenderContext = wglCreateContext(m_hDummyWindowDeviceContext);
									if (m_hDummyWindowRenderContext != NULL) {
										// Make the OpenGL render context to the current one
										wglMakeCurrent(m_hDummyWindowDeviceContext, m_hDummyWindowRenderContext);
									}
								}
							}
						}
					}
				} else {
					// Error, failed to create a OpenGL render context!
				}
			} else {
				// Error, failed to choose a pixel format!
			}
		} else {
			// Error, failed to obtain the device context of the OpenGL dummy window!
		}
	} else {
		// Error, failed to create the OpenGL dummy window!
	}
}

/**
*  @brief
*    Destructor
*/
ContextWindows::~ContextWindows()
{
	// Destroy the OpenGL dummy window
	if (m_hDummyWindow != NULL) {
		// Release the device context of the OpenGL dummy window
		if (m_hDummyWindowDeviceContext != NULL) {
			// Is the device context of the OpenGL dummy window is the currently active OpenGL device context?
			if (wglGetCurrentDC() == m_hDummyWindowDeviceContext)
				wglMakeCurrent(NULL, NULL);

			// Destroy the render context of the OpenGL dummy window
			if (m_hDummyWindowRenderContext != NULL)
				wglDeleteContext(m_hDummyWindowRenderContext);

			// Release the device context of the OpenGL dummy window
			ReleaseDC(m_hDummyWindow, m_hDummyWindowDeviceContext);
		}

		// Destroy the OpenGL dummy window
		DestroyWindow(m_hDummyWindow);
	}

	// Unregister the window class for the OpenGL dummy window
	UnregisterClass(TEXT("PLOpenGLDummyNativeWindow"), GetModuleHandle(NULL));
}

/**
*  @brief
*    Returns the primary device context
*/
HDC ContextWindows::GetDeviceContext() const
{
	return m_hDummyWindowDeviceContext;
}

/**
*  @brief
*    Returns the primary render context
*/
HGLRC ContextWindows::GetRenderContext() const
{
	return m_hDummyWindowRenderContext;
}


//[-------------------------------------------------------]
//[ Public virtual Context methods                        ]
//[-------------------------------------------------------]
bool ContextWindows::IsValid() const
{
	return (m_hDummyWindow != NULL && m_hDummyWindowDeviceContext != NULL && m_hDummyWindowRenderContext != NULL);
}

void ContextWindows::MakeDummyCurrent() const
{
	wglMakeCurrent(m_hDummyWindowDeviceContext, m_hDummyWindowRenderContext);
}

bool ContextWindows::QueryDisplayModes(Array<const PLRenderer::DisplayMode*> &lstDisplayModeList)
{
	uint32 nDisplayMode = 0;
	DEVMODE DevMode;
	String sTemp;

	// Clear old list of display modes
	for (uint32 i=0; i<lstDisplayModeList.GetNumOfElements(); i++)
		delete lstDisplayModeList[i];
	lstDisplayModeList.Clear();

	// Get list of display modes
	PL_LOG(Info, "Query available display modes")
	while (EnumDisplaySettings(NULL, nDisplayMode++, &DevMode)) {
		// First at all, we're only interested in some of the settings - as a result, we really should check if there's
		// already a display mode within our list with the interesting settings of the current found display mode
		bool bNewMode = true;
		for (uint32 i=0; i<lstDisplayModeList.GetNumOfElements(); i++) {
			const PLRenderer::DisplayMode *pDisplayMode = lstDisplayModeList[i];
			if (pDisplayMode->vSize.x == DevMode.dmPelsWidth && pDisplayMode->vSize.y == DevMode.dmPelsHeight &&
				pDisplayMode->nColorBits == DevMode.dmBitsPerPel && pDisplayMode->nFrequency == DevMode.dmDisplayFrequency) {
				// We already have such a display mode within our list!
				bNewMode = false;

				// Get us out of this loop right now!
				i = lstDisplayModeList.GetNumOfElements();
			}
		}
		if (bNewMode) {
			// Get required information
			PLRenderer::DisplayMode *pDisplayMode = new PLRenderer::DisplayMode;
			pDisplayMode->vSize.x	 = DevMode.dmPelsWidth;
			pDisplayMode->vSize.y	 = DevMode.dmPelsHeight;
			pDisplayMode->nColorBits = DevMode.dmBitsPerPel;
			pDisplayMode->nFrequency = DevMode.dmDisplayFrequency;

			// Give out log message
			if (pDisplayMode->nFrequency) {
				sTemp = String::Format("Found: %dx%dx%d %d Hz", pDisplayMode->vSize.x, pDisplayMode->vSize.y,
																pDisplayMode->nColorBits, pDisplayMode->nFrequency);
			} else {
				sTemp = String::Format("Found: %dx%dx%d", pDisplayMode->vSize.x, pDisplayMode->vSize.y, pDisplayMode->nColorBits);
			}

			// Add found display mode to list
			PL_LOG(Info, sTemp)
			lstDisplayModeList.Add(pDisplayMode);
		}
	}

	// Was at least one display mode found?
	if (lstDisplayModeList.IsEmpty()) {
		PL_LOG(Error, "No available & supported display modes found!")

		// Error!
		return false;
	}

	// Done
	return true;
}

void ContextWindows::SwapInterval(bool bEnabled)
{
	if (m_pRenderer->IsWGL_EXT_swap_control()) 
		wglSwapIntervalEXT(bEnabled);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
