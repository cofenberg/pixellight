/*********************************************************\
 *  File: SurfaceWindow.h                                *
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
#include "PLRenderer/Renderer/SurfaceWindowHandler.h"
#include "PLRenderer/Renderer/SurfaceHandler.h"
#include "PLRenderer/Renderer/SurfaceWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceWindow::~SurfaceWindow()
{
	// Clean up the surface
	if (m_pHandler) {
		// Inform handler
		m_pHandler->m_pSurfaceHandler->SetSurface(nullptr);
	}
}

/**
*  @brief
*    Returns the renderer surface handler this surface is assigned with
*/
SurfaceWindowHandler *SurfaceWindow::GetHandler() const
{
	return m_pHandler;
}

/**
*  @brief
*    Returns the window the surface is assigned with
*/
handle SurfaceWindow::GetWindow() const
{
	return m_nWindow;
}

/**
*  @brief
*    Returns whether the window is in fullscreen mode or not
*/
bool SurfaceWindow::IsFullscreen() const
{
	return m_bIsFullscreen;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindow::SurfaceWindow(SurfaceWindowHandler &cHandler, handle nWindow, bool bFullscreen) :
	Surface(*cHandler.GetRenderer(), Surface::Window),
	m_bIsFullscreen(bFullscreen),
	m_pHandler(&cHandler),
	m_nWindow(nWindow)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
SurfaceWindow::SurfaceWindow(const SurfaceWindow &cSource) : Surface(cSource.GetRenderer(), cSource.GetType()),
	m_bIsFullscreen(cSource.IsFullscreen()),
	m_pHandler(cSource.GetHandler()),
	m_nWindow(cSource.GetWindow())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
SurfaceWindow &SurfaceWindow::operator =(const SurfaceWindow &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer