/*********************************************************\
 *  File: ScrollWidget.cpp                               *
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
#include "PLGui/Widgets/Controls/ScrollBar.h"
#include "PLGui/Widgets/Containers/ScrollWidget.h"


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
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(ScrollWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScrollWidget::ScrollWidget(Widget *pParent) : ContainerWidget(pParent),
	ScrollBarStyleX(this),
	ScrollBarStyleY(this),
	SlotOnInnerWidgetSize(this),
	SlotOnScrollBarXChanged(this),
	SlotOnScrollBarYChanged(this),
	m_nScrollBarStyleX(ScrollBarStyleDynamic),
	m_nScrollBarStyleY(ScrollBarStyleDynamic),
	m_pInnerWidget(nullptr),
	m_pScrollBarX(nullptr),
	m_pScrollBarY(nullptr),
	m_bScrollBarX(false),
	m_bScrollBarY(false)
{
	// Remove layout of content widget, otherwise the inner widget would never be bigger than the content widget itself
	m_pContentWidget->SetLayout(nullptr);

	// Create scrollbars
	m_pScrollBarX = new ScrollBar(this);
	m_pScrollBarX->SetOrientation(Horizontal);
	m_pScrollBarX->FitSize();
	m_pScrollBarX->EventChangeValue.Connect(&SlotOnScrollBarXChanged);
	m_pScrollBarY = new ScrollBar(this);
	m_pScrollBarY->SetOrientation(Vertical);
	m_pScrollBarY->FitSize();
	m_pScrollBarY->EventChangeValue.Connect(&SlotOnScrollBarYChanged);

	// Create inner content widget
	m_pInnerWidget = new Widget(m_pContentWidget);
	m_pInnerWidget->EventSize.Connect(&SlotOnInnerWidgetSize);
	m_pInnerWidget->SetPos(Vector2i(0, 0));
	m_pInnerWidget->SetSize(Vector2i(1280, 854));
	m_pInnerWidget->SetVisible(true);
	m_pInnerWidget->SetLayout("LayoutBox", "Orientation=Vertical");
}

/**
*  @brief
*    Destructor
*/
ScrollWidget::~ScrollWidget()
{
}

/**
*  @brief
*    Get scrollbar style of horizontal scrollbar
*/
EScrollBarStyle ScrollWidget::GetScrollBarStyleX() const
{
	// Return scrollbar style
	return m_nScrollBarStyleX;
}

/**
*  @brief
*    Set scrollbar style of horizontal scrollbar
*/
void ScrollWidget::SetScrollBarStyleX(EScrollBarStyle nStyle)
{
	// Set scrollbar style
	m_nScrollBarStyleX = nStyle;
}

/**
*  @brief
*    Get scrollbar style of vertical scrollbar
*/
EScrollBarStyle ScrollWidget::GetScrollBarStyleY() const
{
	// Return scrollbar style
	return m_nScrollBarStyleY;
}

/**
*  @brief
*    Set scrollbar style of vertical scrollbar
*/
void ScrollWidget::SetScrollBarStyleY(EScrollBarStyle nStyle)
{
	// Set scrollbar style
	m_nScrollBarStyleY = nStyle;
}

/**
*  @brief
*    Get content widget
*/
Widget *ScrollWidget::GetContentWidget() const
{
	// Return inner widget
	return m_pInnerWidget;
}


//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
void ScrollWidget::OnSize(const Vector2i &vSize)
{
	// Update scroll bars
	AdjustScrollBars();
}

