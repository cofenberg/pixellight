/*********************************************************\
 *  File: XmlElement.cpp                                 *
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
#include "PLGeneral/Xml/XmlAttribute.h"
#include "PLGeneral/Xml/XmlDocument.h"
#include "PLGeneral/Xml/XmlElement.h"


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
XmlElement::XmlElement(const String &sValue) :
	XmlNode(new TiXmlElement(sValue))
{
}

/**
*  @brief
*    Copy constructor
*/
XmlElement::XmlElement(const XmlElement &cSource) :
	XmlNode(new TiXmlElement(*(TiXmlElement*)cSource.m_pData))
{
}

/**
*  @brief
*    Destructor
*/
XmlElement::~XmlElement()
{
}

/**
*  @brief
*    Copy operator
*/
XmlElement &XmlElement::operator =(const XmlElement &cSource)
{
	*((TiXmlElement*)m_pData) = (const TiXmlElement&)*((TiXmlElement*)cSource.m_pData);
	return *this;
}

/**
*  @brief
*    Given an attribute name, 'GetAttribute()' returns the value
*    for the attribute of that name, or NULL if none exists
*/
String XmlElement::GetAttribute(const String &sName) const
{
	return ((TiXmlElement*)m_pData)->Attribute(sName);
}

/**
*  @brief
*    Given an attribute name, 'GetAttribute()' returns the value
*    for the attribute of that name, or NULL if none exists
*/
String XmlElement::GetAttribute(const String &sName, int *pnValue) const
{
	if (pnValue) {
		int nBackup = *pnValue;
		const char *pszResult = ((TiXmlElement*)m_pData)->Attribute(sName, pnValue);
		if (!pszResult)
			*pnValue = nBackup;
		return pszResult;
	} else {
		return ((TiXmlElement*)m_pData)->Attribute(sName, (int*)NULL);
	}
}

/**
*  @brief
*    Given an attribute name, 'GetAttribute()' returns the value
*    for the attribute of that name, or NULL if none exists
*/
String XmlElement::GetAttribute(const String &sName, double *pdValue) const
{
	if (pdValue) {
		double dBackup = *pdValue;
		const char *pszResult = ((TiXmlElement*)m_pData)->Attribute(sName, pdValue);
		if (!pszResult)
			*pdValue = dBackup;
		return pszResult;
	} else {
		return ((TiXmlElement*)m_pData)->Attribute(sName, (double*)NULL);
	}
}

/**
*  @brief
*    Examines the attribute
*/
XmlBase::EQueryResult XmlElement::QueryIntAttribute(const String &sName, int *pnValue) const
{
	if (pnValue) {
		int nBackup = *pnValue;
		EQueryResult nResult = (EQueryResult)((TiXmlElement*)m_pData)->QueryIntAttribute(sName, pnValue);
		if (nResult != Success)
			*pnValue = nBackup;
		return nResult;
	} else {
		return (EQueryResult)((TiXmlElement*)m_pData)->QueryIntAttribute(sName, NULL);
	}
}

/**
*  @brief
*    Examines the attribute
*/
XmlBase::EQueryResult XmlElement::QueryFloatAttribute(const String &sName, float *pfValue) const
{
	if (pfValue) {
		float fBackup = *pfValue;
		EQueryResult nResult = (EQueryResult)((TiXmlElement*)m_pData)->QueryFloatAttribute(sName, pfValue);
		if (nResult != Success)
			*pfValue = fBackup;
		return nResult;
	} else {
		return (EQueryResult)((TiXmlElement*)m_pData)->QueryFloatAttribute(sName, NULL);
	}
}

/**
*  @brief
*    Examines the attribute
*/
XmlBase::EQueryResult XmlElement::QueryDoubleAttribute(const String &sName, double *pdValue) const
{
	if (pdValue) {
		double dBackup = *pdValue;
		EQueryResult nResult = (EQueryResult)((TiXmlElement*)m_pData)->QueryDoubleAttribute(sName, pdValue);
		if (nResult != Success)
			*pdValue = dBackup;
		return nResult;
	} else {
		return (EQueryResult)((TiXmlElement*)m_pData)->QueryDoubleAttribute(sName, NULL);
	}
}

/**
*  @brief
*    Sets an attribute of name to a given value
*/
void XmlElement::SetAttribute(const String &sName, const String &sValue)
{
	((TiXmlElement*)m_pData)->SetAttribute(sName, sValue);
}

