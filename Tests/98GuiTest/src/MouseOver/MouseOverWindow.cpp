/*********************************************************\
 *  File: MouseOverWindow.cpp                            *
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
