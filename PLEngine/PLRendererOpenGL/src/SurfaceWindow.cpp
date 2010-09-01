/*********************************************************\
 *  File: SurfaceWindow.cpp                              *
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
#ifdef WIN32
	#include <PLGeneral/PLGeneralWindowsIncludes.h>
#endif
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/SurfaceWindow.h"
#ifdef LINUX
	#include "PLRendererOpenGL/ContextLinux.h"
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceWindow::~SurfaceWindow()
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
SurfaceWindow::SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nWindow, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen) :
	PLRenderer::SurfaceWindow(cHandler, nWindow, bFullscreen),
	#ifdef WIN32
		m_hDC(NULL),
	#endif
	#ifdef LINUX
		m_nWindow(NULL),
	#endif
		m_bGammaChanged(false)
{
	// Initialize gamma backup
	m_fGammaBackup[0] = m_fGammaBackup[1] = m_fGammaBackup[2] = 0.0f;

	// Just copy over the given information
	m_sDisplayMode = sDisplayMode;

	// Initialize the OpenGL surface window
	Init();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceWindow::GetSize() const
{
	if (GetWindow()) {
		#ifdef WIN32
			RECT sRect;
			GetClientRect((HWND)GetWindow(), &sRect);
			return Vector2i(sRect.right, sRect.bottom);
		#endif
		#ifdef LINUX
			::Window nRootWindow = 0;
			int nPositionX = 0, nPositionY = 0;
			unsigned int nWidth = 0, nHeight = 0, nBorder = 0, nDepth = 0;

			// Get the Linux context implementation
			ContextLinux *pContextLinux = (ContextLinux*)((Renderer&)GetRenderer()).GetContext();
			if (pContextLinux) {
				// Get the X server display connection
				Display *pDisplay = pContextLinux->GetDisplay();
				if (pDisplay) {
					// Get X window geometry information
					XGetGeometry(pDisplay, GetWindow(), &nRootWindow, &nPositionX, &nPositionY, &nWidth, &nHeight, &nBorder, &nDepth);
				}
			}

			// Return the window size
			return Vector2i(nWidth, nHeight);
		#endif
	} else {
		return Vector2i::Zero;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
