/*********************************************************\
 *  File: TabBarEntry.cpp                                *
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
#include "PLGui/Widgets/Controls/TabBar.h"
#include "PLGui/Widgets/Controls/TabBarEntry.h"
#include "PLGui/Widgets/Controls/TabBarButton.h"


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
pl_implement_class(TabBarEntry)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TabBarEntry::TabBarEntry(Widget *pParent) : Widget(pParent),
	m_cIcon(*GetGui()),
	m_pWidget(NULL),
	m_pData(NULL),
	m_pTabBar(NULL),
	m_nIndex(0),
	m_bClosable(false),
	m_pButtonClose(NULL)
{
}

/**
*  @brief
*    Destructor
*/
TabBarEntry::~TabBarEntry()
{
}

/**
*  @brief
*    Get TabBar
*/
TabBar *TabBarEntry::GetTabBar() const
{
	// Return TabBar
	return m_pTabBar;
}

/**
*  @brief
*    Get text
*/
String TabBarEntry::GetText() const
{
	// Return text
	return m_sText;
}

/**
*  @brief
*    Set text
*/
void TabBarEntry::SetText(const String &sText)
{
	// Set text
	m_sText = sText;
}

/**
*  @brief
*    Get icon
*/
const Image &TabBarEntry::GetIcon() const
{
	// Return icon
	return m_cIcon;
}

/**
*  @brief
*    Set icon
*/
void TabBarEntry::SetIcon(const Image &cIcon)
{
	// Set icon
	m_cIcon = cIcon;
}

/**
*  @brief
*    Get associated widget
*/
Widget *TabBarEntry::GetWidget() const
{
	// Return widget
	return m_pWidget;
}

/**
*  @brief
*    Set associated widget
*/
void TabBarEntry::SetWidget(Widget *pWidget)
{
	// Set widget
	m_pWidget = pWidget;
}

/**
*  @brief
*    Get associated data
*/
void *TabBarEntry::GetUserData() const
{
	// Return data
	return m_pData;
}

/**
*  @brief
*    Set associated data
*/
void TabBarEntry::SetUserData(void *pData)
{
	// Set data
	m_pData = pData;
}

/**
*  @brief
*    Get tab index
*/
int TabBarEntry::GetIndex() const
{
	// Return index
	return m_nIndex;
}

/**
*  @brief
*    Check if tab can be closed by the user
*/
bool TabBarEntry::IsClosable() const
{
	// Return closable
	return m_bClosable;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Set TabBar
*/
void TabBarEntry::SetTabBar(TabBar *pTabBar)
{
	// Set TabBar
	m_pTabBar = pTabBar;
}

/**
*  @brief
*    Set tab index
*/
void TabBarEntry::SetIndex(int nIndex)
{
	// Set index
	m_nIndex = nIndex;
}

/**
*  @brief
*    Set if tab can be closed by the user
*/
void TabBarEntry::SetClosable(bool bClosable)
{
	// Set closable
	m_bClosable = bClosable;

	// Create close-button
	if (m_pButtonClose == NULL && bClosable) {
		m_pButtonClose = new TabBarButton(this);
		m_pButtonClose->SetTabBar(m_pTabBar);
		m_pButtonClose->SetTabBarEntry(this);
		m_pButtonClose->SetFunction(TabFunctionCloseTab);
		m_pButtonClose->SetSize(Vector2i(16, 16));
		AdjustContent();
	}

	// Set button visibility
	if (m_pButtonClose) {
		m_pButtonClose->SetVisible(bClosable);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Widget functions                    ]
//[-------------------------------------------------------]
Vector2i TabBarEntry::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Set preferred size
	Vector2i vSize;
	if (m_pTabBar->GetSide() == SideLeft || m_pTabBar->GetSide() == SideRight || (m_pTabBar->GetOptions() & TabOptionStaticSize) != 0) {
		// Static tab width
		vSize.x = m_pTabBar->GetTabWidth();
		vSize.y = m_pTabBar->GetTabHeight();
	} else {
		// Dynamic tab width
		Graphics cGraphics(*GetGui());
		Font cFont = GetTheme()->GetDefaultFont();
		uint32 nTextWidth = cGraphics.GetTextWidth(cFont, m_sText);
		nTextWidth += 16;
		if (m_bClosable) nTextWidth += 20;
		if (!m_cIcon.IsEmpty()) nTextWidth += 20;
		if (nTextWidth <					   32) nTextWidth = 32;
		if (nTextWidth > m_pTabBar->GetTabWidth()) nTextWidth = m_pTabBar->GetTabWidth();
		vSize.x = nTextWidth;
		vSize.y = m_pTabBar->GetTabHeight();
	}

	// Return preferred size
	return vSize;
}

void TabBarEntry::OnAdjustContent()
{
	// Call base implementation
	Widget::OnAdjustContent();

	// Update close-button
	if (m_pButtonClose) {
		Vector2i vSize = GetSize();
		Vector2i vPos;
		vPos.x =  vSize.x - 20;
		vPos.y = (vSize.y - 16) / 2;
		m_pButtonClose->SetPos(vPos);
	}
}

void TabBarEntry::OnMouseEnter()
{
	// Call base implementation
	Widget::OnMouseEnter();

	// Update mouseover-index
	m_pTabBar->SetMouseSelection(m_nIndex);
}

void TabBarEntry::OnMouseLeave()
{
	// Call base implementation
	Widget::OnMouseLeave();

	// Update mouseover-index
	m_pTabBar->SetMouseSelection(-1);
}

void TabBarEntry::OnMouseButtonClick(uint32 nButton, const Vector2i &vPos)
{
	// Call base implementation
	Widget::OnMouseButtonClick(nButton, vPos);

	// Set selected tab
	if (nButton == LeftButton) {
		m_pTabBar->SetSelection(m_nIndex);
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
