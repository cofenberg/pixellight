/*********************************************************\
 *  File: XmlDocument.cpp                                *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <tinyxml.h>
#include "PLGeneral/File/File.h"
#include "PLGeneral/Xml/XmlDocument.h"


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
XmlDocument::XmlDocument() :
	XmlNode(new TiXmlDocument())
{
}

/**
*  @brief
*    Constructor
*/
XmlDocument::XmlDocument(const String &sName) :
	XmlNode(new TiXmlDocument(sName))
{
}

/**
*  @brief
*    Copy constructor
*/
XmlDocument::XmlDocument(const XmlDocument &cSource) :
	XmlNode(new TiXmlDocument(*(TiXmlDocument*)cSource.m_pData))
{
}

/**
*  @brief
*    Destructor
*/
XmlDocument::~XmlDocument()
{
}

/**
*  @brief
*    Copy operator
*/
XmlDocument &XmlDocument::operator =(const XmlDocument &cSource)
{
	*((TiXmlDocument*)m_pData) = (const TiXmlDocument&)*((TiXmlDocument*)cSource.m_pData);
	return *this;
}

/**
*  @brief
*    Load a file using the current document value
*/
bool XmlDocument::Load(EEncoding nEncoding)
{
	return Load(GetValue(), nEncoding);
}

/**
*  @brief
*    Load a file using the given filename
*/
bool XmlDocument::Load(const String &sFilename, EEncoding nEncoding)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Set document value
		SetValue(sFilename);

		// Open file in binary mode so that TinyXML can normalize the end of lines (EOL)
		File cFile(sFilename);
		if (cFile.Exists() && cFile.Open(File::FileRead)) {
			return Load(cFile);
		} else {
			((TiXmlDocument*)m_pData)->SetError(TiXmlBase::TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN);
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Loads from a given file
*/
bool XmlDocument::Load(File &cFile, EEncoding nEncoding)
{
	// Set document value
	SetValue(cFile.GetUrl().GetNativePath());

	// Get data
	uint32 nFileSize = cFile.GetSize();
	if (nFileSize) {
		char *pszData = new char[nFileSize+1];
		cFile.Read(pszData, 1, nFileSize);
		pszData[nFileSize] = '\0';

		// Parse data
		Parse(pszData, NULL, nEncoding);

		// Cleanup the data
		delete [] pszData;

		// Done
		return !Error();
	} else {
		// Done
		return true;
	}
}

/**
*  @brief
*    Save a file using the current document value
*/
bool XmlDocument::Save()
{
	return Save(GetValue());
}

/**
*  @brief
*    Save a file using the given filename
*/
bool XmlDocument::Save(const String &sFilename)
{
	// Open the file
	File cFile(sFilename);
	if (cFile.Open(File::FileWrite | File::FileCreate)) {
		// Set document value
		SetValue(sFilename);

		// Save
		Save(cFile);

		// Done
		return true;
	} else {
		// Error!
		((TiXmlDocument*)m_pData)->SetError(TiXmlBase::TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN);
		return false;
	}
}

/**
*  @brief
*    Parse the given null terminated block of XML data
*/
const char *XmlDocument::Parse(const char *pszData, XmlParsingData *pData, EEncoding nEncoding)
{
	return ((TiXmlDocument*)m_pData)->Parse(pszData, (TiXmlParsingData*)pData, (TiXmlEncoding)nEncoding);
}

/**
*  @brief
*    Get the root element -- the only top level element -- of the document
*/
XmlElement *XmlDocument::GetRootElement()
{
	return (XmlElement*)GetPLNode(((TiXmlDocument*)m_pData)->RootElement());
}

const XmlElement *XmlDocument::GetRootElement() const
{
	return (const XmlElement*)((XmlDocument*)this)->GetPLNode(((TiXmlDocument*)m_pData)->RootElement());
}

/**
*  @brief
*    If an error occurs, error will be set to true
*/
bool XmlDocument::Error() const
{
	return ((TiXmlDocument*)m_pData)->Error();
}

/**
*  @brief
*    Contains a textual (english) description of the error if one occurs
*/
String XmlDocument::GetErrorDesc(bool bLocation) const
{
	if (bLocation) {
		String sString = ((TiXmlDocument*)m_pData)->ErrorDesc();
		if (GetErrorRow() > 0)
			sString += String::Format(" Row: %d", GetErrorRow());
		if (GetErrorColumn() > 0)
			sString += String::Format(" Column: %d", GetErrorColumn());
		return sString;
	} else {
		return ((TiXmlDocument*)m_pData)->ErrorDesc();
	}
}

/**
*  @brief
*    Generally, you probably want the error string ('GetErrorDesc()') - but if you
*    prefer the error ID, this function will fetch it
*/
int XmlDocument::GetErrorID() const
{
	return ((TiXmlDocument*)m_pData)->ErrorId();
}

/**
*  @brief
*    Returns the location (if known) of the error
*/
int XmlDocument::GetErrorRow() const
{
	return ((TiXmlDocument*)m_pData)->ErrorRow();
}

/**
*  @brief
*    The column where the error occured
*/
int XmlDocument::GetErrorColumn() const
{
	return ((TiXmlDocument*)m_pData)->ErrorCol();
}

/**
*  @brief
*    Returns the tab size
*/
uint32 XmlDocument::GetTabSize() const
{
	return ((TiXmlDocument*)m_pData)->TabSize();
}

/**
*  @brief
*    Sets the tab size
*/
void XmlDocument::SetTabSize(uint32 nTabSize)
{
	((TiXmlDocument*)m_pData)->SetTabSize(nTabSize);
}

/**
*  @brief
*    If you have handled the error, it can be reset with this call
*/
void XmlDocument::ClearError()
{
	((TiXmlDocument*)m_pData)->ClearError();
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlDocument::Save(File &cFile, uint32 nDepth)
{
	for (XmlNode *pNode=GetFirstChild(); pNode; pNode=pNode->GetNextSibling()) {
		pNode->Save(cFile, nDepth);
		cFile.PutC('\n');
	}

	// Done
	return true;
}

String XmlDocument::ToString(uint32 nDepth)
{
	String sXml;
	for (XmlNode *pNode=GetFirstChild(); pNode; pNode=pNode->GetNextSibling()) {
		sXml += pNode->ToString(nDepth);
	}
	return sXml;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlDocument::XmlDocument(void *pNode, int nDummy) :
	XmlNode(pNode)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
