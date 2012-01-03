/*********************************************************\
 *  File: LocalizationText.inl                           *
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
*    Returns the group the text is in
*/
inline LocalizationGroup &LocalizationText::GetGroup() const
{
	return *m_pGroup;
}

/**
*  @brief
*    Returns the name of the text
*/
inline String LocalizationText::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns the translation of the text
*/
inline String LocalizationText::GetTranslation() const
{
	return m_sTranslation;
}

/**
*  @brief
*    Sets the translation of the text
*/
inline void LocalizationText::SetTranslation(const String &sTranslation)
{
	m_sTranslation = sTranslation;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
