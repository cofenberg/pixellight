/*********************************************************\
 *  File: FrontendContext.inl                            *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get frontend executable name
*/
inline String FrontendContext::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set frontend executable name
*/
inline void FrontendContext::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Returns the name of the frontend RTTI class to use
*/
inline String FrontendContext::GetFrontend() const
{
	return m_sFrontend;
}

/**
*  @brief
*    Sets the name of the frontend RTTI class to use
*/
inline void FrontendContext::SetFrontend(const String &sFrontend)
{
	m_sFrontend = sFrontend;
}

/**
*  @brief
*    Returns the name of the frontend RTTI class constructor to use
*/
inline String FrontendContext::GetFrontendConstructor() const
{
	return m_sFrontendConstructor;
}

/**
*  @brief
*    Sets the name of the frontend RTTI class constructor to use
*/
inline void FrontendContext::SetFrontendConstructor(const String &sFrontendConstructor)
{
	m_sFrontendConstructor = sFrontendConstructor;
}

/**
*  @brief
*    Returns the parameters for the frontend RTTI class constructor
*/
inline String FrontendContext::GetFrontendConstructorParameters() const
{
	return m_sFrontendConstructorParameters;
}

/**
*  @brief
*    Sets the parameters for the frontend RTTI class constructor
*/
inline void FrontendContext::SetFrontendConstructorParameters(const String &sFrontendConstructorParameters)
{
	m_sFrontendConstructorParameters = sFrontendConstructorParameters;
}

/**
*  @brief
*    Returns the parameters for the instanced frontend RTTI class
*/
inline String FrontendContext::GetFrontendParameters() const
{
	return m_sFrontendParameters;
}

/**
*  @brief
*    Sets the parameters for the instanced frontend RTTI class
*/
inline void FrontendContext::SetFrontendParameters(const String &sFrontendParameters)
{
	m_sFrontendParameters = sFrontendParameters;
}

/**
*  @brief
*    Returns the name of the frontend implementation RTTI class to use
*/
inline String FrontendContext::GetFrontendImplementation() const
{
	return m_sFrontendImplementation;
}

/**
*  @brief
*    Sets the name of the frontend implementation RTTI class to use
*/
inline void FrontendContext::SetFrontendImplementation(const String &sFrontendImplementation)
{
	m_sFrontendImplementation = sFrontendImplementation;
}

/**
*  @brief
*    Returns the name of the frontend implementation RTTI class constructor to use
*/
inline String FrontendContext::GetFrontendImplementationConstructor() const
{
	return m_sFrontendImplementationConstructor;
}

/**
*  @brief
*    Sets the name of the frontend implementation RTTI class constructor to use
*/
inline void FrontendContext::SetFrontendImplementationConstructor(const String &sFrontendImplementationConstructor)
{
	m_sFrontendImplementationConstructor = sFrontendImplementationConstructor;
}

/**
*  @brief
*    Returns the parameters for the frontend implementation RTTI class constructor
*/
inline String FrontendContext::GetFrontendImplementationConstructorParameters() const
{
	return m_sFrontendImplementationConstructorParameters;
}

/**
*  @brief
*    Sets the parameters for the frontend implementation RTTI class constructor
*/
inline void FrontendContext::SetFrontendImplementationConstructorParameters(const String &sFrontendImplementationConstructorParameters)
{
	m_sFrontendImplementationConstructorParameters = sFrontendImplementationConstructorParameters;
}

/**
*  @brief
*    Returns the parameters for the instanced frontend implementation RTTI class
*/
inline String FrontendContext::GetFrontendImplementationParameters() const
{
	return m_sFrontendImplementationParameters;
}

/**
*  @brief
*    Sets the parameters for the instanced frontend implementation RTTI class
*/
inline void FrontendContext::SetFrontendImplementationParameters(const String &sFrontendImplementationParameters)
{
	m_sFrontendImplementationParameters = sFrontendImplementationParameters;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
