/*********************************************************\
 *  File: MenuBar.cpp                                    *
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
#include "PLGui/Themes/Theme.h"
#include "PLGui/Gui/Resources/Menu.h"
#include "PLGui/Widgets/Controls/MenuBar.h"


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
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(MenuBar)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MenuBar::MenuBar(Widget *pParent) : AbstractMenu(pParent)
{
	// Menu bars are usually horizontal
	m_nOrientation = Horizontal;

	// We take the focus
	SetFocusStyle(AcceptFocus);
}

/**
*  @brief
*    Destructor
*/
MenuBar::~MenuBar()
{
}


//[-------------------------------------------------------]
//[ Protected virtual Widget functions                    ]
//[-------------------------------------------------------]
void MenuBar::OnDraw(Graphics &cGraphics)
{
	// Draw menu background and border
	m_pTheme->DrawMenuBar(cGraphics, Vector2i::Zero, GetSize() - Vector2i(1, 1), m_nOrientation, GetWidgetState());

	// Draw menu items
	for (uint32 i=0; i<m_pMenu->GetItems().GetNumOfElements(); i++) {
		// Get item
		MenuItem *pItem = m_pMenu->GetItems().Get(i);
		if (static_cast<int>(i) < m_nItems) {
			// Draw item
			Vector2i vPos1	= m_pItems[i].vPos1;
			Vector2i vPos2	= m_pItems[i].vPos2;
			bool bSelected	= (m_nSelection == static_cast<int>(i));
			bool bDrawArrow	= false;
			uint32 nWidgetState = 0;
			if (IsEnabled())					nWidgetState |= WidgetEnabled;
			if (IsActive())						nWidgetState |= WidgetActive;
			if (HasFocus())						nWidgetState |= WidgetFocus;
			if (bSelected)						nWidgetState |= WidgetMouseOver;
			if (bSelected && m_pSelectedItem)	nWidgetState |= WidgetPressed;
			m_pTheme->DrawMenuItem(cGraphics, vPos1, vPos2, pItem->GetText(), pItem->GetIcon(), bDrawArrow, pItem->GetType(), m_nOrientation, nWidgetState);
		}
	}
}

Vector2i MenuBar::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Call base implementation
	AbstractMenu::OnPreferredSize(vRefSize);

	// Set preferred size
	Vector2i vSize;

	// Horizontal
	if (m_nOrientation == Horizontal) {
		// Get menu bar height from current theme
		int nHeight = m_pTheme->GetMenuBarHeight();

		// Set size
		vSize.x = vRefSize.x;		// Take as much space as possible in X-direction
		vSize.y = nHeight;			// And set a static size in Y-direction
	}

	// Vertical
	else {
		// Set size
		vSize.x = m_nMaxWidth;		// Set a static size in X-direction
		vSize.y = vRefSize.y;		// And take as much space as possible in Y-direction
	}

	// Return preferred size
	return vSize;
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
