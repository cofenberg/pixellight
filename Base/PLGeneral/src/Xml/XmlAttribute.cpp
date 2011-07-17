/*********************************************************\
 *  File: XmlAttribute.cpp                               *
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
#include <stdio.h>
#include "PLGeneral/File/File.h"
#include "PLGeneral/Xml/XmlParsingData.h"
#include "PLGeneral/Xml/XmlDocument.h"
#include "PLGeneral/Xml/XmlAttribute.h"


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
XmlAttribute::XmlAttribute() :
	m_pDocument(nullptr),
	m_pPreviousAttribute(nullptr),
	m_pNextAttribute(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
XmlAttribute::~XmlAttribute()
{
}

/**
*  @brief
*    Return the name of this attribute
*/
String XmlAttribute::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set the name of this attribute
*/
void XmlAttribute::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Return the value of this attribute
*/
String XmlAttribute::GetValue() const
{
	return m_sValue;
}

/**
*  @brief
*    Return the value of this attribute, converted to an integer
*/
int XmlAttribute::GetIntValue() const
{
	return m_sValue.GetInt();
}

/**
*  @brief
*    Return the value of this attribute, converted to a double
*/
double XmlAttribute::GetDoubleValue() const
{
	return m_sValue.GetDouble();
}

/**
*  @brief
*    Examines the value string
*/
XmlBase::EQueryResult XmlAttribute::QueryIntValue(int &nValue) const
{
	int nBackup = nValue;
	EQueryResult nResult = (sscanf(m_sValue.GetASCII(), "%d", &nValue) == 1) ? Success : WrongType;
	if (nResult != Success)
		nValue = nBackup;
	return nResult;
}

/**
*  @brief
*    Examines the value string
*/
XmlBase::EQueryResult XmlAttribute::QueryDoubleValue(double &dValue) const
{
	double dBackup = dValue;
	EQueryResult nResult = (sscanf(m_sValue.GetASCII(), "%lf", &dValue) == 1) ? Success : WrongType;
	if (nResult != Success)
		dValue = dBackup;
	return nResult;
}

/**
*  @brief
*    Set the value
*/
void XmlAttribute::SetValue(const String &sValue)
{
	m_sValue = sValue;
}

/**
*  @brief
*    Set the value from an integer
*/
void XmlAttribute::SetIntValue(int nValue)
{
	m_sValue = nValue;
}

/**
*  @brief
*    Set the value from a double
*/
void XmlAttribute::SetDoubleValue(double dValue)
{
	m_sValue = dValue;
}

/**
*  @brief
*    Get the next sibling attribute in the DOM
*/
XmlAttribute *XmlAttribute::GetNext()
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pNextAttribute->m_sValue.GetLength() && !m_pNextAttribute->m_sName.GetLength()) ? nullptr : m_pNextAttribute;
}

const XmlAttribute *XmlAttribute::GetNext() const
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pNextAttribute->m_sValue.GetLength() && !m_pNextAttribute->m_sName.GetLength()) ? nullptr : m_pNextAttribute;
}

/**
*  @brief
*    Get the previous sibling attribute in the DOM
*/
XmlAttribute *XmlAttribute::GetPrevious()
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pPreviousAttribute->m_sValue.GetLength() && !m_pPreviousAttribute->m_sName.GetLength()) ? nullptr : m_pPreviousAttribute;
}

const XmlAttribute *XmlAttribute::GetPrevious() const
{
	// We are using knowledge of the sentinel. The sentinel have a value or name.
	return (!m_pPreviousAttribute->m_sValue.GetLength() && !m_pPreviousAttribute->m_sName.GetLength()) ? nullptr : m_pPreviousAttribute;
}

bool XmlAttribute::operator ==(const XmlAttribute &cOther) const
{
	return (cOther.m_sName == m_sName);
}

bool XmlAttribute::operator <(const XmlAttribute &cOther) const
{
	return (m_sName < cOther.m_sName);
}

