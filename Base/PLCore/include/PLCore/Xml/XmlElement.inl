/*********************************************************\
 *  File: XmlElement.inl                                 *
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Access the first attribute in this element
*/
inline XmlAttribute *XmlElement::GetFirstAttribute()
{
	return m_cAttributeSet.GetFirst();
}

inline const XmlAttribute *XmlElement::GetFirstAttribute() const
{
	return m_cAttributeSet.GetFirst();
}

/**
*  @brief
*    Access the last attribute in this element
*/
inline XmlAttribute *XmlElement::GetLastAttribute()
{
	return m_cAttributeSet.GetLast();
}

inline const XmlAttribute *XmlElement::GetLastAttribute() const
{
	return m_cAttributeSet.GetLast();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
