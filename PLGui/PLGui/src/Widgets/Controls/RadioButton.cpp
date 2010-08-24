/*********************************************************\
 *  File: RadioButton.cpp                                *
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
#include "PLGui/Gui/Resources/Graphics.h"
#include "PLGui/Themes/Theme.h"
#include "PLGui/Widgets/Controls/RadioButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(RadioButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RadioButton::RadioButton(Widget *pParent) : AbstractToggleButton(pParent)
{
	// Accept focus
	SetFocusStyle(AcceptFocus);
}

/**
*  @brief
*    Destructor
*/
RadioButton::~RadioButton()
{
}


//[-------------------------------------------------------]
//[ Protected virtual Widget functions                    ]
//[-------------------------------------------------------]
void RadioButton::OnDraw(Graphics &cGraphics)
{
	// Draw radio button
	m_pTheme->DrawRadioButton(cGraphics, Vector2i(0, 0), GetSize()-Vector2i(1, 1), GetText(), GetWidgetState(), GetState());
}

Vector2i RadioButton::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Call base function
	AbstractButton::OnPreferredSize(vRefSize);

	// Get width and height of the button text
	Graphics cGraphics(*GetGui());
	String sText = GetText();
	Font   cFont = GetTheme()->GetDefaultFont();
	int nTextWidth  = cGraphics.GetTextWidth (cFont, sText);
	int nTextHeight = cGraphics.GetTextHeight(cFont, sText);
	if (nTextHeight <= 0) {
		nTextWidth  = cGraphics.GetTextWidth (cFont, "Empty");
		nTextHeight = cGraphics.GetTextHeight(cFont, "Empty");
	}

	// Make widget as wide as needed for the text in X direction, and as small as possible in Y direction
	Vector2i vSize;
	vSize.x = nTextWidth  + 32;
	vSize.y = nTextHeight +  8;
	return vSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
