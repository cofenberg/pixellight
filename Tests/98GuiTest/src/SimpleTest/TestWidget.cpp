/*********************************************************\
 *  File: TestWidget.cpp                                 *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
using namespace PLCore;
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
	// Set default color to gray
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
//[ Public virtual PLGui::Widget functions                ]
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
