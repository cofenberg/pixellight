/*********************************************************\
 *  File: TestWidget.cpp                                 *
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
#include <PLGui/Gui/Gui.h>
#include "SimpleTest/TestWidget.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(TestWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestWidget::TestWidget(Widget *pParent) : Widget(pParent),
	m_bExit(false),
	m_cColor(0.7f, 0.7f, 0.7f, 1.0f)
{
	// Set default color to grey
	SetBackgroundColor(m_cColor);
}

/**
*  @brief
*    Destructor
*/
TestWidget::~TestWidget()
{
}

/**
*  @brief
*    Set if this window can exit the application
*/
void TestWidget::SetExit(bool bExit)
{
	// Set option
	m_bExit = bExit;
}

/**
*  @brief
*    Set default color (visible if no focus is set to the window)
*/
void TestWidget::SetColor(const PLGraphics::Color4 &cColor)
{
	// Set color
	m_cColor = cColor;

	// Update background color
	if (!HasFocus()) {
		SetBackgroundColor(m_cColor);
	}
}


//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
void TestWidget::OnClose()
{
	// Exit application
	if (m_bExit) {
		GetGui()->Exit();
	}
}

void TestWidget::OnMouseButtonDown(uint32 nButton, const Vector2i &vPos)
{
	// Exit application
	if (nButton == RightButton && m_bExit) {
		GetGui()->Exit();
	}
}

void TestWidget::OnGetFocus()
{
	// Set color to green
	SetBackgroundColor(Color4(0.4f, 1.0f, 0.2f, 1.0f));
	Redraw();
}

void TestWidget::OnLooseFocus()
{
	// Set color to default
	SetBackgroundColor(m_cColor);
	Redraw();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
