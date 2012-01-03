/*********************************************************\
 *  File: ContainerWidget.cpp                            *
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
#include "PLGui/Widgets/Containers/ContainerWidget.h"


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
pl_implement_class(ContainerWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContainerWidget::ContainerWidget(Widget *pParent) : Widget(pParent),
	m_pContentWidget(nullptr)
{
	// Create content widget
	m_pContentWidget = new Widget(this);
	m_pContentWidget->SetVisible(true);

	// Set layout
	GetContentWidget()->SetLayout("PLGui::LayoutBox", "Orientation=Vertical");

	// Give focus to child windows
	SetFocusStyle(ChildFocusOrSelf);
	m_pContentWidget->SetFocusStyle(ChildFocus);
}

/**
*  @brief
*    Destructor
*/
ContainerWidget::~ContainerWidget()
{
}

/**
*  @brief
*    Get content widget
*/
Widget *ContainerWidget::GetContentWidget() const
{
	// Return content widget
	return m_pContentWidget;
}


//[-------------------------------------------------------]
//[ Protected virtual WidgetFunctions functions           ]
//[-------------------------------------------------------]
void ContainerWidget::OnThemeChanged()
{
	// Adjust child widgets
	AdjustContent();

	// Redraw
	Redraw();
}

void ContainerWidget::OnAdjustContent()
{
	// Make content widget as big as container widget
	if (m_pContentWidget) {
		m_pContentWidget->SetSize(m_vSize);
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
