/*********************************************************\
 *  File: Tooltip.cpp                                    *
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
#include "PLGui/Gui/Screen.h"
#include "PLGui/Themes/Theme.h"
#include "PLGui/Widgets/Controls/Label.h"
#include "PLGui/Widgets/Popups/Tooltip.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Tooltip)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Tooltip::Tooltip(Widget *pParent) : AbstractTooltip(pParent),
	m_pLabel(nullptr)
{
	// Colors
	Color4 cTooltipBackgroundColor(1.0f,  1.0f,  0.88f, 1.0f);
	Color4 cTooltipTextColor	  (0.0f,  0.0f,  0.0f,  1.0f);

	// Set layout
	GetContentWidget()->SetLayout("LayoutBox", "Orientation=Horizontal");
	GetContentWidget()->GetLayoutHints().SetPadding(SizeHint(SizeHint::Pixel, 2));

	// Create label
	m_pLabel = new Label(GetContentWidget());
	m_pLabel->SetText("Tooltip Text");
	m_pLabel->SetVisible(true);
	m_pLabel->SetAlign(AlignCenter);
	m_pLabel->SetBackgroundColor(cTooltipBackgroundColor);
	m_pLabel->SetColor(cTooltipTextColor);
}

/**
*  @brief
*    Destructor
*/
Tooltip::~Tooltip()
{
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractTooltip functions           ]
//[-------------------------------------------------------]
void Tooltip::OnShowTooltip()
{
	// Set maximum text width to 80% of the screen width
	int nWidth = (int)(GetScreen()->GetSize().x * 0.8f);

	// Set label text
	m_pLabel->SetText(m_sTooltip);

	// Calculate text size, try to use a single line first
	m_pLabel->CalculatePreferredSize();
	Vector2i vSize = m_pLabel->GetPreferredSize();
	if (vSize.x > nWidth) {
		// Text is too big, set size to maximum
		m_pLabel->CalculatePreferredSize(Vector2i(nWidth, -1));
		vSize = m_pLabel->GetPreferredSize();
	}

	// Add padding of 2px (at each side)
	vSize.x += 4;
	vSize.y += 4;

	// Set size
	SetSize(vSize);

	// Show tooltip
	SetVisible(true);

	// Start timer
	BlendOut();
}

void Tooltip::OnTimeout()
{
	// Hide tooltip
	SetVisible(false);
}


//[-------------------------------------------------------]
//[ Protected virtual WidgetFunctions functions           ]
//[-------------------------------------------------------]
void Tooltip::OnDraw(Graphics &cGraphics)
{
	// Draw tooltip
	m_pTheme->DrawTooltip(cGraphics, Vector2i(0, 0), GetSize() - Vector2i(1, 1), GetWidgetState());
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
