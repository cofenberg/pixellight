/*********************************************************\
 *  File: Localization.cpp                               *
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
#include "PLCore/Tools/LocalizationGroup.h"
#include "PLCore/Tools/Localization.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String Localization::PixelLight = "PixelLight";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the current language
*/
String Localization::GetLanguage() const
{
	return m_sLanguage;
}

/**
*  @brief
*    Sets the current language
*/
void Localization::SetLanguage(const String &sLanguage)
{
	// Just set the new language
	m_sLanguage = sLanguage;
}

/**
*  @brief
*    Returns the translation of the given text
*/
String Localization::Get(const String &sText, const String &sGroup) const
{
	// Get the group
	const LocalizationGroup *pGroup = m_mapGroups.Get(sGroup);
	if (pGroup) {
		// Get the text
		const LocalizationText *pText = pGroup->GetText(sText);
		if (pText) return pText->GetTranslation();
	}

	// Error! Return the given text instead...
	return sText;
}

/**
*  @brief
*    Returns the number of groups
*/
uint32 Localization::GetNumOfGroups() const
{
	return m_lstGroups.GetNumOfElements();
}

/**
*  @brief
*    Returns a group by index
*/
LocalizationGroup *Localization::GetGroup(uint32 nIndex) const
{
	return m_lstGroups[nIndex];
}

/**
*  @brief
*    Returns a group by name
*/
LocalizationGroup *Localization::GetGroup(const String &sName) const
{
	return m_mapGroups.Get(sName);
}

/**
*  @brief
*    Adds a new group
*/
LocalizationGroup *Localization::AddGroup(const String &sName)
{
	// Is there already a group with the given name?
	LocalizationGroup *pGroup = m_mapGroups.Get(sName);
	if (pGroup)
		return nullptr; // Jap, error!

	// Create the new group
	pGroup = new LocalizationGroup(sName);
	m_lstGroups.Add(pGroup);
	m_mapGroups.Add(sName, pGroup);

	// Return the new group
	return pGroup;
}

/**
*  @brief
*    Removes a group by index
*/
bool Localization::RemoveGroup(uint32 nIndex)
{
	// Get the group
	LocalizationGroup *pGroup = m_lstGroups[nIndex];
	if (!pGroup) return false; // Error!

	// Remove the group
	m_mapGroups.Remove(pGroup->GetName());
	m_lstGroups.RemoveAtIndex(nIndex);
	delete pGroup;

	// Done
	return true;
}

/**
*  @brief
*    Removes a group by name
*/
bool Localization::RemoveGroup(const String &sName)
{
	// Get the group
	LocalizationGroup *pGroup = m_mapGroups.Get(sName);
	if (!pGroup) return false; // Error!

	// Remove the group
	m_mapGroups.Remove(pGroup->GetName());
	m_lstGroups.Remove(pGroup);
	delete pGroup;

	// Done
	return true;
}

/**
*  @brief
*    Removes all groups
*/
void Localization::RemoveAllGroups()
{
	for (uint32 i=0; i<m_lstGroups.GetNumOfElements(); i++)
		delete m_lstGroups[i];
	m_lstGroups.Clear();
	m_mapGroups.Clear();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Localization::Localization()
{
}

/**
*  @brief
*    Copy constructor
*/
Localization::Localization(const Localization &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
Localization::~Localization()
{
	// Cleanup
	RemoveAllGroups();
}

/**
*  @brief
*    Copy operator
*/
Localization &Localization::operator =(const Localization &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
