/*********************************************************\
 *  File: XmlDeclaration.cpp                             *
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
#include "PLGeneral/File/File.h"
#include "PLGeneral/Xml/XmlParsingData.h"
#include "PLGeneral/Xml/XmlDocument.h"
#include "PLGeneral/Xml/XmlAttribute.h"
#include "PLGeneral/Xml/XmlDeclaration.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
XmlDeclaration::XmlDeclaration() : XmlNode(Declaration)
{
}

/**
*  @brief
*    Constructor
*/
XmlDeclaration::XmlDeclaration(const String &sVersion, const String &sEncoding, const String &sStandalone) : XmlNode(Declaration),
	m_sVersion(sVersion),
	m_sEncoding(sEncoding),
	m_sStandalone(sStandalone)
{
}

/**
*  @brief
*    Copy constructor
*/
XmlDeclaration::XmlDeclaration(const XmlDeclaration &cSource) : XmlNode(Declaration),
	m_sVersion(cSource.m_sVersion),
	m_sEncoding(cSource.m_sEncoding),
	m_sStandalone(cSource.m_sStandalone)
{
}

/**
*  @brief
*    Destructor
*/
XmlDeclaration::~XmlDeclaration()
{
}

/**
*  @brief
*    Copy operator
*/
XmlDeclaration &XmlDeclaration::operator =(const XmlDeclaration &cSource)
{
	// Copy the data
	m_sVersion    = cSource.m_sVersion;
	m_sEncoding   = cSource.m_sEncoding;
	m_sStandalone = cSource.m_sStandalone;
	return *this;
}

/**
*  @brief
*    Version - will return an empty string if none was found
*/
String XmlDeclaration::GetVersion() const
{
	return m_sVersion;
}

/**
*  @brief
*    Encoding - will return an empty string if none was found
*/
String XmlDeclaration::GetEncoding() const
{
	return m_sEncoding;
}

/**
*  @brief
*    Standalone - will return an empty string if none was found
*/
String XmlDeclaration::GetStandalone() const
{
	return m_sStandalone;
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlDeclaration::Save(File &cFile, uint32 nDepth)
{
	cFile.Print("<?xml ");

	if (m_sVersion.GetLength())
		cFile.Print("version=\"" + m_sVersion + "\" ");
	if (m_sEncoding.GetLength())
		cFile.Print("encoding=\"" + m_sEncoding + "\" ");
	if (m_sStandalone.GetLength())
		cFile.Print("standalone=\"" + m_sStandalone + "\" ");
	cFile.Print("?>");

	// Done
	return true;
}

String XmlDeclaration::ToString(uint32 nDepth) const
{
	String sXml = "<?xml ";

	if (m_sVersion.GetLength())
		sXml += "version=\"" + m_sVersion + "\" ";
	if (m_sEncoding.GetLength())
		sXml += "encoding=\"" + m_sEncoding + "\" ";
	if (m_sStandalone.GetLength())
		sXml += "standalone=\"" + m_sStandalone + "\" ";
	sXml += "?>";

	// Done
	return sXml;
}

const char *XmlDeclaration::Parse(const char *pszData, XmlParsingData *pData, EEncoding nEncoding)
{
	pszData = SkipWhiteSpace(pszData, nEncoding);

	// Find the beginning, find the end, and look for the stuff in-between
	if (!pszData || !*pszData || !StringEqual(pszData, "<?xml", true, nEncoding)) {
		// Set error code
		XmlDocument *pDocument = GetDocument();
		if (pDocument)
			pDocument->SetError(ErrorParsingDeclaration, 0, 0, nEncoding);

		// Error!
		return nullptr;
	}
	if (pData) {
		pData->Stamp(pszData, nEncoding);
		m_cCursor = pData->Cursor();
	}
	pszData += 5;

	m_sVersion    = "";
	m_sEncoding   = "";
	m_sStandalone = "";

	while (pszData && *pszData) {
		if (*pszData == '>') {
			++pszData;

			// Done
			return pszData;
		}

		pszData = SkipWhiteSpace(pszData, nEncoding);

		// "version"
		if (StringEqual(pszData, "version", true, nEncoding)) {
			XmlAttribute attrib;
			pszData = attrib.Parse(pszData, pData, nEncoding);
			m_sVersion = attrib.GetValue();

		// "nEncoding"
		} else if (StringEqual(pszData, "nEncoding", true, nEncoding)) {
			XmlAttribute attrib;
			pszData = attrib.Parse(pszData, pData, nEncoding);
			m_sEncoding = attrib.GetValue();

		// "standalone"
		} else if (StringEqual(pszData, "standalone", true, nEncoding)) {
			XmlAttribute attrib;
			pszData = attrib.Parse(pszData, pData, nEncoding);
			m_sStandalone = attrib.GetValue();

		} else {
			// Read over whatever it is
			while(pszData && *pszData && *pszData != '>' && !IsWhiteSpace(*pszData))
				++pszData;
		}
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public virtual XmlNode functions                      ]
//[-------------------------------------------------------]
XmlNode *XmlDeclaration::Clone() const
{
	return new XmlDeclaration(*this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
