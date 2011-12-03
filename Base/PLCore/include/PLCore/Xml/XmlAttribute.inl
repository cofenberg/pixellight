/*********************************************************\
 *  File: XmlAttribute.inl                               *
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
*    Return the name of this attribute
*/
inline String XmlAttribute::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set the name of this attribute
*/
inline void XmlAttribute::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Return the value of this attribute
*/
inline String XmlAttribute::GetValue() const
{
	return m_sValue;
}

/**
*  @brief
*    Return the value of this attribute, converted to an integer
*/
inline int XmlAttribute::GetIntValue() const
{
	return m_sValue.GetInt();
}

/**
*  @brief
*    Return the value of this attribute, converted to a double
*/
inline double XmlAttribute::GetDoubleValue() const
{
	return m_sValue.GetDouble();
}

/**
*  @brief
*    Set the value
*/
inline void XmlAttribute::SetValue(const String &sValue)
{
	m_sValue = sValue;
}

/**
*  @brief
*    Set the value from an integer
*/
inline void XmlAttribute::SetIntValue(int nValue)
{
	m_sValue = nValue;
}

/**
*  @brief
*    Set the value from a double
*/
inline void XmlAttribute::SetDoubleValue(double dValue)
{
	m_sValue = dValue;
}

/**
*  @brief
*    Get the next sibling attribute in the DOM
*/
inline XmlAttribute *XmlAttribute::GetNext()
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pNextAttribute->m_sValue.GetLength() && !m_pNextAttribute->m_sName.GetLength()) ? nullptr : m_pNextAttribute;
}

inline const XmlAttribute *XmlAttribute::GetNext() const
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pNextAttribute->m_sValue.GetLength() && !m_pNextAttribute->m_sName.GetLength()) ? nullptr : m_pNextAttribute;
}

/**
*  @brief
*    Get the previous sibling attribute in the DOM
*/
inline XmlAttribute *XmlAttribute::GetPrevious()
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pPreviousAttribute->m_sValue.GetLength() && !m_pPreviousAttribute->m_sName.GetLength()) ? nullptr : m_pPreviousAttribute;
}

inline const XmlAttribute *XmlAttribute::GetPrevious() const
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pPreviousAttribute->m_sValue.GetLength() && !m_pPreviousAttribute->m_sName.GetLength()) ? nullptr : m_pPreviousAttribute;
}

inline bool XmlAttribute::operator ==(const XmlAttribute &cOther) const
{
	return (cOther.m_sName == m_sName);
}

inline bool XmlAttribute::operator <(const XmlAttribute &cOther) const
{
	return (m_sName < cOther.m_sName);
}

inline bool XmlAttribute::operator >(const XmlAttribute &cOther) const
{
	return (m_sName > cOther.m_sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
