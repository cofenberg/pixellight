/*********************************************************\
 *  File: Button.cpp                                     *
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
#include "PLInput/Input/Controls/Button.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Button::Button(Controller *pController, const String &sName, const String &sDescription, char nCharacter) : Control(pController, ControlButton, sName, sDescription),
	m_nCharacter(nCharacter),
	m_bPressed(false),
	m_bHit(false)
{
}

/**
*  @brief
*    Copy constructor
*/
Button::Button(const Button &cOther) : Control(cOther.GetController(), ControlButton, cOther.GetName(), cOther.GetDescription()),
	m_nCharacter(cOther.m_nCharacter),
	m_bPressed(cOther.m_bPressed),
	m_bHit(cOther.m_bHit)
{
}


/**
*  @brief
*    Destructor
*/
Button::~Button()
{
}

/**
*  @brief
*    Comparison operator
*/
bool Button::operator ==(const Button &cOther) const
{
	// Compare values
	return (m_nCharacter == cOther.m_nCharacter && m_bPressed == cOther.m_bPressed && m_bHit == cOther.m_bHit);
}

/**
*  @brief
*    Copy operator
*/
Button &Button::operator =(const Button &cOther)
{
	// Copy value
	m_nCharacter = cOther.m_nCharacter;
	m_bPressed	 = cOther.m_bPressed;
	m_bHit		 = cOther.m_bHit;

	// Control has changed
	InformUpdate();

	// Return reference to this button
	return *this;
}

/**
*  @brief
*    Get character
*/
char Button::GetCharacter() const
{
	// Return character
	return m_nCharacter;
}

/**
*  @brief
*    Get button status
*/
bool Button::IsPressed() const
{
	// Return state
	return m_bPressed;
}

/**
*  @brief
*    Set button status
*/
void Button::SetPressed(bool bPressed)
{
	// If the button was previously pressed but now isn't, we received a hit
	if (m_bPressed && !bPressed) m_bHit = true;
	else						 m_bHit = false;

	// Set state
	m_bPressed = bPressed;

	// Control has changed
	InformUpdate();
}

/**
*  @brief
*    Check if the button has been hit
*/
bool Button::IsHit()
{
	// Return hit-state
	bool bHit = m_bHit;
	m_bHit = false;
	return bHit;
}

/**
*  @brief
*    Check if the button has been hit
*/
bool Button::CheckHit()
{
	// Return hit-state
	return m_bHit;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
