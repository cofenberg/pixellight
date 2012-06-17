/*********************************************************\
 *  File: SurfaceWindowMacOSX_Cocoa.mm                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#import <Cocoa/Cocoa.h>
#import <AppKit/NSOpenGL.h>
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/MacOSX/ContextMacOSX_Cocoa.h"
#include "PLRendererOpenGL/MacOSX/SurfaceWindowMacOSX_Cocoa.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceWindowMacOSX_Cocoa::~SurfaceWindowMacOSX_Cocoa()
{
	// De-initialize the OpenGL surface window
	DeInit();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindowMacOSX_Cocoa::SurfaceWindowMacOSX_Cocoa(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen) :
	SurfaceWindowMacOSX(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen),
	m_pNSOpenGLContext(nullptr)
{
	// Initialize the OpenGL surface window
	Init();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceWindow functions    ]
//[-------------------------------------------------------]
bool SurfaceWindowMacOSX_Cocoa::GetGamma(float &fRed, float &fGreen, float &fBlue) const
{
	// [TODO] Implement me

	// Error!
	return false;
}

bool SurfaceWindowMacOSX_Cocoa::SetGamma(float fRed, float fGreen, float fBlue)
{
	// [TODO] Implement me

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceWindowMacOSX_Cocoa::GetSize() const
{
	// Get the NSWindow instance
	NSWindow *pNSWindow = reinterpret_cast<NSWindow*>(GetNativeWindowHandle());

	// Is there a NSWindow instance?
	if (pNSWindow) {
		// Get the size of the NSWindow content area, meaning excluding the window border and title bar
		const NSSize sNSSize = [[pNSWindow contentView] frame].size;

		// Return the window size
		return Vector2i(sNSSize.width, sNSSize.height);
	} else {
		return Vector2i::Zero;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindowMacOSX_Cocoa::Init()
{
	// Get the NSWindow instance
	NSWindow *pNSWindow = reinterpret_cast<NSWindow*>(GetNativeWindowHandle());

	// Is there a NSWindow instance?
	if (pNSWindow) {
		// Get the OpenGL renderer context
		ContextMacOSX_Cocoa &cContextMacOSX_Cocoa = static_cast<ContextMacOSX_Cocoa&>(static_cast<Renderer&>(GetRenderer()).GetContext());

		// Get the CGL context
		CGLContextObj cCGLContextObj = cContextMacOSX_Cocoa.GetRenderContext();

		// Wrap the CGLContextObj into a NSOpenGLContex
		m_pNSOpenGLContext = [[NSOpenGLContext alloc] initWithCGLContextObj:cCGLContextObj];

		// Get the NSView from the NSWindow
		NSView *pNSView = [pNSWindow contentView];

		// Assign the NSView with the NSOpenGLContex
		[m_pNSOpenGLContext setView:pNSView];

		// Make the NSOpenGLContex to the currently used one
		[m_pNSOpenGLContext makeCurrentContext];

		{ // Set the CGL swap rectangle
			const NSRect sNSRect = [pNSView bounds];
			const GLint nRectangle[] = { sNSRect.origin.x, sNSRect.origin.y, sNSRect.size.width, sNSRect.size.height };
			CGLSetParameter(cCGLContextObj, kCGLCPSwapRectangle, nRectangle);
		}
	}

	// Error!
	return false;
}

void SurfaceWindowMacOSX_Cocoa::DeInit()
{
	// First check if there is a native window handle
	const handle nNativeWindowHandle = GetNativeWindowHandle();
	if (nNativeWindowHandle) {
		// We're going to perform a cruel act - so give OpenGL a chance to flush and finish it's data...
		// just so be on the safe side, you never now...
		glFinish();

		// If this is the current render target, make the main window to the new current one
		Renderer &cRenderer = static_cast<Renderer&>(GetRenderer());
		if (cRenderer.GetRenderTarget() == this)
			cRenderer.SetRenderTarget(nullptr);

		// Reset gamma - but only when the gamma was changed by using "SetGamma()"
		if (m_bGammaChanged) {
			SetGamma(m_fGammaBackup[0], m_fGammaBackup[1], m_fGammaBackup[2]);
			m_bGammaChanged = false;
		}

		// Release our NS OpenGL context
		if (m_pNSOpenGLContext) {
			[m_pNSOpenGLContext release];
			m_pNSOpenGLContext = nil;
		}
	}
}

bool SurfaceWindowMacOSX_Cocoa::MakeCurrent(uint8 nFace)
{
	// Is there a valid NSOpenGLContext instance?
	if (m_pNSOpenGLContext) {
		// Make the NSOpenGLContex to the currently used one
		[m_pNSOpenGLContext makeCurrentContext];

		// Done
		return true;
	}

	// Error!
	return false;
}

bool SurfaceWindowMacOSX_Cocoa::Present()
{
	// Is there a valid NSOpenGLContext instance?
	if (m_pNSOpenGLContext) {
		// Flush buffer (= swap front/back buffer)
		[m_pNSOpenGLContext flushBuffer];

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
