/*********************************************************\
 *  File: ButtonGroup.cpp                                *
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
#include "PLGui/Gui/Data/ButtonGroup.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ButtonGroup::ButtonGroup() :
	m_bExclusive(true),
	m_pButton(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ButtonGroup::~ButtonGroup()
{
}

/**
*  @brief
*    Check if the button activation is exclusive
*/
bool ButtonGroup::IsExclusive() const
{
	// Return exclusive-flag
	return m_bExclusive;
}

/**
*  @brief
*    Set if the button activation is exclusive
*/
void ButtonGroup::SetExclusive(bool bExclusive)
{
	// Set exclusive-flag
	m_bExclusive = bExclusive;
}

/**
*  @brief
*    Activates a certain button
*/
void ButtonGroup::Activate(AbstractToggleButton &cButton)
{
	// Has the active button changed?
	if (m_pButton != &cButton) {
		// Save active button
		m_pButton = &cButton;

		// Send event that a new button is active
		EventActivate(m_pButton);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
