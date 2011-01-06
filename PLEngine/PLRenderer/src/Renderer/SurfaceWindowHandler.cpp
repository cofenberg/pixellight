/*********************************************************\
 *  File: SurfaceWindowHandler.cpp                       *
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
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/SurfaceHandler.h"
#include "PLRenderer/Renderer/SurfaceWindow.h"
#include "PLRenderer/Renderer/SurfaceWindowHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindowHandler::SurfaceWindowHandler() :
	m_pRenderer(nullptr),
	m_pSurfaceHandler(new SurfaceHandler())
{
}

/**
*  @brief
*    Destructor
*/
SurfaceWindowHandler::~SurfaceWindowHandler()
{
	// Destroy the renderer surface
	DeInit();
	delete m_pSurfaceHandler;
}

/**
*  @brief
*    Returns the owner renderer
*/
Renderer *SurfaceWindowHandler::GetRenderer() const
{
	return m_pRenderer;
}

/**
*  @brief
*    Returns the renderer surface of this handler
*/
Surface *SurfaceWindowHandler::GetSurface() const
{
	return m_pSurfaceHandler->GetSurface();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes the surface window handler
*/
void SurfaceWindowHandler::Init(Renderer &cRenderer, handle nWindow, const DisplayMode &sDisplayMode, bool bFullscreen)
{
	// Create the surface window
	m_pRenderer = &cRenderer;
	m_pSurfaceHandler->SetSurface((Surface*)m_pRenderer->CreateSurfaceWindow(*this, nWindow, sDisplayMode, bFullscreen));
}

/**
*  @brief
*    De-initializes the surface window handler
*/
void SurfaceWindowHandler::DeInit()
{
	Surface *pSurface = m_pSurfaceHandler->GetSurface();
	if (pSurface) {
		((SurfaceWindow*)pSurface)->m_pHandler = nullptr;
		m_pSurfaceHandler->SetSurface(nullptr);
		delete pSurface;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
SurfaceWindowHandler::SurfaceWindowHandler(const SurfaceWindowHandler &cSource) :
	m_pRenderer(cSource.GetRenderer()),
	m_pSurfaceHandler(new SurfaceHandler())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
SurfaceWindowHandler &SurfaceWindowHandler::operator =(const SurfaceWindowHandler &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
