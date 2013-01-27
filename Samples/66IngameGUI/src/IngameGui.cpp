/*********************************************************\
 *  File: IngameGui.cpp                                  *
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
#include "GuiLabel.h"
#include "GuiButton.h"
#include "IngameGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IngameGui::IngameGui(Application66 &cApplication, Widget *pParent) : Widget(pParent),
	m_pApplication(&cApplication)
{
	// GuiLabel instance
	GuiLabel *pLabel = new GuiLabel(this);
	pLabel->SetPos(Vector2i(40, 80));
	pLabel->SetSize(Vector2i(100, 30));
	pLabel->SetBackgroundColor(Color4::Transparent);
	pLabel->SetColor(Color4::White);
	pLabel->SetText("GuiLabel");
	pLabel->SetVisible(true);

	// GuiButton instance
	GuiButton *pButton = new GuiButton(this);
	pButton->SetPos(Vector2i(40, 120));
	pButton->SetSize(Vector2i(100, 100));
	pButton->SetBackgroundColor(Color4::Transparent);
	pButton->SetColor(Color4::Red);
	pButton->SetMouseOverColor(Color4::Green);
	pButton->SetText("GuiButton");
	pButton->SetBackgroundImageFilename("PLGui/button.tga");
	pButton->SetVisible(true);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
IngameGui::~IngameGui()
{
}
