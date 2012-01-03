/*********************************************************\
 *  File: Theme.cpp                                      *
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
#include <PLCore/Base/Class.h>
#include "PLGui/Themes/Theme.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Theme)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Theme::Theme(Gui &cGui, const String &sName) :
	m_pGui(&cGui),
	m_sName(sName),
	m_cDefaultFont(cGui),
	m_cDefaultIcon(cGui),
	m_nWindowBorderSize(2),
	m_nWindowTitleBarHeight(20),
	m_nMenuBarHeight(20),
	m_cWindowColor(Color4::White),
	m_nPanelBorderSize(2),
	m_cPanelColor(0.83f, 0.82f, 0.78f, 1.0f),
	m_vSysButtonSize(16, 16)
{
}

/**
*  @brief
*    Destructor
*/
Theme::~Theme()
{
}

/**
*  @brief
*    Get owner GUI
*/
Gui *Theme::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get name of theme
*/
String Theme::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get default font
*/
const Font &Theme::GetDefaultFont() const
{
	// Return default font
	return m_cDefaultFont;
}

/**
*  @brief
*    Get default icon
*/
const Image &Theme::GetDefaultIcon() const
{
	// Return default icon
	return m_cDefaultIcon;
}

/**
*  @brief
*    Get window border size
*/
int Theme::GetWindowBorderSize() const
{
	// Return border size
	return m_nWindowBorderSize;
}

/**
*  @brief
*    Get window title bar height
*/
int Theme::GetWindowTitleBarHeight() const
{
	// Return title bar height
	return m_nWindowTitleBarHeight;
}

/**
*  @brief
*    Get menu bar height
*/
int Theme::GetMenuBarHeight() const
{
	// Return menu bar height
	return m_nMenuBarHeight;
}

/**
*  @brief
*    Get default window color
*/
Color4 Theme::GetWindowColor() const
{
	// Return window color
	return m_cWindowColor;
}

/**
*  @brief
*    Get panel border size
*/
int Theme::GetPanelBorderSize() const
{
	// Return border size
	return m_nPanelBorderSize;
}

/**
*  @brief
*    Get default panel color
*/
Color4 Theme::GetPanelColor() const
{
	// Return panel color
	return m_cPanelColor;
}

/**
*  @brief
*    Get system button size
*/
PLMath::Vector2i Theme::GetSysButtonSize() const
{
	// Return system button size
	return m_vSysButtonSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
