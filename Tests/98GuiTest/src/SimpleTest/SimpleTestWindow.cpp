/*********************************************************\
 *  File: SimpleTestWindow.cpp                           *
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
#include "SimpleTest/SimpleTestWindow.h"
#include "SimpleTest/TestWidget.h"
#include "SimpleTest/TestWidgetImage.h"
#include "SimpleTest/TestWidgetTimer.h"


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
pl_implement_class(SimpleTestWindow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SimpleTestWindow::SimpleTestWindow(Widget *pParent) : Window(pParent)
{
	// Set title
	SetTitle("Widget Test");

	// Destroy window on close
	AddModifier("PLGui::ModClose", "CloseWindow=1");

	// Set size
	SetSize(Vector2i(320, 200));

	// Make not resizable and disable maximize button
	SetResizable(false);
	SetSystemButtons(SystemButtonMinimize | SystemButtonClose);

	// Create test widget
	TestWidget *pWidget = new TestWidget(GetContentWidget());
	pWidget->SetPos(Vector2i(20, 30));
	pWidget->SetSize(Vector2i(80, 100));
	pWidget->SetVisible(true);

	// Create image test widget
	TestWidgetImage *pWidgetImage = new TestWidgetImage(GetContentWidget());
	pWidgetImage->SetPos(Vector2i(120, 30));
	pWidgetImage->SetSize(Vector2i(80, 100));
	pWidgetImage->SetVisible(true);

	// Create timer test widget
	TestWidgetTimer *pWidgetTimer = new TestWidgetTimer(GetContentWidget());
	pWidgetTimer->SetPos(Vector2i(220, 30));
	pWidgetTimer->SetSize(Vector2i(80, 100));
	pWidgetTimer->SetVisible(true);
}

/**
*  @brief
*    Destructor
*/
SimpleTestWindow::~SimpleTestWindow()
{
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
