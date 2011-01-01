/*********************************************************\
 *  File: RenderWidget.cpp                               *
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
#include <PLGui/Gui/Base/Keys.h>
#include "PLEngine/Gui/RenderWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RenderWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RenderWidget::RenderWidget(Renderer &cRenderer, PLGui::Widget *pParent, const DisplayMode *pDisplayMode) : PLGui::Widget(pParent), WindowConnection(cRenderer, *this),
	m_bBackupAvailable(false)
{
	// There's no need to have a widget background because we're render into it
	SetBackgroundColor(Color4::Transparent);

	// Initialize the window connection
	Initialize(pDisplayMode, false);
}

/**
*  @brief
*    Destructor
*/
RenderWidget::~RenderWidget()
{
}


//[-------------------------------------------------------]
//[ Protected virtual WindowConnection functions          ]
//[-------------------------------------------------------]
void RenderWidget::OnDisplayMode()
{
	// Set the size of the widget depending on the current set display mode
	SetSize(GetDisplayMode().vSize);

	// Call base implementation
	WindowConnection::OnDisplayMode();
}

void RenderWidget::OnFullscreenMode()
{
	// Widget mode backup stuff
	if (IsFullscreen() && !m_bBackupAvailable) {
		m_vBackupSize = GetSize();
		if (m_vBackupSize.x || m_vBackupSize.y) {
			m_bBackupAvailable = true;
			m_vBackupPos	   = GetPos();
		}
	} else {
		if (!IsFullscreen() && m_bBackupAvailable) {
			SetPos (m_vBackupPos);
			SetSize(m_vBackupSize);
			m_bBackupAvailable = false;
		}
	}

	// Is the frame currently in fullscreen mode or not?
	if (IsFullscreen()) {
		// Place the widget at the left top side of the screen
		SetPos(Vector2i::Zero);

		// Set the size of the widget depending on the current set display mode
		SetSize(GetDisplayMode().vSize);
	}

	// Call base implementation
	WindowConnection::OnFullscreenMode();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
RenderWidget::RenderWidget(const RenderWidget &cSource) : PLGui::Widget(cSource.GetParent()), WindowConnection(*cSource.GetRenderer(), *this),
	m_bBackupAvailable(false)
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
RenderWidget &RenderWidget::operator =(const RenderWidget &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
