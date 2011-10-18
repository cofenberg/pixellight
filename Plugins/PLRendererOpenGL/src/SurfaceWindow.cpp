/*********************************************************\
 *  File: SurfaceWindow.cpp                              *
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
#ifdef WIN32
	#include <PLCore/PLCoreWindowsIncludes.h>
#endif
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/SurfaceWindow.h"
#ifdef APPLE
	// [TODO] Implement Mac OS X part
	//#include "PLRendererOpenGL/ContextMacOSX.h"
#elif LINUX
	#include "PLRendererOpenGL/ContextLinux.h"
#endif


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
SurfaceWindow::SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nNativeWindowHandle, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen) :
	PLRenderer::SurfaceWindow(cHandler, nNativeWindowHandle, bFullscreen),
	#ifdef WIN32
		m_hDC(nullptr),
	#endif
	#ifdef APPLE
		// [TODO] Implement Mac OS X part
	#elif LINUX
		m_nNativeWindowHandle(NULL_HANDLE),
		m_nOldSizeID(-1),
		m_nOldRotation(-1),
	#endif
		m_nSwapInterval(-1),
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
