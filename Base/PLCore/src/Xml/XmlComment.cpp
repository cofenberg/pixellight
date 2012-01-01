/*********************************************************\
 *  File: XmlComment.cpp                                 *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string.h>
#include "PLCore/File/File.h"
#include "PLCore/Xml/XmlParsingData.h"
#include "PLCore/Xml/XmlDocument.h"
#include "PLCore/Xml/XmlComment.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
XmlComment::XmlComment() : XmlNode(Comment)
{
}

/**
*  @brief
*    Constructor
*/
XmlComment::XmlComment(const String &sValue) : XmlNode(Comment)
{
	// Copy the value
	SetValue(sValue);
}

/**
*  @brief
*    Copy constructor
*/
XmlComment::XmlComment(const XmlComment &cSource) : XmlNode(Comment)
{
	// Copy the value
	SetValue(cSource.GetValue());
}

/**
*  @brief
*    Destructor
*/
XmlComment::~XmlComment()
{
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlComment::Save(File &cFile, uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	const uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	for (uint32 i=0; i<nNumOfSpaces; i++)
		cFile.PutC(' ');

	// Write value
	cFile.Print("<!--" + m_sValue + "-->");

	// Done
	return true;
}

String XmlComment::ToString(uint32 nDepth) const
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	const uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	String sXml;
	for (uint32 i=0; i<nNumOfSpaces; i++)
		sXml += ' ';

	// Write value
	sXml += "<!--" + m_sValue + "-->";

	// Return the resulting string
	return sXml;
}

const char *XmlComment::Parse(const char *pszData, XmlParsingData *pData, EEncoding nEncoding)
{
	// Constants
	static const char   *pszStartTag     = "<!--";
	static const uint32  nStartTagLength = static_cast<uint32>(strlen(pszStartTag));
	static const char   *pszEndTag       = "-->";
	static const uint32  nEndTagLength   = static_cast<uint32>(strlen(pszEndTag));

	m_sValue = "";

	pszData = SkipWhiteSpace(pszData, nEncoding);

	if (pData) {
		pData->Stamp(pszData, nEncoding);
		m_cCursor = pData->Cursor();
	}

	if (!StringEqual(pszData, pszStartTag, false, nEncoding)) {
		// Set error code
		XmlDocument *pDocument = GetDocument();
		if (pDocument)
			pDocument->SetError(ErrorParsingComment, pszData, pData, nEncoding);

		// Error!
		return nullptr;
	}
	pszData += nStartTagLength;

	// Keep all the white space
	while (pszData && *pszData && !StringEqual(pszData, pszEndTag, false, nEncoding)) {
		m_sValue += *pszData;
		++pszData;
	}
	if (pszData && *pszData)
		pszData += nEndTagLength;

	// Done
	return pszData;
}


//[-------------------------------------------------------]
//[ Public virtual XmlNode functions                      ]
//[-------------------------------------------------------]
XmlNode *XmlComment::Clone() const
{
	return new XmlComment(*this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
