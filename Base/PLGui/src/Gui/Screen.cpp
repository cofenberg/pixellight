/*********************************************************\
 *  File: Screen.cpp                                     *
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
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Gui/Screen.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Screen::Screen(Gui *pGui) :
	m_pGui(pGui),
	m_pDesktopWidget(nullptr),
	m_bDefault(false)
{
}

/**
*  @brief
*    Destructor
*/
Screen::~Screen()
{
	// Destroy desktop widget
	if (m_pDesktopWidget) {
		delete m_pDesktopWidget;
	}
}

/**
*  @brief
*    Get owner GUI
*/
Gui *Screen::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get screen name
*/
String Screen::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Set screen name
*/
void Screen::SetName(const String &sName)
{
	// Set name
	m_sName = sName;
}

/**
*  @brief
*    Get screen position
*/
Vector2i Screen::GetPos() const
{
	// Return position
	return m_vPos;
}

/**
*  @brief
*    Set screen position
*/
void Screen::SetPos(const PLMath::Vector2i &vPos)
{
	// Set pos
	m_vPos = vPos;
}

/**
*  @brief
*    Get screen size
*/
Vector2i Screen::GetSize() const
{
	// Return size
	return m_vSize;
}

/**
*  @brief
*    Set screen size
*/
void Screen::SetSize(const Vector2i &vSize)
{
	// Set size
	m_vSize = vSize;
}

/**
*  @brief
*    Check if this is the primary screen
*/
bool Screen::IsDefault() const
{
	// Return default flag
	return m_bDefault;
}

/**
*  @brief
*    Set if this is the default screen
*/
void Screen::SetDefault(bool bDefault)
{
	// Set default flag
	m_bDefault = bDefault;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
