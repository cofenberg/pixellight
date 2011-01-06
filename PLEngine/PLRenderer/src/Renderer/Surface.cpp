/*********************************************************\
 *  File: Surface.cpp                                    *
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
#include "PLRenderer/Renderer/SurfacePainter.h"
#include "PLRenderer/Renderer/Surface.h"


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
*    Destructor
*/
Surface::~Surface()
{
	{ // Inform all surface handler
		Iterator<SurfaceHandler*> cIterator = m_lstHandler.GetIterator();
		while (cIterator.HasNext())
			cIterator.Next()->m_pSurface = nullptr;
	}

	// Remove surface from the renderer
	m_pRenderer->RemoveSurface(*this);

	// If there'a a painter, destroy it!
	if (m_pPainter)
		delete m_pPainter;
}

/**
*  @brief
*    Returns the owner renderer
*/
Renderer &Surface::GetRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Returns the surface type
*/
Surface::EType Surface::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Returns whether the surface is active or not
*/
bool Surface::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the surface is active or not
*/
void Surface::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Returns the surface painter
*/
SurfacePainter *Surface::GetPainter() const
{
	return m_pPainter;
}

/**
*  @brief
*    Set a surface painter
*/
bool Surface::SetPainter(SurfacePainter *pPainter, bool bDestroy)
{
	// Destroy current surface painter
	if (bDestroy && m_pPainter) {
		delete m_pPainter;
		m_pPainter = nullptr;
	}

	// Set new painter
	m_pPainter = pPainter;

	// Done
	return true;
}

/**
*  @brief
*    Updates the surface
*/
void Surface::Update()
{
	// Is this surface active and is there a surface painter?
	if (m_bActive && m_pPainter) {
		// Emit paint begin event
		EventPaintBegin.Emit();

		// Begin paint
		if (m_pPainter->OnPaintBegin(*this)) {
			// Emit paint event
			EventPaint.Emit();

			// Paint
			m_pPainter->OnPaint(*this);

			// End paint
			m_pPainter->OnPaintEnd(*this);
		}

		// Emit paint end event
		EventPaintEnd.Emit();
	}
}

/**
*  @brief
*    Returns the whether the surface is flipped along the y axis
*/
bool Surface::IsSwapY() const
{
	return m_bSwapY;
}

/**
*  @brief
*    Sets the whether the surface is flipped along the y axis
*/
void Surface::SetSwapY(bool bSwapY)
{
	m_bSwapY = bSwapY;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Surface::Surface(Renderer &cRenderer, EType nType) :
	m_pRenderer(&cRenderer),
	m_nType(nType),
	m_bActive(true),
	m_bSwapY(false),
	m_pPainter(nullptr)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Surface::Surface(const Surface &cSource) :
	m_pRenderer(&cSource.GetRenderer()),
	m_nType(cSource.GetType()),
	m_bActive(true),
	m_bSwapY(false),
	m_pPainter(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Surface &Surface::operator =(const Surface &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Protected virtual functions                           ]
//[-------------------------------------------------------]
bool Surface::IsAPISwapY() const
{
	return m_bSwapY;
}

bool Surface::UnmakeCurrent()
{
	// Done
	return true;
}

void Surface::BackupDeviceData()
{
	// Nothing to do by default
}

void Surface::RestoreDeviceData()
{
	// Nothing to do by default
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
