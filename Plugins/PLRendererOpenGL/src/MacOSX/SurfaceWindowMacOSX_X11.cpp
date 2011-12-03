/*********************************************************\
 *  File: SurfaceWindowMacOSX_X11.cpp                    *
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
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/xf86vmode.h>
#undef None		// We undef this to avoid name conflicts (else we can't use it as e.g. class method name!)
#undef Always	// We undef this to avoid name conflicts (else we can't use it as e.g. class method name!)
#undef Success	// We undef this to avoid name conflicts (else we can't use it as e.g. class method name!)
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/MacOSX/ContextMacOSX_X11.h"
#include "PLRendererOpenGL/MacOSX/SurfaceWindowMacOSX_X11.h"


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
SurfaceWindowMacOSX_X11::~SurfaceWindowMacOSX_X11()
{
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindowMacOSX_X11::SurfaceWindowMacOSX_X11(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen) :
	SurfaceWindowMacOSX(cHandler, nNativeWindowHandle, sDisplayMode, bFullscreen)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceWindow functions    ]
//[-------------------------------------------------------]
bool SurfaceWindowMacOSX_X11::GetGamma(float &fRed, float &fGreen, float &fBlue) const
{
	// Get the MacOS X OpenGL render context
	ContextMacOSX_X11 &cContextMacOSX_X11 = static_cast<ContextMacOSX_X11&>(static_cast<Renderer&>(GetRenderer()).GetContext());

	// Get the X server display connection
	Display *pDisplay = cContextMacOSX_X11.GetDisplay();

	// Get gamma information
	XF86VidModeGamma sXF86VidModeGamma;
	if (XF86VidModeGetGamma(pDisplay, XDefaultScreen(pDisplay), &sXF86VidModeGamma)) {
		fRed   = sXF86VidModeGamma.red;
		fGreen = sXF86VidModeGamma.green;
		fBlue  = sXF86VidModeGamma.blue;

		// Done
		return true;
	}

	// Set fallback settings so that the reference parameters are never within an undefined state
	fRed   = 0.0f;
	fGreen = 0.0f;
	fBlue  = 0.0f;

	// Error!
	return false;
}

bool SurfaceWindowMacOSX_X11::SetGamma(float fRed, float fGreen, float fBlue)
{
	if (static_cast<int>(fRed*10) <= 10 && static_cast<int>(fGreen*10) <= 10 && static_cast<int>(fBlue*10) <= 10) {
		// Get the MacOS X OpenGL render context
		ContextMacOSX_X11 &cContextMacOSX_X11 = static_cast<ContextMacOSX_X11&>(static_cast<Renderer&>(GetRenderer()).GetContext());

		// Get the X server display connection
		Display *pDisplay = cContextMacOSX_X11.GetDisplay();

		// Gamma was changed...
		m_bGammaChanged = true;

		// Call the OS gamma ramp function
		XF86VidModeGamma sXF86VidModeGamma;
		sXF86VidModeGamma.red   = fRed;
		sXF86VidModeGamma.green = fGreen;
		sXF86VidModeGamma.blue  = fBlue;
		if (XF86VidModeSetGamma(pDisplay, XDefaultScreen(pDisplay), &sXF86VidModeGamma))
			return true; // Done
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceWindowMacOSX_X11::GetSize() const
{
	if (GetNativeWindowHandle()) {
		::Window nRootWindow = 0;
		int nPositionX = 0, nPositionY = 0;
		unsigned int nWidth = 0, nHeight = 0, nBorder = 0, nDepth = 0;

		// Get the MacOS X context implementation
		ContextMacOSX_X11 &cContextMacOSX_X11 = static_cast<ContextMacOSX_X11&>(static_cast<Renderer&>(GetRenderer()).GetContext());

		// Get the X server display connection
		Display *pDisplay = cContextMacOSX_X11.GetDisplay();
		if (pDisplay) {
			// Get X window geometry information
			XGetGeometry(pDisplay, GetNativeWindowHandle(), &nRootWindow, &nPositionX, &nPositionY, &nWidth, &nHeight, &nBorder, &nDepth);
		}

		// Return the window size
		return Vector2i(nWidth, nHeight);
	} else {
		return Vector2i::Zero;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
