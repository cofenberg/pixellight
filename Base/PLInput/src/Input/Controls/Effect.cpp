/*********************************************************\
 *  File: Effect.cpp                                     *
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
#include "PLInput/Input/Controls/Effect.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Effect::Effect(Controller *pController, const String &sName, const String &sDescription) : Control(pController, ControlEffect, sName, sDescription),
	m_fValue(0.0f)
{
}

/**
*  @brief
*    Copy constructor
*/
Effect::Effect(const Effect &cOther) : Control(cOther.GetController(), ControlEffect, cOther.GetName(), cOther.GetDescription()),
	m_fValue(cOther.m_fValue)
{
}


/**
*  @brief
*    Destructor
*/
Effect::~Effect()
{
}

/**
*  @brief
*    Comparison operator
*/
bool Effect::operator ==(const Effect &cOther) const
{
	// Compare values
	return (m_fValue == cOther.m_fValue);
}

/**
*  @brief
*    Copy operator
*/
Effect &Effect::operator =(const Effect &cOther)
{
	// Copy value
	m_fValue = cOther.m_fValue;

	// Control has changed
	InformUpdate();

	// Return reference to this effect
	return *this;
}

/**
*  @brief
*    Get effect value
*/
float Effect::GetValue() const
{
	// Return value
	return m_fValue;
}

/**
*  @brief
*    Set effect value
*/
void Effect::SetValue(float fValue)
{
	// Set value
	m_fValue = fValue;

	// Control has changed
	InformUpdate();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
