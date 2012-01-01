/*********************************************************\
 *  File: SimpleTestWindow.cpp                           *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
