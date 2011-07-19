/*********************************************************\
 *  File: TrollType.cpp                                  *
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
#include "TrollType.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TrollType::TrollType() :
	m_nValue(0)
{
}

/**
*  @brief
*    Constructor
*/
TrollType::TrollType(int nValue) :
	m_nValue(0)
{
	SetValue(nValue);
}

/**
*  @brief
*    Copy constructor
*/
TrollType::TrollType(const TrollType &cOther) :
	m_nValue(cOther.m_nValue)
{
}

/**
*  @brief
*    Destructor
*/
TrollType::~TrollType()
{
}

/**
*  @brief
*    Copy operator
*/
TrollType &TrollType::operator =(const TrollType &cOther)
{
	m_nValue = cOther.m_nValue;
	return *this;
}

/**
*  @brief
*    comparison operator
*/
bool TrollType::operator ==(const TrollType &cOther) const
{
	return (m_nValue == cOther.m_nValue);
}

/**
*  @brief
*    Get value
*/
int TrollType::GetValue() const
{
	// Return value
	return m_nValue;
}

/**
*  @brief
*    Set value
*/
void TrollType::SetValue(int nValue)
{
	// Try to remember value ...
	if (nValue >= 0 && nValue <=2)	m_nValue = nValue;
	else if (nValue > 2)			m_nValue =  3;
	else							m_nValue = -1;
}

/**
*  @brief
*    Get comment from troll
*/
String TrollType::GetComment() const
{
	// Return comment about current value
		 if (m_nValue == 0)	return "nuthin'";
	else if (m_nValue == 1)	return "one";
	else if (m_nValue == 2)	return "two";
	else if (m_nValue  > 0)	return "many";
	else					return "wuz?";
}
