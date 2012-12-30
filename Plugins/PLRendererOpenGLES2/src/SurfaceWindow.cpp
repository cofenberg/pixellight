/*********************************************************\
 *  File: SurfaceWindow.cpp                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRendererOpenGLES2/Renderer.h"
#include "PLRendererOpenGLES2/SurfaceWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererOpenGLES2 {


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


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindow::SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, bool bFullscreen) :
	PLRenderer::SurfaceWindow(cHandler, nNativeWindowHandle, bFullscreen),
	m_hSurface(EGL_NO_SURFACE),
	m_nSwapInterval(-1)
{
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
	if (m_hSurface) {
		// Get the EGL display
		const EGLDisplay hDisplay = static_cast<Renderer&>(GetRenderer()).GetContext().GetEGLDisplay();

		// Query the width and height of the EGL surface
		EGLint nWidth, nHeight;
		eglQuerySurface(hDisplay, m_hSurface, EGL_WIDTH,  &nWidth);
		eglQuerySurface(hDisplay, m_hSurface, EGL_HEIGHT, &nHeight);

		// Done
		return Vector2i(nWidth, nHeight);
	}

	// Error
	return Vector2i::Zero;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindow::Init()
{
	// First check if theres a native window
	const handle nNativeWindowHandle = GetNativeWindowHandle();
	if (nNativeWindowHandle) {
		// Get the OpenGL ES renderer and context
		Renderer &cRendererOpenGLES = static_cast<Renderer&>(GetRenderer());
		Context  &cContext          = cRendererOpenGLES.GetContext();

		// Is this the native window passed into the renderer constructor?
		if (nNativeWindowHandle == cContext.GetNativeWindowHandle()) {
			// Yes, just use the already existing window surface
			m_hSurface = cContext.GetEGLDummySurface();
		} else {
			// Create window surface
			m_hSurface = eglCreateWindowSurface(cContext.GetEGLDisplay(),
												cContext.GetEGLConfig(),
												(EGLNativeWindowType)nNativeWindowHandle,	// Interesting - in here, we have an OS dependent cast issue when using C++ casts: While we would need
																							// reinterpret_cast<EGLNativeWindowType>(nNativeWindowHandle) under MS Windows ("HWND"), we would need static_cast<EGLNativeWindowType>(nNativeWindowHandle)
																							// under Linux ("int")... so, to avoid #ifdefs, we just use old school c-style casts in here...
												nullptr);
			if (m_hSurface == EGL_NO_SURFACE) {
				PL_LOG(Warning, "Could not create OpenGL ES surface")

				// Error!
				return false;
			}
		}
	}

	// Done
	return true;
}

void SurfaceWindow::DeInit()
{
	// Initialized?
	if (m_hSurface) {
		// Get the OpenGL ES renderer and context
		Renderer &cRendererOpenGLES = static_cast<Renderer&>(GetRenderer());
		Context  &cContext          = cRendererOpenGLES.GetContext();

		// Destroy the EGL surface, but only if we're created it
		if (m_hSurface != cContext.GetEGLDummySurface()) {
			// If this is the current render target, make the main window to the new current one
			if (cRendererOpenGLES.GetRenderTarget() == this) {
				// Make the internal dummy surface to the currently used one
				cContext.MakeCurrent(EGL_NO_SURFACE);
			}

			// Destroy the EGL surface
			eglDestroySurface(cContext.GetEGLDisplay(), m_hSurface);
		}
	}
}

bool SurfaceWindow::MakeCurrent(uint8 nFace)
{
	// Make this surface current
	return (static_cast<Renderer&>(GetRenderer()).GetContext().MakeCurrent(m_hSurface) == EGL_TRUE);
}

bool SurfaceWindow::UnmakeCurrent()
{
	// Make the internal dummy surface to the currently used one
	return (static_cast<Renderer&>(GetRenderer()).GetContext().MakeCurrent(EGL_NO_SURFACE) == EGL_TRUE);
}

bool SurfaceWindow::Present()
{
	// Get the OpenGL ES renderer
	Renderer &cRendererOpenGLES = static_cast<Renderer&>(GetRenderer());

	// Swap interval (vertical synchronization) setting changed? (this setting is connected with the window, therefore we must do this update for every window)
	if (m_nSwapInterval != static_cast<int>(cRendererOpenGLES.GetSwapInterval())) {
		m_nSwapInterval = cRendererOpenGLES.GetSwapInterval();
		if (cRendererOpenGLES.GetContext().GetEGLDisplay())
			eglSwapInterval(cRendererOpenGLES.GetContext().GetEGLDisplay(), m_nSwapInterval);
	}

	// Swap buffers
	return (cRendererOpenGLES.GetContext().GetEGLDisplay() && m_hSurface && eglSwapBuffers(cRendererOpenGLES.GetContext().GetEGLDisplay(), m_hSurface) == EGL_TRUE);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
