/*********************************************************\
 *  File: Button.cpp                                     *
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
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Gui/Base/Keys.h"
#include "PLGui/Gui/Resources/Graphics.h"
#include "PLGui/Themes/Theme.h"
#include "PLGui/Widgets/Controls/Button.h"


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
pl_implement_class(Button)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Button::Button(Widget *pParent) : AbstractButton(pParent)
{
	// No background
	SetBackgroundColor(Color4::Transparent);

	// Accept focus
	SetFocusStyle(AcceptFocus);
}

/**
*  @brief
*    Destructor
*/
Button::~Button()
{
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractButton functions            ]
//[-------------------------------------------------------]
void Button::OnButtonClicked()
{
	// Call base implementation
	AbstractButton::OnButtonClicked();
}


//[-------------------------------------------------------]
//[ Protected virtual WidgetFunctions functions           ]
//[-------------------------------------------------------]
void Button::OnDraw(Graphics &cGraphics)
{
	// Draw button
	m_pTheme->DrawButton(cGraphics, Vector2i::Zero, GetSize() - Vector2i(1, 1), GetText(), GetImage(), GetWidgetState());
}

Vector2i Button::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Get width and height of the button text
	Graphics cGraphics(*GetGui());
	String sText = GetText();
	Font   cFont = GetTheme()->GetDefaultFont();
	int nTextWidth  = cGraphics.GetTextWidth (cFont, sText);
	int nTextHeight = cGraphics.GetTextHeight(cFont, sText);

	// Make widget as wide as needed for the text in X direction, and as small as possible in Y direction
	Vector2i vSize;
	vSize.x = nTextWidth  + 32;
	vSize.y = nTextHeight + 16;
	return vSize;
}

void Button::OnMouseEnter()
{
	// Call base function
	AbstractButton::OnMouseEnter();

	// Redraw button
	Redraw();
}

void Button::OnMouseLeave()
{
	// Call base function
	AbstractButton::OnMouseLeave();

	// Redraw button
	Redraw();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
