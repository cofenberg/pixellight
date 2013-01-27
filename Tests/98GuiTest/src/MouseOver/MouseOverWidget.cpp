/*********************************************************\
 *  File: MouseOverWidget.cpp                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
using namespace PLCore;
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
//[ Public virtual PLGui::Widget functions                ]
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
