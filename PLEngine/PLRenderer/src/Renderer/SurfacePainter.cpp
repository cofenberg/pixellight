/*********************************************************\
 *  File: SurfacePainter.cpp                             *
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
#include "PLRenderer/Renderer/SurfacePainter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SurfacePainter)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner renderer
*/
Renderer &SurfacePainter::GetRenderer() const
{
	return *m_pRenderer;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor (not implemented!)
*/
SurfacePainter::SurfacePainter(const SurfacePainter &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Constructor
*/
SurfacePainter::SurfacePainter(Renderer &cRenderer) :
	m_pRenderer(&cRenderer)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
SurfacePainter &SurfacePainter::operator =(const SurfacePainter &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Protected virtual functions                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfacePainter::~SurfacePainter()
{
}

/**
*  @brief
*    Is called when the owner surface is paint process begins
*/
bool SurfacePainter::OnPaintBegin(Surface &cSurface)
{
	// Renderer must match!
	if (&cSurface.GetRenderer() == m_pRenderer) {
		// Set new render target
		if (m_pRenderer->SetRenderTarget(&cSurface)) {
			// Begin scene
			m_pRenderer->BeginScene();

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Is called when the owner surface is paint process ends
*/
void SurfacePainter::OnPaintEnd(Surface &cSurface)
{
	// End scene
	m_pRenderer->EndScene();
	cSurface.Present();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
