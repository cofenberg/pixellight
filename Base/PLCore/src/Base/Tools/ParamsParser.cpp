/*********************************************************\
 *  File: ParamsParser.cpp                               *
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
#include "PLCore/Base/Tools/ParamsParser.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ParamsParser::ParamsParser() :
	m_cRegEx("\\s*((\\w*\\s*=\\s*\"[^\"]*\")|(\\w*\\s*=\\s*'[^']*')|(\\w*\\s*=\\s*\\w*))"),
	m_nParsePos(-1)
{
}

/**
*  @brief
*    Destructor
*/
ParamsParser::~ParamsParser()
{
}

/**
*  @brief
*    Parse parameter string
*/
bool ParamsParser::ParseString(const String &sParameters)
{
	// Save parameter string
	m_sParameters = sParameters;
	if (sParameters.GetLength()) {
		// Get first expression
		m_nParsePos = 0;
		return Next();
	}

	// Parameter string is empty
	return false;
}

/**
*  @brief
*    Parse next parameter
*/
bool ParamsParser::Next()
{
	// Parse next expression
	if (m_nParsePos > -1 && m_cRegEx.Match(m_sParameters, m_nParsePos)) {
		// Get expression and new parse position
		m_nParsePos			= m_cRegEx.GetPosition();
		String sExpression	= m_cRegEx.GetResult(0);

		// Process the found expression
		if (sExpression[sExpression.GetLength()-1] == '\'') {
			static RegEx cRegEx("\\s*(\\w*)\\s*=\\s*'?\\s*([^\']*)\\s*'?");
			if (cRegEx.Match(sExpression)) {
				// Get name and value
				m_sName  = cRegEx.GetResult(0);
				m_sValue = cRegEx.GetResult(1);
				return true;
			}
		} else {
			static RegEx cRegEx("\\s*(\\w*)\\s*=\\s*\"?\\s*([^\"]*)\\s*\"?");
			if (cRegEx.Match(sExpression)) {
				// Get name and value
				m_sName  = cRegEx.GetResult(0);
				m_sValue = cRegEx.GetResult(1);
				return true;
			}
		}
	}

	// Error, could not parse next expression
	m_sName		= "";
	m_sValue	= "";
	m_nParsePos	= -1;
	return false;
}

/**
*  @brief
*    Check if the current (last parsed) parameter is valid
*/
bool ParamsParser::HasParam() const
{
	return m_sName.GetLength();
}

/**
*  @brief
*    Get name of currently parsed parameter
*/
String ParamsParser::GetName() const
{
	// Return parameter name
	return m_sName;
}

/**
*  @brief
*    Get value of currently parsed parameter
*/
String ParamsParser::GetValue() const
{
	// Return parameter value
	return m_sValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