/**
*  @brief
*    Sets an attribute of name to a given value
*/
void XmlElement::SetAttribute(const String &sName, int nValue)
{
	((TiXmlElement*)m_pData)->SetAttribute(sName, nValue);
}

/**
*  @brief
*    Sets an attribute of name to a given value
*/
void XmlElement::SetDoubleAttribute(const String &sName, double dValue)
{
	((TiXmlElement*)m_pData)->SetDoubleAttribute(sName, dValue);
}

/**
*  @brief
*    Deletes an attribute with the given name
*/
void XmlElement::RemoveAttribute(const String &sName)
{
	((TiXmlElement*)m_pData)->RemoveAttribute(sName);
}

/**
*  @brief
*    Access the first attribute in this element
*/
XmlAttribute *XmlElement::GetFirstAttribute()
{
	return XmlAttribute::GetPLAttribute(((TiXmlElement*)m_pData)->FirstAttribute());
}

const XmlAttribute *XmlElement::GetFirstAttribute() const
{
	return (const XmlAttribute*)XmlAttribute::GetPLAttribute(((TiXmlElement*)m_pData)->FirstAttribute());
}

/**
*  @brief
*    Access the last attribute in this element
*/
XmlAttribute *XmlElement::GetLastAttribute()
{
	return XmlAttribute::GetPLAttribute(((TiXmlElement*)m_pData)->LastAttribute());
}

const XmlAttribute *XmlElement::GetLastAttribute() const
{
	return (const XmlAttribute*)XmlAttribute::GetPLAttribute(((TiXmlElement*)m_pData)->LastAttribute());
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlElement::Save(File &cFile, uint32 nDepth)
{
	/// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	for (uint32 i=0; i<nNumOfSpaces; i++)
		cFile.PutC(' ');

	// Print value
	cFile.Print('<' + GetValue());

	// Print attributes
	for (XmlAttribute *pAttribute=GetFirstAttribute(); pAttribute; pAttribute=pAttribute->GetNext()) {
		cFile.PutC(' ');
		pAttribute->Save(cFile, nDepth);
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	if (!GetFirstChild())
		cFile.Print(" />");
	else if (GetFirstChild() == GetLastChild() && GetFirstChild()->GetType() == Text) {
		cFile.PutC('>');
		GetFirstChild()->Save(cFile, nDepth+1);
		cFile.Print("</" + GetValue() + '>');
	} else {
		cFile.PutC('>');

		for (XmlNode *pNode=GetFirstChild(); pNode; pNode=pNode->GetNextSibling()) {
			if (pNode->GetType() != Text)
				cFile.PutC('\n');
			pNode->Save(cFile, nDepth+1);
		}
		cFile.PutC('\n');

		// Print empty spaces
		for (uint32 i=0; i<nNumOfSpaces; i++)
			cFile.PutC(' ');

		// Print value
		cFile.Print("</" + GetValue() + '>');
	}

	// Done
	return true;
}

String XmlElement::ToString(uint32 nDepth)
{
	// Get the number of empty spaces
	const XmlDocument *pDocument = GetDocument();
	uint32 nNumOfSpaces = (pDocument ? pDocument->GetTabSize() : 4) * nDepth;

	// Print empty spaces
	String sXml;
	for (uint32 i=0; i<nNumOfSpaces; i++)
		sXml += ' ';

	// Print value
	sXml += '<' + GetValue();

	// Print attributes
	for (XmlAttribute *pAttribute=GetFirstAttribute(); pAttribute; pAttribute=pAttribute->GetNext()) {
		sXml += ' ' + pAttribute->ToString(nDepth);
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	if (!GetFirstChild())
		sXml += " />";
	else if (GetFirstChild() == GetLastChild() && GetFirstChild()->GetType() == Text) {
		sXml += '>' + GetFirstChild()->ToString(nDepth+1) + "</" + GetValue() + '>';
	} else {
		sXml += '>';

		for (XmlNode *pNode=GetFirstChild(); pNode; pNode=pNode->GetNextSibling()) {
			if (pNode->GetType() != Text)
				sXml += '\n';
			sXml += pNode->ToString(nDepth+1);
		}
		sXml += '\n';

		// Print empty spaces
		for (uint32 i=0; i<nNumOfSpaces; i++)
			sXml += ' ';

		// Print value
		sXml += "</" + GetValue() + '>';
	}

	// Done
	return sXml;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlElement::XmlElement(void *pNode, int nDummy) :
	XmlNode(pNode)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
