/*********************************************************\
 *  File: LED.cpp                                        *
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
#include "PLInput/Input/Controls/LED.h"


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
LED::LED(Controller *pController, const String &sName, const String &sDescription) : Control(pController, ControlLED, sName, sDescription),
	m_nLEDs(0)
{
}

/**
*  @brief
*    Copy constructor
*/
LED::LED(const LED &cOther) : Control(cOther.GetController(), ControlLED, cOther.GetName(), cOther.GetDescription()),
	m_nLEDs(cOther.m_nLEDs)
{
}


/**
*  @brief
*    Destructor
*/
LED::~LED()
{
}

/**
*  @brief
*    Comparison operator
*/
bool LED::operator ==(const LED &cOther) const
{
	// Compare values
	return (m_nLEDs == cOther.m_nLEDs);
}

/**
*  @brief
*    Copy operator
*/
LED &LED::operator =(const LED &cOther)
{
	// Copy value
	m_nLEDs = cOther.m_nLEDs;

	// Control has changed
	InformUpdate();

	// Return reference to this LED
	return *this;
}

/**
*  @brief
*    Get state of all LEDs as a bitfield
*/
uint32 LED::GetLEDs() const
{
	// Return state of LEDs
	return m_nLEDs;
}

/**
*  @brief
*    Set state of all LEDs as a bitfield
*/
void LED::SetLEDs(uint32 nLEDs)
{
	// Set state of LEDs
	m_nLEDs = nLEDs;

	// Control has changed
	InformUpdate();
}

/**
*  @brief
*    Get LED status
*/
bool LED::IsOn(int nLED) const
{
	// Check index
	if (nLED >= 0 && nLED < 32) {
		// Check if LED is on
		return ((m_nLEDs >> nLED) & 1) != 0;
	}

	// Wrong index
	return false;
}

/**
*  @brief
*    Set LED status
*/
void LED::SetOn(int nLED, bool bOn)
{
	// Check index
	if (nLED >= 0 && nLED < 32) {
		// Set LED state
		uint32 nMask = ((uint32)1) << nLED;
		if (bOn)
			m_nLEDs |= nMask;
		else
			m_nLEDs &= nMask;

		// Control has changed
		InformUpdate();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
