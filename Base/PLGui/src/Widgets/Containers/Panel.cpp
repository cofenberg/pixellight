/*********************************************************\
 *  File: Panel.cpp                                      *
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
#include "PLGui/Widgets/Containers/Panel.h"


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
pl_implement_class(Panel)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Panel::Panel(Widget *pParent) : ContainerWidget(pParent),
	BorderStyle(this),
	m_nBorderStyle(RaisedBorder)
{
}

/**
*  @brief
*    Destructor
*/
Panel::~Panel()
{
}

/**
*  @brief
*    Get border style
*/
EBorderStyle Panel::GetBorderStyle() const
{
	// Return border style
	return m_nBorderStyle;
}

/**
*  @brief
*    Set border style
*/
void Panel::SetBorderStyle(EBorderStyle nBorderStyle)
{
	// Has the border style changed?
	if (m_nBorderStyle != nBorderStyle) {
		// Set border style
		m_nBorderStyle = nBorderStyle;

		// Size may have changed
		UpdateContent();

		// Redraw border
		Redraw();
	}
}


//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
void Panel::OnDraw(Graphics &cGraphics)
{
	// Draw border
	m_pTheme->DrawBorder(cGraphics, Vector2i::Zero, GetSize() - Vector2i(1, 1), m_nBorderStyle);
}

Vector2i Panel::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Do we have a content widget?
	if (m_pContentWidget) {
		// Start with reference size
		Vector2i vSize = vRefSize;

		// Get border size
		int nBorderSize = m_pTheme->GetPanelBorderSize();

		// Subtract border size from size for content widget
		if (vSize.x > -1) {
			vSize.x -= nBorderSize*2;
			if (vSize.x < 0) vSize.x = 0;
		}
		if (vSize.y > -1) {
			vSize.y -= nBorderSize*2;
			if (vSize.y < 0) vSize.y = 0;
		}

		// Get preferred size from content widget
		m_pContentWidget->CalculatePreferredSize(vSize);
		Vector2i vPreferredSize = m_pContentWidget->GetPreferredSize();

		// Add sizes for border again
		if (vPreferredSize.x >= 0) vPreferredSize.x += nBorderSize*2;
		if (vPreferredSize.y >= 0) vPreferredSize.y += nBorderSize*2;

		// Return preferred size
		return vPreferredSize;
	}

	// Give me everything
	return Vector2i(-1, -1);
}

void Panel::OnAdjustContent()
{
	// Get border size
	int nBorderSize = m_pTheme->GetPanelBorderSize();

	// Set position and size of content widget
	if (m_pContentWidget) {
		m_pContentWidget->SetPos (Vector2i(nBorderSize, nBorderSize));
		m_pContentWidget->SetSize(GetSize() - Vector2i(2*nBorderSize, 2*nBorderSize));
	}
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
