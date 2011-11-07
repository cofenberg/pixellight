/*********************************************************\
 *  File: SurfaceWindowMacOSXCocoa.mm                    *
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
//#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/MacOSX/ContextMacOSX.h"
#include "PLRendererOpenGL/MacOSX/SurfaceWindowMacOSXCocoa.h"
#include <AppKit/NSOpenGL.h>


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
SurfaceWindowMacOSXCocoa::~SurfaceWindowMacOSXCocoa()
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
SurfaceWindowMacOSXCocoa::SurfaceWindowMacOSXCocoa(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen) :
	// [TODO] This is just a test -> For now, do never ever go into fullscreen or we may have to restart the Mac Mini in order to close an appliation...
	SurfaceWindowMacOSX(cHandler, nNativeWindowHandle, sDisplayMode, false),
//	SurfaceWindowMacOSX(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen),
	m_pNSOpenGLContext(nullptr)
{
	// Initialize the OpenGL surface window
	Init();
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindowMacOSXCocoa::Init()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		return SurfaceWindowMacOSX::Init();
	} else {
		// Get the MacOS X context implementation
	//	ContextMacOSX *pContextMacOSX = static_cast<ContextMacOSX*>(static_cast<Renderer&>(GetRenderer()).GetContext());
	//	if (pContextMacOSX) {
			
			NSOpenGLContext *pNSOpenGLContext = [[NSOpenGLContext alloc] initWithFormat:nullptr shareContext:nullptr];
	
			//		m_pNSOpenGLContext = new NSOpenGLContext();
//			m_pNSOpenGLContext = [[NSOpenGLContext alloc] initWithFormat:pContextMacOSX->GetRenderContext() shareContext:shareContext]
	//	}

		// [TODO] Implement me
		return false;
	}
}

void SurfaceWindowMacOSXCocoa::DeInit()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		SurfaceWindowMacOSX::DeInit();
	} else {
		if (m_pNSOpenGLContext) {
			delete static_cast<NSOpenGLContext*>(m_pNSOpenGLContext);
			m_pNSOpenGLContext = nullptr;
			// [TODO] Implement me
		}
	}
}

bool SurfaceWindowMacOSXCocoa::MakeCurrent(uint8 nFace)
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		return SurfaceWindowMacOSX::MakeCurrent(nFace);
	} else {
		// [TODO] Implement me
		return false;
	}
}

bool SurfaceWindowMacOSXCocoa::Present()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Call base implementation
		return SurfaceWindowMacOSX::Present();
	} else {
		// [TODO] Implement me
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
