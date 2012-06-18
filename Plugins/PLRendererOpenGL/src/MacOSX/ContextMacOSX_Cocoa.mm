/*********************************************************\
 *  File: ContextMacOSX_Cocoa.h                          *
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
#include "PLRendererOpenGL/MacOSX/ContextMacOSX_Cocoa.h"


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
ContextMacOSX_Cocoa::ContextMacOSX_Cocoa(Renderer &cRenderer, uint32 nMultisampleAntialiasingSamples) : ContextMacOSX(cRenderer, nMultisampleAntialiasingSamples)
{
}

/**
*  @brief
*    Destructor
*/
ContextMacOSX_Cocoa::~ContextMacOSX_Cocoa()
{
}


//[-------------------------------------------------------]
//[ Public virtual Context methods                        ]
//[-------------------------------------------------------]
PLRenderer::SurfaceWindow *ContextMacOSX_Cocoa::CreateSurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen)
{
	return new SurfaceWindowMacOSX_Cocoa(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
