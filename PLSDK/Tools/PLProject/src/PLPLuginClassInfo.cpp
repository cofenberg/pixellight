/*********************************************************\
 *  File: PLPluginInfo.cpp                               *
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
#include "PLPLuginClassInfo.h"
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/Xml/XmlElement.h>
#include <PLGeneral/Xml/XmlText.h>
#include <PLGeneral/Xml/XmlDocument.h>
#include <PLGeneral/String/RegEx.h>
#include <PLGeneral/Container/ConstIterator.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PLPLuginClassInfo::PLPLuginClassInfo()
{

}

/**
*  @brief
*    Destructor
*/
PLPLuginClassInfo::~PLPLuginClassInfo()
{

}

/**
*  @brief
*    Appends the parsed information to the given xml element
*/
void PLPLuginClassInfo::Save(PLGeneral::XmlElement &pParent)
{
	XmlElement *pClassElement = new XmlElement("Class");
	pClassElement->SetAttribute("Name", m_sClassName);
	pClassElement->SetAttribute("Namespace", m_sNamespace);
	pClassElement->SetAttribute("BaseClassName", m_sBaseClass);
	pClassElement->SetAttribute("Description", m_sDescription);
	pClassElement->SetAttribute("HasConstructor", m_bHasConstructor ? 1 : 0);
	pClassElement->SetAttribute("HasDefaultConstructor", m_bHasDefaultConstructor ? 1 : 0);

	pParent.LinkEndChild(*pClassElement);

	// Properties
	if (m_mapProperties.IsEmpty())
		return;

	ConstIterator<String> iter = m_mapProperties.GetConstKeyIterator();

	XmlElement *pPropertiesElement = new XmlElement("Properties");
	pClassElement->LinkEndChild(*pPropertiesElement);

	while (iter.HasNext()) {
		const String &sKey = iter.Next();
		const String &sValue = m_mapProperties.Get(sKey);

		XmlElement *pElement = new XmlElement("Property");
		pElement->SetAttribute("Name", sKey);

		XmlText *pTextElement = new XmlText(sValue);

		pElement->LinkEndChild(*pTextElement);
		pPropertiesElement->LinkEndChild(*pElement);
	}
}

/**
*  @brief
*    Parse the given pl_class pl_class_end block
*/
void PLPLuginClassInfo::ParsePlClassBlock(const PLGeneral::String &sPLClassBlock)
{
	m_sClassName = "";
	m_sBaseClass = "";
	m_sDescription = "";
	m_sNamespace = "";
	m_bHasConstructor = false;
	m_bHasDefaultConstructor = false;
	m_mapProperties.Clear();

	{
		RegEx cplclassBlock("^\\s*pl_class\\s*\\((?<RTTIEXP>\\w*)\\s*,\\s*(?<name>\\w*)\\s*,\\s*\\\"(?<namespace>\\w*)\\\"\\s*,\\s*(?<baseclass>\\w*\\:\\:\\w*)\\s*,\\s*\\\"(?<description>.*)\\\"\\)", RegEx::Multiline);

		if (cplclassBlock.Match(sPLClassBlock)) {
			m_sClassName = cplclassBlock.GetNameResult("name");
			m_sNamespace = cplclassBlock.GetNameResult("namespace");
			m_sBaseClass = cplclassBlock.GetNameResult("baseclass");
			m_sDescription = cplclassBlock.GetNameResult("description");
		}
	}

	{
		RegEx cplconstructorBlock("^\\s*(pl_constructor_\\d\\d?)", RegEx::Multiline);
		RegEx cpldefaultconstructorBlock("^\\s*(pl_constructor_0)", RegEx::Multiline);

		m_bHasConstructor = cplconstructorBlock.Match(sPLClassBlock);
		if (m_bHasConstructor)
			m_bHasDefaultConstructor = cpldefaultconstructorBlock.Match(sPLClassBlock);
	}

	{
		RegEx cplpropertiesBlock("^\\s*(pl_properties.*pl_properties_end)", RegEx::Multiline | RegEx::DotAll);

		if (cplpropertiesBlock.Match(sPLClassBlock)) {
			String content = cplpropertiesBlock.GetResult(0);

			Tokenizer cTokenizer;

			cTokenizer.SetDelimiters("\r\n");
			cTokenizer.SetSingleChars("");
			cTokenizer.SetQuotes("");
			cTokenizer.Start(content);

			RegEx cplpropertyBlock("^\\s*(pl_property\\(\\\"(?<name>\\w*)\\\"\\s*,\\s*\\\"(?<value>.*)\\\"\\s*\\))", RegEx::Multiline);

			String sToken = cTokenizer.GetNextToken();
			while (sToken.GetLength() != 0) {
				if (cplpropertyBlock.Match(sToken)) {
					String sPropName = cplpropertyBlock.GetNameResult("name");
					String sPropValue = cplpropertyBlock.GetNameResult("value");
					m_mapProperties.Add(sPropName, sPropValue);
				}
				sToken = cTokenizer.GetNextToken();
			}
		}
	}
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    copy constructor
*/
PLPLuginClassInfo::PLPLuginClassInfo(const PLPLuginClassInfo& other)
{

}

/**
*  @brief
*    assignment operator
*/
PLPLuginClassInfo& PLPLuginClassInfo::operator=(const PLPLuginClassInfo & other)
{
	return *this;
}

