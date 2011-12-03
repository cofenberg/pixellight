/*********************************************************\
 *  File: HTMLParser.inl                                 *
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
*    Constructor
*/
inline HTMLParser::HTMLParser() :
	m_nPos(0),
	m_pXML(nullptr),
	m_nErrors(0)
{
}

/**
*  @brief
*    Destructor
*/
inline HTMLParser::~HTMLParser()
{
	// Destroy data
	Clear();
}

/**
*  @brief
*    Get parsed HTML as an XML document
*/
inline XmlDocument *HTMLParser::GetXML() const
{
	// Return HTML tree
	return m_pXML;
}

/**
*  @brief
*    Get number of errors occurring while parsing the HTML file
*/
inline uint32 HTMLParser::GetNumOfErrors() const
{
	// Return number of errors
	return m_nErrors;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether or not the given string is a single tag (no closing tag required to be well-formed!)
*/
inline bool HTMLParser::IsSingleTag(const String &sTag) const
{
	// Identify known tokens that don't need a closing-tag
	return (sTag == "img" || sTag == "br" || sTag == "hr");
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
