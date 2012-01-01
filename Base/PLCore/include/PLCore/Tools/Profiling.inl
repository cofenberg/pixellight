/*********************************************************\
 *  File: Profiling.inl                                  *
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
*    Returns the text of the element
*/
inline String ProfileGroupElement::GetText() const
{
	return m_sText;
}

/**
*  @brief
*    Sets the element text
*/
inline bool ProfileGroupElement::SetText(const String &sText)
{
	// Set text
	m_sText = sText;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
inline ProfileGroupElement &ProfileGroupElement::operator =(const ProfileGroupElement &cSource)
{
	// Copy text
	m_sText = cSource.m_sText;

	// Return this implementation
	return *this;
}




//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the text of the element group
*/
inline String ProfileGroup::GetText() const
{
	return m_sText;
}

/**
*  @brief
*    Sets the element group text
*/
inline bool ProfileGroup::SetText(const String &sText)
{
	// Set text
	m_sText = sText;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
inline ProfileGroup &ProfileGroup::operator =(const ProfileGroup &cSource)
{
	// Copy text
	m_sText = cSource.m_sText;

	// Call base implementation

	// Return this implementation
	return *this;
}




//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether the profiling system is active or not
*/
inline bool Profiling::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the profiling system is active or not
*/
inline void Profiling::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Returns the name of the current selected profile group
*/
inline String Profiling::GetSelectedGroup() const
{
	return m_sGroupName;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