void ScrollWidget::OnAdjustContent()
{
	// Call base implementation
	ContainerWidget::OnAdjustContent();

	// Adjust content of inner window
	m_pInnerWidget->AdjustContent();

	// Position widgets
	if (m_pScrollBarX && m_pScrollBarY) {
		// Get sizes
		Vector2i vSize = GetSize();
		m_pScrollBarX->CalculatePreferredSize();
		m_pScrollBarY->CalculatePreferredSize();
		int nScrollBarX = m_pScrollBarY->GetPreferredSize().x;
		int nScrollBarY = m_pScrollBarX->GetPreferredSize().y;

		// Set horizontal scrollbar
		m_pScrollBarX->SetPos (Vector2i(0, vSize.y - nScrollBarY));
		m_pScrollBarX->SetSize(Vector2i(vSize.x - nScrollBarX, nScrollBarY));
		m_pScrollBarX->SetEnabled(m_bScrollBarX);
		m_pScrollBarX->SetVisible(m_nScrollBarStyleX == ScrollBarStyleAlways || (m_nScrollBarStyleX == ScrollBarStyleDynamic && m_bScrollBarX));

		// Set vertical scrollbar
		m_pScrollBarY->SetPos (Vector2i(vSize.x - nScrollBarX, 0));
		m_pScrollBarY->SetSize(Vector2i(nScrollBarX, vSize.y - nScrollBarY));
		m_pScrollBarY->SetEnabled(m_bScrollBarY);
		m_pScrollBarY->SetVisible(m_nScrollBarStyleY == ScrollBarStyleAlways || (m_nScrollBarStyleY == ScrollBarStyleDynamic && m_bScrollBarY));

		// Set position and size of content widget
		if (m_pContentWidget) {
			m_pContentWidget->SetPos (Vector2i(0, 0));
			m_pContentWidget->SetSize(Vector2i(vSize.x - nScrollBarX, vSize.y - nScrollBarY));
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the size of the inner window has changed
*/
void ScrollWidget::OnInnerWidgetSize(const Vector2i &vSize)
{
	// Update scroll bars
	AdjustScrollBars();
}

/**
*  @brief
*    Called when the horizontal scrollbar has changed it's value
*/
void ScrollWidget::OnScrollBarXChanged(int nX)
{
	m_pInnerWidget->SetPos(Vector2i(-nX, m_pInnerWidget->GetPos().y));
}

/**
*  @brief
*    Called when the vertical scrollbar has changed it's value
*/
void ScrollWidget::OnScrollBarYChanged(int nY)
{
	m_pInnerWidget->SetPos(Vector2i(m_pInnerWidget->GetPos().x, -nY));
}

/**
*  @brief
*    Show or hide scroll bars according to the widget size
*/
void ScrollWidget::AdjustScrollBars()
{
	// Get outer size
	Vector2i vOuterSize = GetSize();

	// Get inner size
	Vector2i vInnerSize = m_pInnerWidget->GetSize();

	// Get size of scroll bars
	int nScrollBarX = m_pScrollBarY->GetSize().x;
	int nScrollBarY = m_pScrollBarX->GetSize().y;

	// Do we need a horizontal scrollbar?
	m_bScrollBarX = false;
	if (vInnerSize.x > vOuterSize.x) m_bScrollBarX = true;

	// Do we need a vertical scrollbar?
	m_bScrollBarY = false;
	if (vInnerSize.y > vOuterSize.y) m_bScrollBarY = true;

	// Now check again, because one scrollbar may change the situation of the other
	if (m_bScrollBarX) vOuterSize.y -= nScrollBarY;
	if (m_bScrollBarY) vOuterSize.x -= nScrollBarX;
	if (m_bScrollBarX && vInnerSize.y > vOuterSize.y) m_bScrollBarY = true;
	if (m_bScrollBarY && vInnerSize.x > vOuterSize.x) m_bScrollBarX = true;

	// Update scroll bars
	if (m_pScrollBarX) {
		m_pScrollBarX->SetMinValue(0);
		m_pScrollBarX->SetMaxValue(vInnerSize.x - vOuterSize.x);
	}
	if (m_pScrollBarY) {
		m_pScrollBarY->SetMinValue(0);
		m_pScrollBarY->SetMaxValue(vInnerSize.y - vOuterSize.y);
	}

	// Update widgets
	AdjustContent();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
