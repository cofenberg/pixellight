/*********************************************************\
 *  File: XmlUnknown.cpp                                 *
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
#include "PLCore/File/File.h"
#include "PLCore/Xml/XmlParsingData.h"
#include "PLCore/Xml/XmlDocument.h"
#include "PLCore/Xml/XmlUnknown.h"


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
XmlUnknown::XmlUnknown() : XmlNode(Unknown)
{
}

/**
*  @brief
*    Copy constructor
*/
XmlUnknown::XmlUnknown(const XmlUnknown &cSource) : XmlNode(Unknown)
{
	// Copy the value
	SetValue(cSource.GetValue());
}

/**
*  @brief
*    Destructor
*/
XmlUnknown::~XmlUnknown()
{
}

/**
*  @brief
*    Copy operator
*/
XmlUnknown &XmlUnknown::operator =(const XmlUnknown &cSource)
{
	// Copy the value
	SetValue(cSource.GetValue());
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlUnknown::Save(File &cFile, uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	const uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	for (uint32 i=0; i<nNumOfSpaces; i++)
		cFile.PutC(' ');

	// Write value
	cFile.Print('<' + m_sValue + '>');

	// Done
	return true;
}

String XmlUnknown::ToString(uint32 nDepth) const
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	const uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	String sXml;
	for (uint32 i=0; i<nNumOfSpaces; i++)
		sXml += ' ';

	// Write value
	sXml += '<' + m_sValue + '>';

	// Return the resulting string
	return sXml;
}

const char *XmlUnknown::Parse(const char *pszData, XmlParsingData *pData, EEncoding nEncoding)
{
	pszData = SkipWhiteSpace(pszData, nEncoding);

	if (pData) {
		pData->Stamp(pszData, nEncoding);
		m_cCursor = pData->Cursor();
	}
	if (!pszData || !*pszData || *pszData != '<') {
		// Set error code
		XmlDocument *pDocument = GetDocument();
		if (pDocument)
			pDocument->SetError(ErrorParsingUnknown, pszData, pData, nEncoding);

		// Error!
		return nullptr;
	}
	++pszData;
	m_sValue = "";

	while (pszData && *pszData && *pszData != '>') {
		m_sValue += *pszData;
		++pszData;
	}

	if (!pszData) {
		// Set error code
		XmlDocument *pDocument = GetDocument();
		if (pDocument)
			pDocument->SetError(ErrorParsingUnknown, 0, 0, nEncoding);
	}
	if (pszData && *pszData == '>')
		return pszData + 1;

	// Done
	return pszData;
}


//[-------------------------------------------------------]
//[ Public virtual XmlNode functions                      ]
//[-------------------------------------------------------]
XmlNode *XmlUnknown::Clone() const
{
	return new XmlUnknown(*this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
