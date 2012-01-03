/*********************************************************\
 *  File: LocalizationGroup.cpp                          *
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
#include "PLCore/Tools/Loader.h"
#include "PLCore/Tools/LocalizationText.h"
#include "PLCore/Tools/LocalizationGroup.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String LocalizationGroup::English = "English";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a new text
*/
LocalizationText *LocalizationGroup::AddText(const String &sName, const String &sTranslation)
{
	// Is there already a text with the given name?
	LocalizationText *pText = m_mapTexts.Get(sName);
	if (pText)
		return nullptr; // Jap, error!

	// Create the new text
	pText = new LocalizationText(*this, sName, sTranslation);
	m_lstTexts.Add(pText);
	m_mapTexts.Add(sName, pText);

	// Return the new text
	return pText;
}

/**
*  @brief
*    Removes a text by index
*/
bool LocalizationGroup::RemoveText(uint32 nIndex)
{
	// Get the text
	LocalizationText *pText = m_lstTexts[nIndex];
	if (!pText)
		return false; // Error!

	// Remove the text
	m_mapTexts.Remove(pText->GetName());
	m_lstTexts.RemoveAtIndex(nIndex);
	delete pText;

	// Done
	return true;
}

/**
*  @brief
*    Removes a text by name
*/
bool LocalizationGroup::RemoveText(const String &sName)
{
	// Get the text
	LocalizationText *pText = m_mapTexts.Get(sName);
	if (!pText)
		return false; // Error!

	// Remove the text
	m_mapTexts.Remove(pText->GetName());
	m_lstTexts.Remove(pText);
	delete pText;

	// Done
	return true;
}

/**
*  @brief
*    Removes all texts
*/
void LocalizationGroup::RemoveAllTexts()
{
	for (uint32 i=0; i<m_lstTexts.GetNumOfElements(); i++)
		delete m_lstTexts[i];
	m_lstTexts.Clear();
	m_mapTexts.Clear();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LocalizationGroup::LocalizationGroup(const String &sName) :
	m_sName(sName),
	m_sFromLanguage(English),
	m_sToLanguage(English)
{
}

/**
*  @brief
*    Copy constructor
*/
LocalizationGroup::LocalizationGroup(const LocalizationGroup &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
LocalizationGroup::~LocalizationGroup()
{
}

/**
*  @brief
*    Copy operator
*/
LocalizationGroup &LocalizationGroup::operator =(const LocalizationGroup &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual Loadable functions                     ]
//[-------------------------------------------------------]
bool LocalizationGroup::Unload()
{
	// Cleanup
	RemoveAllTexts();
	m_sFromLanguage = English;
	m_sToLanguage   = English;

	// Call base implementation
	return Loadable::Unload();
}

String LocalizationGroup::GetLoadableTypeName() const
{
	return "Localization";
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
