/*********************************************************\
 *  File: LocalizationGroup.inl                          *
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
*    Returns the name of the group
*/
inline String LocalizationGroup::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns the language used as 'from-key'
*/
inline String LocalizationGroup::GetFromLanguage() const
{
	return m_sFromLanguage;
}

/**
*  @brief
*    Sets the language used as 'from-key'
*/
inline void LocalizationGroup::SetFromLanguage(const String &sFrom)
{
	m_sFromLanguage = sFrom;
}

/**
*  @brief
*    Returns the language used as 'to-key'
*/
inline String LocalizationGroup::GetToLanguage() const
{
	return m_sToLanguage;
}

/**
*  @brief
*    Sets the language used as 'to-key'
*/
inline void LocalizationGroup::SetToLanguage(const String &sTo)
{
	m_sToLanguage = sTo;
}

/**
*  @brief
*    Returns the number of texts
*/
inline uint32 LocalizationGroup::GetNumOfTexts() const
{
	return m_lstTexts.GetNumOfElements();
}

/**
*  @brief
*    Returns a text by index
*/
inline LocalizationText *LocalizationGroup::GetText(uint32 nIndex) const
{
	return m_lstTexts[nIndex];
}

/**
*  @brief
*    Returns a text by name
*/
inline LocalizationText *LocalizationGroup::GetText(const String &sName) const
{
	return m_mapTexts.Get(sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
