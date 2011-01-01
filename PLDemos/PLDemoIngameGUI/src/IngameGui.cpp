/*********************************************************\
 *  File: IngameGui.cpp                                  *
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
IngameGui::IngameGui(Application &cApplication, Widget *pParent) : Widget(pParent),
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
	pButton->SetBackgroundImageFilename("PLGui/button.png");
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
