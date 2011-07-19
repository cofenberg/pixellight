/*********************************************************\
 *  File: Axis.cpp                                       *
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
#include "PLInput/Input/Controls/Axis.h"


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
Axis::Axis(Controller *pController, const String &sName, const String &sDescription) : Control(pController, ControlAxis, sName, sDescription),
	m_fValue(0.0f),
	m_bValueRelative(false)
{
}

/**
*  @brief
*    Copy constructor
*/
Axis::Axis(const Axis &cOther) : Control(cOther.GetController(), ControlAxis, cOther.GetName(), cOther.GetDescription()),
	m_fValue(cOther.m_fValue),
	m_bValueRelative(cOther.m_bValueRelative)
{
}

/**
*  @brief
*    Destructor
*/
Axis::~Axis()
{
}

/**
*  @brief
*    Comparison operator
*/
bool Axis::operator ==(const Axis &cOther) const
{
	// Compare values
	return (m_fValue == cOther.m_fValue && m_bValueRelative == cOther.m_bValueRelative);
}

/**
*  @brief
*    Copy operator
*/
Axis &Axis::operator =(const Axis &cOther)
{
	// Copy value
	m_fValue		 = cOther.m_fValue;
	m_bValueRelative = cOther.m_bValueRelative;

	// Control has changed
	InformUpdate();

	// Return reference to this axis
	return *this;
}

/**
*  @brief
*    Get axis value
*/
float Axis::GetValue() const
{
	// Return value
	return m_fValue;
}

/**
*  @brief
*    Set axis value
*/
void Axis::SetValue(float fValue, bool bValueRelative)
{
	// Set value
	m_fValue		 = fValue;
	m_bValueRelative = bValueRelative;

	// Control has changed
	InformUpdate();
}

/**
*  @brief
*    Return whether the current value is relative or absolute
*/
bool Axis::IsValueRelative() const
{
	return m_bValueRelative;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
