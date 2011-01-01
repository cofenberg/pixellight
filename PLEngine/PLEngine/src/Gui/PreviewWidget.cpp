/*********************************************************\
 *  File: PreviewWidget.cpp                              *
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
#include <PLGui/Gui/Gui.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLRenderer/SPPreview.h>
#include "PLEngine/Gui/PreviewWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGui;
using namespace PLRenderer;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PreviewWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PreviewWidget::PreviewWidget(Renderer &cRenderer, PLGui::Widget *pParent) : RenderWidget(cRenderer, pParent),
	m_bLeftMouseButtonPressed(false),
	m_bRightMouseButtonPressed(false)
{
	// Set widget mouse cursor
	Cursor *pCursor = GetGui()->GetCursorManager().GetCursor(CursorSize);
	if (pCursor)
		SetCursor(*pCursor);
}

/**
*  @brief
*    Destructor
*/
PreviewWidget::~PreviewWidget()
{
}

/**
*  @brief
*    Resets the view
*/
void PreviewWidget::ResetView()
{
	SPPreview *pPainter = (SPPreview*)GetSurface()->GetPainter();
	if (pPainter)
		pPainter->SetCameraPosition(Vector3(0.5f, 0.5f, -0.5f));
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
PreviewWidget::PreviewWidget(const PreviewWidget &cSource) : RenderWidget(cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
PreviewWidget &PreviewWidget::operator =(const PreviewWidget &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Private virtual PLGui::Widget functions               ]
//[-------------------------------------------------------]
void PreviewWidget::OnMouseMove(const Vector2i &vPos)
{
	// Is the left or right mouse button pressed?
	if (m_bLeftMouseButtonPressed || m_bRightMouseButtonPressed) {
		// Preview camera control
		SPPreview *pPainter = (SPPreview*)GetSurface()->GetPainter();
		if (pPainter) {
			Vector3 vCameraPos = pPainter->GetCameraPosition();
			if (m_bLeftMouseButtonPressed) {
				vCameraPos.x += (m_vPreviousMousePosition.x-vPos.x)/50.0f;
				vCameraPos.y += (m_vPreviousMousePosition.y-vPos.y)/50.0f;
			} else if (m_bRightMouseButtonPressed) {
				vCameraPos.z += (m_vPreviousMousePosition.y-vPos.y)/40.0f;
				if (vCameraPos.z > -0.1f)
					vCameraPos.z = -0.1f;
			}
			pPainter->SetCameraPosition(vCameraPos);

			// Backup current mouse position
			m_vPreviousMousePosition = vPos;
		}
	}
}

void PreviewWidget::OnMouseButtonDown(uint32 nButton, const Vector2i &vPos)
{
	// Call base implementation
	RenderWidget::OnMouseButtonDown(nButton, vPos);

	// Check mouse button
	switch (nButton) {
		// Left mouse button
		case 0:
			m_bLeftMouseButtonPressed = true;

			// Backup current mouse position
			m_vPreviousMousePosition = vPos;
			break;

		// Right mouse button
		case 1:
			m_bRightMouseButtonPressed = true;

			// Backup current mouse position
			m_vPreviousMousePosition = vPos;
			break;
	}
}

void PreviewWidget::OnMouseButtonUp(uint32 nButton, const Vector2i &vPos)
{
	// Call base implementation
	RenderWidget::OnMouseButtonUp(nButton, vPos);

	// Check mouse button
	switch (nButton) {
		// Left mouse button
		case 0:
			m_bLeftMouseButtonPressed = false;
			break;

		// Right mouse button
		case 1:
			m_bRightMouseButtonPressed = false;
			break;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
