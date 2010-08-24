/*********************************************************\
 *  File: MouseOverWidget.cpp                            *
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
#include <PLGui/Gui/Resources/Graphics.h>
#include "MouseOver/MouseOverWidget.h"


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
pl_implement_class(MouseOverWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MouseOverWidget::MouseOverWidget(Widget *pParent) : Widget(pParent)
{
	SetBackgroundColor(Color4::Gray);
}

/**
*  @brief
*    Destructor
*/
MouseOverWidget::~MouseOverWidget()
{
}


//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
void MouseOverWidget::OnDraw(Graphics &cGraphics)
{
	cGraphics.DrawRect(Color4::Black, Vector2i::Zero, GetSize() - Vector2i(1, 1), 0, 0, 1);
}

void MouseOverWidget::OnMouseEnter()
{
	/*
	SetBackgroundColor(Color4::Green);
	Redraw();
	*/
}

void MouseOverWidget::OnMouseLeave()
{
	/*
	SetBackgroundColor(Color4::Gray);
	Redraw();
	*/
}

void MouseOverWidget::OnMouseOver(bool bMouseOver)
{
	// Check if mouse-over widget is this or a child widget
	if (m_pGui->GetMouseOverWidget() == this)
		SetBackgroundColor(Color4::Lime);
	else if (bMouseOver)
		SetBackgroundColor(Color4::Green);
	else
		SetBackgroundColor(Color4::Gray);
	Redraw();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
