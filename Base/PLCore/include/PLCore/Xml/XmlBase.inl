/*********************************************************\
 *  File: XmlBase.inl                                    *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the current white space setting
*/
inline bool XmlBase::IsWhiteSpaceCondensed()
{
	return bCondenseWhiteSpace;
}

/**
*  @brief
*    Set white space handling
*/
inline void XmlBase::SetCondenseWhiteSpace(bool bCondense)
{
	bCondenseWhiteSpace = bCondense;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the row position, in the original source file, of this node or attribute
*/
inline int XmlBase::GetRow() const
{
	return m_cCursor.nRow + 1;
}

/**
*  @brief
*    Return the column position, in the original source file, of this node or attribute
*/
inline int XmlBase::GetColumn() const
{
	return m_cCursor.nColumn + 1;
}

/**
*  @brief
*    Returns the user data
*/
inline void *XmlBase::GetUserData() const
{
	return m_pUserData;
}

/**
*  @brief
*    Sets the user data
*/
inline void XmlBase::SetUserData(void *pUser)
{
	m_pUserData = pUser;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
