/*********************************************************\
 *  File: Localization.inl                               *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the current language
*/
inline String Localization::GetLanguage() const
{
	return m_sLanguage;
}

/**
*  @brief
*    Sets the current language
*/
inline void Localization::SetLanguage(const String &sLanguage)
{
	// Just set the new language
	m_sLanguage = sLanguage;
}

/**
*  @brief
*    Returns the number of groups
*/
inline uint32 Localization::GetNumOfGroups() const
{
	return m_lstGroups.GetNumOfElements();
}

/**
*  @brief
*    Returns a group by index
*/
inline LocalizationGroup *Localization::GetGroup(uint32 nIndex) const
{
	return m_lstGroups[nIndex];
}

/**
*  @brief
*    Returns a group by name
*/
inline LocalizationGroup *Localization::GetGroup(const String &sName) const
{
	return m_mapGroups.Get(sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
