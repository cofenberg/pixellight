/*********************************************************\
 *  File: ModTooltip.cpp                                 *
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
#include "PLGui/Gui/Gui.h"
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Modifiers/ModTooltip.h"


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
pl_implement_class(ModTooltip)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ModTooltip::ModTooltip() :
	Tooltip(this)
{
}

/**
*  @brief
*    Destructor
*/
ModTooltip::~ModTooltip()
{
}

/**
*  @brief
*    Get tooltip text
*/
String ModTooltip::GetTooltip() const
{
	// Return tooltip text
	return m_sTooltip;
}

/**
*  @brief
*    Set tooltip text
*/
void ModTooltip::SetTooltip(const String &sTooltip)
{
	// Set tooltip text
	m_sTooltip = sTooltip;
}


//[-------------------------------------------------------]
//[ Protected virtual ModTooltip functions                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a tooltip shall be displayed
*/
void ModTooltip::OnShowTooltip()
{
	// Set tooltip position
	Vector2i vTooltipPos = m_pWidget->GetAbsPos() + Vector2i(16, 20);

	// Display tooltip
	m_pWidget->GetGui()->ShowTooltip(vTooltipPos, m_sTooltip);
}


//[-------------------------------------------------------]
//[ Protected virtual Modifier functions                  ]
//[-------------------------------------------------------]
void ModTooltip::OnAttach(Widget &cWidget)
{
}

void ModTooltip::OnDetach(Widget &cWidget)
{
}


//[-------------------------------------------------------]
//[ Protected virtual WidgetFunctions functions           ]
//[-------------------------------------------------------]
void ModTooltip::OnMouseHover()
{
	// Show tooltip
	OnShowTooltip();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
