/*********************************************************\
 *  File: FrontendContext.cpp                            *
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
#include "PLCore/Frontend/FrontendContext.h"


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
FrontendContext::FrontendContext() :
	m_sFrontend("PLCore::FrontendPixelLight"),
	m_sFrontendImplementation("PLFrontendOS::Frontend")
{
}

/**
*  @brief
*    Destructor
*/
FrontendContext::~FrontendContext()
{
}


//[-------------------------------------------------------]
//[ Options and data                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get frontend executable name
*/
String FrontendContext::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set frontend executable name
*/
void FrontendContext::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Returns the name of the frontend RTTI class to use
*/
String FrontendContext::GetFrontend() const
{
	return m_sFrontend;
}

/**
*  @brief
*    Sets the name of the frontend RTTI class to use
*/
void FrontendContext::SetFrontend(const String &sFrontend)
{
	m_sFrontend = sFrontend;
}

/**
*  @brief
*    Returns the name of the frontend RTTI class constructor to use
*/
String FrontendContext::GetFrontendConstructor() const
{
	return m_sFrontendConstructor;
}

/**
*  @brief
*    Sets the name of the frontend RTTI class constructor to use
*/
void FrontendContext::SetFrontendConstructor(const String &sFrontendConstructor)
{
	m_sFrontendConstructor = sFrontendConstructor;
}

/**
*  @brief
*    Returns the parameters for the frontend RTTI class constructor
*/
String FrontendContext::GetFrontendConstructorParameters() const
{
	return m_sFrontendConstructorParameters;
}

/**
*  @brief
*    Sets the parameters for the frontend RTTI class constructor
*/
void FrontendContext::SetFrontendConstructorParameters(const String &sFrontendConstructorParameters)
{
	m_sFrontendConstructorParameters = sFrontendConstructorParameters;
}

/**
*  @brief
*    Returns the parameters for the instanced frontend RTTI class
*/
String FrontendContext::GetFrontendParameters() const
{
	return m_sFrontendParameters;
}

/**
*  @brief
*    Sets the parameters for the instanced frontend RTTI class
*/
void FrontendContext::SetFrontendParameters(const String &sFrontendParameters)
{
	m_sFrontendParameters = sFrontendParameters;
}

/**
*  @brief
*    Returns the name of the frontend implementation RTTI class to use
*/
String FrontendContext::GetFrontendImplementation() const
{
	return m_sFrontendImplementation;
}

/**
*  @brief
*    Sets the name of the frontend implementation RTTI class to use
*/
void FrontendContext::SetFrontendImplementation(const String &sFrontendImplementation)
{
	m_sFrontendImplementation = sFrontendImplementation;
}

/**
*  @brief
*    Returns the name of the frontend implementation RTTI class constructor to use
*/
String FrontendContext::GetFrontendImplementationConstructor() const
{
	return m_sFrontendImplementationConstructor;
}

/**
*  @brief
*    Sets the name of the frontend implementation RTTI class constructor to use
*/
void FrontendContext::SetFrontendImplementationConstructor(const String &sFrontendImplementationConstructor)
{
	m_sFrontendImplementationConstructor = sFrontendImplementationConstructor;
}

/**
*  @brief
*    Returns the parameters for the frontend implementation RTTI class constructor
*/
String FrontendContext::GetFrontendImplementationConstructorParameters() const
{
	return m_sFrontendImplementationConstructorParameters;
}

/**
*  @brief
*    Sets the parameters for the frontend implementation RTTI class constructor
*/
void FrontendContext::SetFrontendImplementationConstructorParameters(const String &sFrontendImplementationConstructorParameters)
{
	m_sFrontendImplementationConstructorParameters = sFrontendImplementationConstructorParameters;
}

/**
*  @brief
*    Returns the parameters for the instanced frontend implementation RTTI class
*/
String FrontendContext::GetFrontendImplementationParameters() const
{
	return m_sFrontendImplementationParameters;
}

/**
*  @brief
*    Sets the parameters for the instanced frontend implementation RTTI class
*/
void FrontendContext::SetFrontendImplementationParameters(const String &sFrontendImplementationParameters)
{
	m_sFrontendImplementationParameters = sFrontendImplementationParameters;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
