/*********************************************************\
 *  File: XmlText.cpp                                    *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string.h>
#include "PLGeneral/File/File.h"
#include "PLGeneral/Xml/XmlParsingData.h"
#include "PLGeneral/Xml/XmlDocument.h"
#include "PLGeneral/Xml/XmlText.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlText::XmlText() : XmlNode(Text),
	m_bCDATA(false)
{
}

/**
*  @brief
*    Default constructor
*/
XmlText::XmlText(const String &sValue) : XmlNode(Text),
	m_bCDATA(false)
{
	// Copy the value
	SetValue(sValue);
}

/**
*  @brief
*    Copy constructor
*/
XmlText::XmlText(const XmlText &cSource) : XmlNode(Text),
	m_bCDATA(cSource.m_bCDATA)
{
	// Copy the value
	SetValue(cSource.GetValue());
}

/**
*  @brief
*    Destructor
*/
XmlText::~XmlText()
{
}

/**
*  @brief
*    Copy operator
*/
XmlText &XmlText::operator =(const XmlText &cSource)
{
	// Copy data
	m_bCDATA = cSource.m_bCDATA;
	SetValue(cSource.GetValue());
	return *this;
}

/**
*  @brief
*    Queries whether this represents text using a CDATA section
*/
bool XmlText::IsCDATA() const
{
	return m_bCDATA;
}

/**
*  @brief
*    Turns on or off a CDATA representation of text
*/
void XmlText::SetCDATA(bool bCDATA)
{
	m_bCDATA = bCDATA;
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlText::Save(File &cFile, uint32 nDepth)
{
	String sBuffer;
	EncodeString(m_sValue, sBuffer);
	cFile.Print(sBuffer);

	// Done
	return true;
}

String XmlText::ToString(uint32 nDepth) const
{
	String sBuffer;
	EncodeString(m_sValue, sBuffer);
	return String(sBuffer);
}

const char *XmlText::Parse(const char *pszData, XmlParsingData *pData, EEncoding nEncoding)
{
	// Constants
	static const char   *pszStartTag     = "<![CDATA[";
	static const uint32  nStartTagLength = strlen(pszStartTag);
	static const char   *pszEndTag       = "]]>";
	static const char   *pszEnd          = "<";

	m_sValue = "";

	if (pData) {
		pData->Stamp(pszData, nEncoding);
		m_cCursor = pData->Cursor();
	}

	if (m_bCDATA || StringEqual(pszData, pszStartTag, false, nEncoding)) {
		m_bCDATA = true;

		if (!StringEqual(pszData, pszStartTag, false, nEncoding)){
			// Set error code
			XmlDocument *pDocument = GetDocument();
			if (pDocument)
				pDocument->SetError(ErrorParsingCData, pszData, pData, nEncoding);

			// Error!
			return nullptr;
		}
		pszData += nStartTagLength;

		// Keep all the white space, ignore the encoding, etc.
		while (pszData && *pszData && !StringEqual(pszData, pszEndTag, false, nEncoding)) {
			m_sValue += *pszData;
			++pszData;
		}

		String sDummy;
		pszData = ReadText(pszData, sDummy, false, pszEndTag, false, nEncoding);

		// Done
		return pszData;
	} else {
		bool bIgnoreWhite = true;
		pszData = ReadText(pszData, m_sValue, bIgnoreWhite, pszEnd, false, nEncoding);
		if (pszData && *pszData)
			return pszData - 1;	// don't truncate the '<'

		// Error!
		return nullptr;
	}
}


//[-------------------------------------------------------]
//[ Public virtual XmlNode functions                      ]
//[-------------------------------------------------------]
XmlNode *XmlText::Clone() const
{
	return new XmlText(*this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
