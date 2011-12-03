/*********************************************************\
 *  File: XmlDocument.inl                                *
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
*    Load a file using the current document value
*/
inline bool XmlDocument::Load(EEncoding nEncoding)
{
	return Load(m_sValue, nEncoding);
}

/**
*  @brief
*    Save a file using the current document value
*/
inline bool XmlDocument::Save()
{
	return Save(m_sValue);
}

/**
*  @brief
*    Get the root element -- the only top level element -- of the document
*/
inline XmlElement *XmlDocument::GetRootElement()
{
	return GetFirstChildElement();
}

inline const XmlElement *XmlDocument::GetRootElement() const
{
	return GetFirstChildElement();
}

/**
*  @brief
*    If an error occurs, error will be set to true
*/
inline bool XmlDocument::Error() const
{
	return m_bError;
}

/**
*  @brief
*    Generally, you probably want the error string ('GetErrorDesc()') - but if you
*    prefer the error ID, this function will fetch it
*/
inline int XmlDocument::GetErrorID() const
{
	return m_nErrorID;
}

/**
*  @brief
*    Returns the location (if known) of the error
*/
inline int XmlDocument::GetErrorRow() const
{
	return m_cErrorCursor.nRow + 1;
}

/**
*  @brief
*    The column where the error occurred
*/
inline int XmlDocument::GetErrorColumn() const
{
	return  m_cErrorCursor.nColumn + 1;
}

/**
*  @brief
*    Returns the tab size
*/
inline uint32 XmlDocument::GetTabSize() const
{
	return m_nTabSize;
}

/**
*  @brief
*    Sets the tab size
*/
inline void XmlDocument::SetTabSize(uint32 nTabSize)
{
	m_nTabSize = nTabSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