bool XmlAttribute::operator >(const XmlAttribute &cOther) const
{
	return (m_sName > cOther.m_sName);
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlAttribute::Save(File &cFile, uint32 nDepth)
{
	String sName, sValue;

	EncodeString(m_sName,  sName);
	EncodeString(m_sValue, sValue);

	if (sValue.IsSubstring('\"'))
		cFile.Print(sName + "='" + sValue + '\'');
	else
		cFile.Print(sName + "=\"" + sValue + '\"');

	// Done
	return true;
}

String XmlAttribute::ToString(uint32 nDepth) const
{
	String sName, sValue;

	EncodeString(m_sName,  sName);
	EncodeString(m_sValue, sValue);

	if (sValue.IsSubstring('\"'))
		return sName + "='" + sValue + '\'';
	else
		return sName + "=\"" + sValue + '\"';
}

const char *XmlAttribute::Parse(const char *pszData, XmlParsingData *pData, EEncoding nEncoding)
{
	pszData = SkipWhiteSpace(pszData, nEncoding);
	if (!pszData || !*pszData)
		return nullptr; // Error!

	if (pData) {
		pData->Stamp(pszData, nEncoding);
		m_cCursor = pData->Cursor();
	}

	// Read the name, the '=' and the value
	const char *pszError = pszData;
	pszData = ReadName(pszData, m_sName, nEncoding);
	if (!pszData || !*pszData) {
		// Set error code
		if (m_pDocument)
			m_pDocument->SetError(ErrorReadingAttributes, pszError, pData, nEncoding);

		// Error!
		return nullptr;
	}
	pszData = SkipWhiteSpace(pszData, nEncoding);
	if (!pszData || !*pszData || *pszData != '=') {
		// Set error code
		if (m_pDocument)
			m_pDocument->SetError(ErrorReadingAttributes, pszData, pData, nEncoding);

		// Error!
		return nullptr;
	}

	++pszData;	// skip '='
	pszData = SkipWhiteSpace(pszData, nEncoding);
	if (!pszData || !*pszData) {
		// Set error code
		if (m_pDocument)
			m_pDocument->SetError(ErrorReadingAttributes, pszData, pData, nEncoding);

		// Error!
		return nullptr;
	}

	// Constants
	const char szSingleQuote = '\'';
	const char szDoubleQuote = '\"';

	if (*pszData == szSingleQuote) {
		++pszData;
		const char *pszEnd = "\'";		// Single quote in string
		pszData = ReadText(pszData, m_sValue, false, pszEnd, false, nEncoding);
	} else if (*pszData == szDoubleQuote) {
		++pszData;
		const char *pszEnd = "\"";		// Double quote in string
		pszData = ReadText(pszData, m_sValue, false, pszEnd, false, nEncoding);
	} else {
		// All attribute values should be in single or double quotes.
		// But this is such a common error that the parser will try
		// its best, even without them.
		m_sValue = "";
		while (    pszData && *pszData										// Existence
				&& !IsWhiteSpace( *pszData )								// Whitespace
				&& *pszData != '/' && *pszData != '>' ) {					// Tag end
			if (*pszData == szSingleQuote || *pszData == szDoubleQuote) {
				// We did not have an opening quote but seem to have a closing one. Give up and throw an error.

				// Set error code
				if (m_pDocument)
					m_pDocument->SetError(ErrorReadingAttributes, pszData, pData, nEncoding);

				// Error!
				return nullptr;
			}
			m_sValue += *pszData;
			++pszData;
		}
	}

	// Done
	return pszData;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
XmlAttribute::XmlAttribute(const XmlAttribute &cSource) :
	m_pDocument(nullptr),
	m_pPreviousAttribute(nullptr),
	m_pNextAttribute(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
XmlAttribute &XmlAttribute::operator =(const XmlAttribute &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
