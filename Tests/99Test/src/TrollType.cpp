/*********************************************************\
 *  File: TrollType.cpp                                  *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
