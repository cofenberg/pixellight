/*********************************************************\
 *  File: MouseOverWindow.cpp                            *
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
#include "MouseOver/MouseOverWindow.h"
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
pl_implement_class(MouseOverWindow)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MouseOverWindow::MouseOverWindow(Widget *pParent) : Window(pParent)
{
	// Set title
	SetTitle("MouseOver Test");

	// Destroy window on close
	AddModifier("PLGui::ModClose", "CloseWindow=1");

	// Blend-Out modifier
	AddModifier("PLGui::ModBlend", "");

	// Set size
	SetSize(Vector2i(588, 612));

	// Make not resizable and disable maximize button
	SetResizable(false);
	SetSystemButtons(SystemButtonMinimize | SystemButtonClose);

	// Add root window
	MouseOverWidget *pRoot = new MouseOverWidget(GetContentWidget());
	pRoot->SetPos(Vector2i(0, 0));
	pRoot->SetSize(Vector2i(588, 588));
	pRoot->SetVisible(true);

	// Add windows
	for (int i=0; i<4; i++) {
		// Add window
		MouseOverWidget *pWidget = new MouseOverWidget(pRoot->GetContentWidget());
		pWidget->SetPos(Vector2i(i%2 == 0 ? 32 : 300, i/2 == 0 ? 32 : 300));
		pWidget->SetSize(Vector2i(256, 256));
		pWidget->SetVisible(true);

		// Add sub-windows
		for (int j=0; j<4; j++) {
			// Add sub-window
			MouseOverWidget *pSub = new MouseOverWidget(pWidget->GetContentWidget());
			pSub->SetPos(Vector2i(j%2 == 0 ? 32 : 144, j/2 == 0 ? 32 : 144));
			pSub->SetSize(Vector2i(80, 80));
			pSub->SetVisible(true);
		}
	}
}

/**
*  @brief
*    Destructor
*/
MouseOverWindow::~MouseOverWindow()
{
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
