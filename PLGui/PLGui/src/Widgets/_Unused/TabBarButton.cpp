/*********************************************************\
 *  File: TabBarButton.cpp                               *
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
#include "PLGui/Widgets/Controls/TabBar.h"
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
pl_implement_class(TabBarButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TabBarButton::TabBarButton(Widget *pParent) : AbstractButton(pParent),
	m_pTabBar(nullptr),
	m_pTabBarEntry(nullptr),
	m_nFunction(TabFunctionCreateTab)
{
}

/**
*  @brief
*    Destructor
*/
TabBarButton::~TabBarButton()
{
}

/**
*  @brief
*    Get TabBar
*/
TabBar *TabBarButton::GetTabBar() const
{
	// Return TabBar
	return m_pTabBar;
}

/**
*  @brief
*    Get TabBarEntry
*/
TabBarEntry *TabBarButton::GetTabBarEntry() const
{
	// Return TabBarEntry
	return m_pTabBarEntry;
}

/**
*  @brief
*    Get tab-bar function
*/
ETabBarFunction TabBarButton::GetFunction() const
{
	// Return function
	return m_nFunction;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Set TabBar
*/
void TabBarButton::SetTabBar(TabBar *pTabBar)
{
	// Set TabBar
	m_pTabBar = pTabBar;
}

/**
*  @brief
*    Set TabBarEntry
*/
void TabBarButton::SetTabBarEntry(TabBarEntry *pEntry)
{
	// Set TabBarEntry
	m_pTabBarEntry = pEntry;
}

/**
*  @brief
*    Set tab-bar function
*/
void TabBarButton::SetFunction(ETabBarFunction nFunction)
{
	// Set function
	m_nFunction = nFunction;
}


//[-------------------------------------------------------]
//[ Protected virtual Widget functions                    ]
//[-------------------------------------------------------]
void TabBarButton::OnMouseEnter()
{
	// Call base function
	AbstractButton::OnMouseEnter();

	// Update mouseover-index
	if (m_pTabBarEntry) {
		m_pTabBar->SetMouseSelection(m_pTabBarEntry->GetIndex());
	}

	// Redraw button
	Redraw();
}

void TabBarButton::OnMouseLeave()
{
	// Call base function
	AbstractButton::OnMouseLeave();

	// Redraw button
	Redraw();
}


//[-------------------------------------------------------]
//[ Private virtual AbstractButton functions              ]
//[-------------------------------------------------------]
void TabBarButton::OnButtonClicked()
{
	// Call base implementation
	AbstractButton::OnButtonClicked();

	// Execute function
	if (m_nFunction == TabFunctionCreateTab) {
		// Create tab
		if (m_pTabBar) {
			m_pTabBar->CreateTab();
		}
	} else if (m_nFunction == TabFunctionCloseTab) {
		// Close tab
		if (m_pTabBar && m_pTabBarEntry) {
			m_pTabBar->CloseTab(m_pTabBarEntry->GetIndex());
		}
	} else if (m_nFunction == TabFunctionScrollNext) {
		// Scroll (next)
		if (m_pTabBar) {
			m_pTabBar->SetScrollingPos(m_pTabBar->GetScrollingPos() + 1);
		}
	} else if (m_nFunction == TabFunctionScrollPrev) {
		// Scroll (prev)
		if (m_pTabBar) {
			m_pTabBar->SetScrollingPos(m_pTabBar->GetScrollingPos() - 1);
		}
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
