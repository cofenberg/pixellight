/*********************************************************\
 *  File: SurfaceWindowMacOSX.cpp                        *
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
#include <OpenGL/OpenGL.h>
#include <ApplicationServices/ApplicationServices.h>	// "#include <CoreGraphics/CGDirectDisplay.h>" would do the job, but on Apple we're forced to use the "framework"-approach instead of addressing headers the natural way, and this one here is a "sub-framework" which can't be addressed directly, so we have to use this overkill approach and this really long comment
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/MacOSX/ContextMacOSX.h"
#include "PLRendererOpenGL/MacOSX/SurfaceWindowMacOSX.h"


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
SurfaceWindowMacOSX::~SurfaceWindowMacOSX()
{
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindowMacOSX::SurfaceWindowMacOSX(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen) :
	SurfaceWindow(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen)
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLRenderer::Surface functions       ]
//[-------------------------------------------------------]
bool SurfaceWindowMacOSX::Init()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Get the MacOS X context implementation
		ContextMacOSX &cContextMacOSX = static_cast<ContextMacOSX&>(static_cast<Renderer&>(GetRenderer()).GetContext());

		// [TODO] Switch to the requested resolution

		// Attach rendering context to a fullscreen drawable object
		return (CGLSetFullScreenOnDisplay(cContextMacOSX.GetRenderContext(), CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay)) == kCGLNoError);
	} else {
		// CGL only supports fullscreen rendering
	}

	// Error!
	return false;
}

void SurfaceWindowMacOSX::DeInit()
{
	// Is it fullscreen?
	if (m_bIsFullscreen) {
		// Get the MacOS X context implementation
		ContextMacOSX &cContextMacOSX = static_cast<ContextMacOSX&>(static_cast<Renderer&>(GetRenderer()).GetContext());

		// Disassociate rendering context from any drawable objects attached to it
		CGLClearDrawable(cContextMacOSX.GetRenderContext());

		// [TODO] Restore the previous resolution
	} else {
		// CGL only supports fullscreen rendering
	}
}

bool SurfaceWindowMacOSX::MakeCurrent(uint8 nFace)
{
	// Get the MacOS X context implementation
	ContextMacOSX &cContextMacOSX = static_cast<ContextMacOSX&>(static_cast<Renderer&>(GetRenderer()).GetContext());

	// Set the current rendering context
	return (CGLSetCurrentContext(cContextMacOSX.GetRenderContext())== kCGLNoError);;
}

bool SurfaceWindowMacOSX::Present()
{
	// Get the MacOS X context implementation
	ContextMacOSX &cContextMacOSX = static_cast<ContextMacOSX&>(static_cast<Renderer&>(GetRenderer()).GetContext());

	// Set the current rendering context
	return (CGLFlushDrawable(cContextMacOSX.GetRenderContext())== kCGLNoError);;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
