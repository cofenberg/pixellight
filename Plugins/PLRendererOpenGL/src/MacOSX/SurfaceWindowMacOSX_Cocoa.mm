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
#include "PLRendererOpenGL/MacOSX/ContextMacOSX.h"
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
	SurfaceWindowMacOSX(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen)
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
