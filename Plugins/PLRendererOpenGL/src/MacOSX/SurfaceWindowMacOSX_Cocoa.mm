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
#include <AppKit/NSOpenGL.h>
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/MacOSX/ContextMacOSX.h"
#include "PLRendererOpenGL/MacOSX/SurfaceWindowMacOSX_Cocoa.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
	// [TODO] This is just a test -> For now, do never ever go into fullscreen or we may have to restart the Mac Mini in order to close an appliation...
	SurfaceWindowMacOSX_X11(cHandler, nNativeWindowHandle, sDisplayMode, false),
//	SurfaceWindowMacOSX_X11(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen),
	m_pNSOpenGLContext(nullptr)
{
	// Initialize the OpenGL surface window
	Init();
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindowMacOSX_Cocoa::Init()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		return SurfaceWindowMacOSX_X11::Init();
	} else {
		// Get the MacOS X context implementation
		ContextMacOSX &cContextMacOSX = static_cast<ContextMacOSX&>(static_cast<Renderer&>(GetRenderer()).GetContext());

		// [TODO] Implement me
		// Obj-C style object creation
		NSOpenGLContext *pNSOpenGLContext = [[NSOpenGLContext alloc] initWithFormat:nullptr shareContext:nullptr];
//		m_pNSOpenGLContext = [[NSOpenGLContext alloc] initWithFormat:nullptr shareContext:cContextMacOSX.GetRenderContext()];

		// [TODO] Implement me
		return (m_pNSOpenGLContext != nullptr);
	}
}

void SurfaceWindowMacOSX_Cocoa::DeInit()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		SurfaceWindowMacOSX_X11::DeInit();
	} else {
		if (m_pNSOpenGLContext) {
			delete static_cast<NSOpenGLContext*>(m_pNSOpenGLContext);
			m_pNSOpenGLContext = nullptr;
			// [TODO] Implement me
		}
	}
}

bool SurfaceWindowMacOSX_Cocoa::MakeCurrent(uint8 nFace)
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		return SurfaceWindowMacOSX_X11::MakeCurrent(nFace);
	} else {
		// [TODO] Implement me
		return false;
	}
}

bool SurfaceWindowMacOSX_Cocoa::Present()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		return SurfaceWindowMacOSX_X11::Present();
	} else {
		// [TODO] Implement me
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
