/*********************************************************\
 *  File: ApplicationContext.inl                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
//[-------------------------------------------------------]
//[ Options and data                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get absolute path of application executable
*/
inline String ApplicationContext::GetExecutableFilename() const
{
	// Return absolute executable filename
	return m_sExecutableFilename;
}

/**
*  @brief
*    Get command line arguments
*/
inline const Array<String> &ApplicationContext::GetArguments() const
{
	// Return argument list
	return m_lstArguments;
}

/**
*  @brief
*    Set command line arguments
*/
inline void ApplicationContext::SetArguments(const Array<String> &lstArguments)
{
	// Set argument list
	m_lstArguments = lstArguments;
}

/**
*  @brief
*    Get directory of application executable
*/
inline String ApplicationContext::GetAppDirectory() const
{
	// Return application directory
	return m_sAppDirectory;
}

/**
*  @brief
*    Get current directory when the application constructor was called
*/
inline String ApplicationContext::GetStartupDirectory() const
{
	// Return startup directory
	return m_sStartupDirectory;
}

/**
*  @brief
*    Get log filename
*/
inline String ApplicationContext::GetLogFilename() const
{
	// Return log filename
	return m_sLog;
}

/**
*  @brief
*    Get config filename
*/
inline String ApplicationContext::GetConfigFilename() const
{
	// Return config filename
	return m_sConfig;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
