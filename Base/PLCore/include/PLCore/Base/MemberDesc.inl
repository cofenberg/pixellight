/*********************************************************\
 *  File: MemberDesc.inl                                 *
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
*    Get type
*/
inline EMemberType MemberDesc::GetMemberType() const
{
	// Return type
	return m_nMemberType;
}

/**
*  @brief
*    Get name
*/
inline String MemberDesc::GetName() const
{
	// Return name of var
	return m_sName;
}

/**
*  @brief
*    Get description
*/
inline String MemberDesc::GetDescription() const
{
	// Return description of var
	return m_sDescription;
}

/**
*  @brief
*    Get annotation
*/
inline String MemberDesc::GetAnnotation() const
{
	// Return annotation of var
	return m_sAnnotation;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
