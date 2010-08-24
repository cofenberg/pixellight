/*********************************************************\
 *  File: ParamsParserXml.cpp                            *
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
#include <PLGeneral/Xml/Xml.h>
#include "PLCore/Base/Tools/ParamsParserXml.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ParamsParserXml::ParamsParserXml() :
	m_pElement(NULL)
{
}

/**
*  @brief
*    Destructor
*/
ParamsParserXml::~ParamsParserXml()
{
}

/**
*  @brief
*    Parse parameters from XML
*/
bool ParamsParserXml::ParseXml(const XmlElement &cElement)
{
	// Save pointer to XML element
	m_pElement = &cElement;
	if (m_pElement) {
		// Get first attribute
		m_pAttribute = m_pElement->GetFirstAttribute();
		if (m_pAttribute) {
			m_sName  = m_pAttribute->GetName();
			m_sValue = m_pAttribute->GetValue();
			return true;
		}
	}

	// Parameters are empty
	return false;
}

/**
*  @brief
*    Parse next parameter
*/
bool ParamsParserXml::Next()
{
	// Is attribute valid?
	if (m_pAttribute) {
		// Get the next attribute
		m_pAttribute = m_pAttribute->GetNext();
		if (m_pAttribute) {
			// Get name and value
			m_sName  = m_pAttribute->GetName();
			m_sValue = m_pAttribute->GetValue();
			return true;
		}
	}

	// Error, could not parse next expression
	m_pAttribute = NULL;
	m_sName		 = "";
	m_sValue	 = "";
	return false;
}

/**
*  @brief
*    Check if the current (last parsed) parameter is valid
*/
bool ParamsParserXml::HasParam() const
{
	return (m_sName != "");
}

/**
*  @brief
*    Get name of currently parsed parameter
*/
String ParamsParserXml::GetName() const
{
	// Return parameter name
	return m_sName;
}

/**
*  @brief
*    Get value of currently parsed parameter
*/
String ParamsParserXml::GetValue() const
{
	// Return parameter value
	return m_sValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
