/*********************************************************\
 *  File: CommandLineOption.cpp                          *
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
#include "PLCore/Tools/CommandLineOption.h"


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
CommandLineOption::CommandLineOption() :
	m_nType(OptionParam),
	m_bRequired(false)
{
}

/**
*  @brief
*    Destructor
*/
CommandLineOption::~CommandLineOption()
{
}

/**
*  @brief
*    Get option type
*/
CommandLineOption::EType CommandLineOption::GetType() const
{
	// Return type
	return m_nType;
}

/**
*  @brief
*    Set option type
*/
void CommandLineOption::SetType(EType nType)
{
	// Set type
	m_nType = nType;
}

/**
*  @brief
*    Check if this option is required
*/
bool CommandLineOption::IsRequired() const
{
	// Return required-flag
	return m_bRequired;
}

/**
*  @brief
*    Set if this option is required
*/
void CommandLineOption::SetRequired(bool bRequired)
{
	// Set required-flag
	m_bRequired = bRequired;
}

/**
*  @brief
*    Get name
*/
String CommandLineOption::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Set name
*/
void CommandLineOption::SetName(const String &sName)
{
	// Set name
	m_sName = sName;
}

/**
*  @brief
*    Get short name
*/
String CommandLineOption::GetShortName() const
{
	// Return short name
	return m_sShortName;
}

/**
*  @brief
*    Set short name
*/
void CommandLineOption::SetShortName(const String &sName)
{
	// Set short name
	m_sShortName = sName;
}

/**
*  @brief
*    Get long name
*/
String CommandLineOption::GetLongName() const
{
	// Return long name
	return m_sLongName;
}

/**
*  @brief
*    Set long name
*/
void CommandLineOption::SetLongName(const String &sName)
{
	// Set long name
	m_sLongName = sName;
}

/**
*  @brief
*    Get description
*/
String CommandLineOption::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Set description
*/
void CommandLineOption::SetDescription(const String &sDescription)
{
	// Set description
	m_sDescription = sDescription;
}

/**
*  @brief
*    Get default value
*/
String CommandLineOption::GetDefault() const
{
	// Return default value
	return m_sDefault;
}

/**
*  @brief
*    Set default value
*/
void CommandLineOption::SetDefault(const String &sDefault)
{
	// Set default value
	m_sDefault = sDefault;
}

/**
*  @brief
*    Check if option value is set (either by command line or by default value)
*/
bool CommandLineOption::IsSet() const
{
	return (m_sValue.GetLength() > 0);
}

/**
*  @brief
*    Get option value
*/
String CommandLineOption::GetValue() const
{
	// Return value
	return m_sValue;
}

/**
*  @brief
*    Set value
*/
void CommandLineOption::SetValue(const String &sValue)
{
	// Set value
	m_sValue = sValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
