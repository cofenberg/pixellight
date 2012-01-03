/*********************************************************\
 *  File: ContextMacOSX_X11.h                            *
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
#include "PLRendererOpenGL/MacOSX/SurfaceWindowMacOSX_Cocoa.h"
#include "PLRendererOpenGL/MacOSX/ContextMacOSX_X11.h"
#include <X11/Xutil.h>	// Include this after the rest, else we get OS definition issues, again 


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContextMacOSX_X11::ContextMacOSX_X11(Renderer &cRenderer) : ContextMacOSX(cRenderer),
	m_pDisplay(XOpenDisplay(nullptr))
{
}

/**
*  @brief
*    Destructor
*/
ContextMacOSX_X11::~ContextMacOSX_X11()
{
	// Is there a valid X server display connection?
	if (m_pDisplay) {
		// Close the X server display connection
		XCloseDisplay(m_pDisplay);
	}
}

/**
*  @brief
*    Returns the X server display connection
*/
Display *ContextMacOSX_X11::GetDisplay() const
{
	return m_pDisplay;
}


//[-------------------------------------------------------]
//[ Public virtual Context methods                        ]
//[-------------------------------------------------------]
PLRenderer::SurfaceWindow *ContextMacOSX_X11::CreateSurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen)
{
	// [TODO] This method should create an SurfaceWindowMacOSX_X11 instance
	return new SurfaceWindowMacOSX_Cocoa(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
