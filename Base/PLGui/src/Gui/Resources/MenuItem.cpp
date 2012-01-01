/*********************************************************\
 *  File: MenuItem.cpp                                   *
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
#include "PLGui/Gui/Resources/MenuItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MenuItem::MenuItem(Gui &cGui) :
	m_pGui(&cGui),
	m_nType(TypeMenuItem),
	m_nCommandID(0),
	m_cIcon(cGui)
{
}

/**
*  @brief
*    Constructor
*/
MenuItem::MenuItem(Gui &cGui, const String &sText) :
	m_pGui(&cGui),
	m_nType(TypeMenuItem),
	m_nCommandID(0),
	m_sText(sText),
	m_cIcon(cGui)
{
}

/**
*  @brief
*    Constructor
*/
MenuItem::MenuItem(Gui &cGui, const String &sText, const Image &cIcon) :
	m_pGui(&cGui),
	m_nType(TypeMenuItem),
	m_nCommandID(0),
	m_sText(sText),
	m_cIcon(cIcon)
{
}

/**
*  @brief
*    Destructor
*/
MenuItem::~MenuItem()
{
}

/**
*  @brief
*    Get owner GUI
*/
Gui *MenuItem::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get type of menu item
*/
EMenuItemType MenuItem::GetType() const
{
	// Return menu item type
	return m_nType;
}

/**
*  @brief
*    Get command ID
*/
uint32 MenuItem::GetID() const
{
	// Return command ID
	return m_nCommandID;
}

/**
*  @brief
*    Set command ID
*/
void MenuItem::SetID(uint32 nID)
{
	// Set command ID
	m_nCommandID = nID;
}

/**
*  @brief
*    Get item text
*/
String MenuItem::GetText() const
{
	// Return text
	return m_sText;
}

/**
*  @brief
*    Set item text
*/
void MenuItem::SetText(const String &sText)
{
	// Set text
	m_sText = sText;
}

/**
*  @brief
*    Get icon
*/
const Image &MenuItem::GetIcon() const
{
	// Return image
	return m_cIcon;
}

/**
*  @brief
*    Set icon
*/
void MenuItem::SetIcon(const Image &cIcon)
{
	// Set image
	m_cIcon = cIcon;
}

/**
*  @brief
*    Get shortcut of menu item (e.g. if text is "&Test" -> 'T' is the shortcut)
*/
char MenuItem::GetShortcut() const
{
	// Find '&' that marks a shortcut
	int nAmp = m_sText.IndexOf("&");
	if (nAmp >= 0) {
		// Get character after '&'
		String sChar = m_sText.GetSubstring(nAmp+1, 1);
		sChar.ToLower();

		// Return shortcut
		char nChar = sChar.GetASCII()[0];
		return nChar;
	}

	// No shortcut
	return '\0';
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MenuItem::MenuItem(Gui &cGui, EMenuItemType nType) :
	m_pGui(&cGui),
	m_nType(nType),
	m_nCommandID(0),
	m_cIcon(cGui)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
