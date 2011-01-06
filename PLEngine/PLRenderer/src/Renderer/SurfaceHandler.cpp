/*********************************************************\
 *  File: SurfaceHandler.cpp                             *
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
#include "PLRenderer/Renderer/Surface.h"
#include "PLRenderer/Renderer/SurfaceHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceHandler::SurfaceHandler() :
	m_pSurface(nullptr)
{
}

/**
*  @brief
*    Copy constructor
*/
SurfaceHandler::SurfaceHandler(const SurfaceHandler &cSource) :
	m_pSurface(nullptr)
{
	if (cSource.m_pSurface) {
		m_pSurface = cSource.m_pSurface;
		m_pSurface->m_lstHandler.Add(this);
	}
}

/**
*  @brief
*    Destructor
*/
SurfaceHandler::~SurfaceHandler()
{
	// Inform the surface
	if (m_pSurface)
		m_pSurface->m_lstHandler.Remove(this);
}

/**
*  @brief
*    Copy operator
*/
SurfaceHandler &SurfaceHandler::operator =(const SurfaceHandler &cSource)
{
	// Inform the old resource
	if (m_pSurface)
		m_pSurface->m_lstHandler.Remove(this);

	// Set new one
	m_pSurface = cSource.m_pSurface;
	if (m_pSurface)
		m_pSurface->m_lstHandler.Add(this);

	// Return this
	return *this;
}

/**
*  @brief
*    Returns the renderer surface of this handler
*/
Surface *SurfaceHandler::GetSurface() const
{
	return m_pSurface;
}

/**
*  @brief
*    Set the renderer surface of this handler
*/
void SurfaceHandler::SetSurface(Surface *pSurface)
{
	// Inform the old surface
	if (m_pSurface)
		m_pSurface->m_lstHandler.Remove(this);

	// Set new one
	m_pSurface = pSurface;
	if (m_pSurface)
		m_pSurface->m_lstHandler.Add(this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
