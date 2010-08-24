/*********************************************************\
 *  File: XmlAttribute.cpp                               *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
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
	return ((TiXmlAttribute*)m_pData)->Name();
}

/**
*  @brief
*    Set the name of this attribute
*/
void XmlAttribute::SetName(const String &sName)
{
	((TiXmlAttribute*)m_pData)->SetName(sName);
}

/**
*  @brief
*    Return the value of this attribute
*/
String XmlAttribute::GetValue() const
{
	return ((TiXmlAttribute*)m_pData)->Value();
}

/**
*  @brief
*    Return the value of this attribute, converted to an integer
*/
int XmlAttribute::GetIntValue() const
{
	return ((TiXmlAttribute*)m_pData)->IntValue();
}

/**
*  @brief
*    Return the value of this attribute, converted to a double
*/
double XmlAttribute::GetDoubleValue() const
{
	return ((TiXmlAttribute*)m_pData)->DoubleValue();
}

/**
*  @brief
*    Examines the value string
*/
XmlBase::EQueryResult XmlAttribute::QueryIntValue(int &nValue) const
{
	int nBackup = nValue;
	EQueryResult nResult = (EQueryResult)((TiXmlAttribute*)m_pData)->QueryIntValue(&nValue);
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
	EQueryResult nResult = (EQueryResult)((TiXmlAttribute*)m_pData)->QueryDoubleValue(&dValue);
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
	((TiXmlAttribute*)m_pData)->SetValue(sValue);
}

/**
*  @brief
*    Set the value from an integer
*/
void XmlAttribute::SetIntValue(int nValue)
{
	((TiXmlAttribute*)m_pData)->SetIntValue(nValue);
}

/**
*  @brief
*    Set the value from a double
*/
void XmlAttribute::SetDoubleValue(double dValue)
{
	((TiXmlAttribute*)m_pData)->SetDoubleValue(dValue);
}

/**
*  @brief
*    Get the next sibling attribute in the DOM
*/
XmlAttribute *XmlAttribute::GetNext()
{
	return GetPLAttribute(((TiXmlAttribute*)m_pData)->Next());
}

const XmlAttribute *XmlAttribute::GetNext() const
{
	return (const XmlAttribute*)GetPLAttribute(((TiXmlAttribute*)m_pData)->Next());
}

/**
*  @brief
*    Get the previous sibling attribute in the DOM
*/
XmlAttribute *XmlAttribute::GetPrevious()
{
	return GetPLAttribute(((TiXmlAttribute*)m_pData)->Previous());
}

const XmlAttribute *XmlAttribute::GetPrevious() const
{
	return (const XmlAttribute*)GetPLAttribute(((TiXmlAttribute*)m_pData)->Previous());
}

bool XmlAttribute::operator ==(const XmlAttribute &cOther) const
{
	return (*((TiXmlAttribute*)m_pData) == (const TiXmlAttribute&)*((TiXmlAttribute*)cOther.m_pData));
}

bool XmlAttribute::operator <(const XmlAttribute &cOther) const
{
	return (*((TiXmlAttribute*)m_pData) < (const TiXmlAttribute&)*((TiXmlAttribute*)cOther.m_pData));
}

bool XmlAttribute::operator >(const XmlAttribute &cOther) const
{
	return (*((TiXmlAttribute*)m_pData) > (const TiXmlAttribute&)*((TiXmlAttribute*)cOther.m_pData));
}


//[-------------------------------------------------------]
//[ Public virtual XmlBase functions                      ]
//[-------------------------------------------------------]
bool XmlAttribute::Save(File &cFile, uint32 nDepth)
{
	TIXML_STRING sName, sValue;

	TiXmlBase::EncodeString(((TiXmlAttribute*)m_pData)->NameTStr(),  &sName);
	TiXmlBase::EncodeString(((TiXmlAttribute*)m_pData)->ValueTStr(), &sValue);

	if (sValue.find('\"') == TIXML_STRING::npos)
		cFile.Print(String::Format("%s=\"%s\"", sName.c_str(), sValue.c_str()));
	else
		cFile.Print(String::Format("%s='%s'", sName.c_str(), sValue.c_str()));

	// Done
	return true;
}

String XmlAttribute::ToString(uint32 nDepth)
{
	TIXML_STRING sName, sValue;

	TiXmlBase::EncodeString(((TiXmlAttribute*)m_pData)->NameTStr(),  &sName);
	TiXmlBase::EncodeString(((TiXmlAttribute*)m_pData)->ValueTStr(), &sValue);

	if (sValue.find('\"') == TIXML_STRING::npos)
		return String::Format("%s=\"%s\"", sName.c_str(), sValue.c_str());
	else
		return String::Format("%s='%s'", sName.c_str(), sValue.c_str());
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlAttribute::XmlAttribute(void *pNode) :
	XmlBase(pNode)
{
}

/**
*  @brief
*    Copy constructor
*/
XmlAttribute::XmlAttribute(const XmlAttribute &cSource) :
	XmlBase(NULL)
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
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns/creates the PL XML attribute
*/
XmlAttribute *XmlAttribute::GetPLAttribute(void *pNode)
{
	// Check parameter
	if (!pNode)
		return NULL;

	// Check wether this TinyXML attribute has already a PL XML attribute, if there's no
	// PL XML attribute, create one
	TiXmlAttribute *pTinyXMLAttribute = (TiXmlAttribute*)pNode;
	if (pTinyXMLAttribute->GetUserData())
		return (XmlAttribute*)pTinyXMLAttribute->GetUserData();
	else
		return new XmlAttribute(pTinyXMLAttribute);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
