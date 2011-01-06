/*********************************************************\
 *  File: LocalizationText.cpp                           *
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
#include "PLCore/Tools/LocalizationText.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the group the text is in
*/
LocalizationGroup &LocalizationText::GetGroup() const
{
	return *m_pGroup;
}

/**
*  @brief
*    Returns the name of the text
*/
String LocalizationText::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns the translation of the text
*/
String LocalizationText::GetTranslation() const
{
	return m_sTranslation;
}

/**
*  @brief
*    Sets the translation of the text
*/
void LocalizationText::SetTranslation(const String &sTranslation)
{
	m_sTranslation = sTranslation;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LocalizationText::LocalizationText(LocalizationGroup &cGroup, const String &sName, const String &sTranslation) :
	m_pGroup(&cGroup),
	m_sName(sName),
	m_sTranslation(sTranslation)
{
}

/**
*  @brief
*    Copy constructor
*/
LocalizationText::LocalizationText(const LocalizationText &cSource) :
	m_pGroup(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
LocalizationText::~LocalizationText()
{
}

/**
*  @brief
*    Copy operator
*/
LocalizationText &LocalizationText::operator =(const LocalizationText &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
