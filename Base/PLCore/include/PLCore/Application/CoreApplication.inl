/*********************************************************\
 *  File: CoreApplication.inl                            *
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
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get pointer to current application
*/
inline CoreApplication *CoreApplication::GetApplication()
{
	// Return global application pointer
	return g_pApplication;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get application context
*/
inline const ApplicationContext &CoreApplication::GetApplicationContext() const
{
	// Return application context
	return m_cApplicationContext;
}

/**
*  @brief
*    Get application name
*/
inline String CoreApplication::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get application title
*/
inline String CoreApplication::GetTitle() const
{
	// Return title
	return m_sTitle;
}

/**
*  @brief
*    Set application title
*/
inline void CoreApplication::SetTitle(const String &sTitle)
{
	// Set title
	m_sTitle = sTitle;
}

/**
*  @brief
*    Get version of application
*/
inline const Version &CoreApplication::GetVersion() const
{
	// Return version
	return m_cVersion;
}

/**
*  @brief
*    Set version of application
*/
inline void CoreApplication::SetVersion(const Version &cVersion)
{
	// Set version
	m_cVersion = cVersion;
}

/**
*  @brief
*    Check if application uses multi-user environment
*/
inline bool CoreApplication::GetMultiUser() const
{
	// Return multi-user flag
	return m_bMultiUser;
}

/**
*  @brief
*    Set if application uses multi-user environment
*/
inline void CoreApplication::SetMultiUser(bool bMultiUser)
{
	// Set multi-user flag
	m_bMultiUser = bMultiUser;
}

/**
*  @brief
*    Get name of config file
*/
inline String CoreApplication::GetConfigName() const
{
	// Return config name
	return m_sConfigName;
}

/**
*  @brief
*    Set name of config file
*/
inline void CoreApplication::SetConfigName(const String &sConfigName)
{
	// Set config name
	m_sConfigName = sConfigName;
}

/**
*  @brief
*    Get name of log file
*/
inline String CoreApplication::GetLogName() const
{
	// Return log name
	return m_sLogName;
}

/**
*  @brief
*    Set name of log file
*/
inline void CoreApplication::SetLogName(const String &sLogName)
{
	// Set log name
	m_sLogName = sLogName;
}

/**
*  @brief
*    Get subdirectory for application data files
*/
inline String CoreApplication::GetAppDataSubdir() const
{
	// Return application data subdirectory
	return m_sAppDataSubdir;
}

/**
*  @brief
*    Set subdirectory for application data files
*/
inline void CoreApplication::SetAppDataSubdir(const String &sSubdir)
{
	// Set application data subdirectory
	m_sAppDataSubdir = sSubdir;
}

/**
*  @brief
*    Returns the configuration instance
*/
inline Config &CoreApplication::GetConfig()
{
	// Return config
	return m_cConfig;
}

/**
*  @brief
*    Returns whether or not the application is currently running
*/
inline bool CoreApplication::IsRunning() const
{
	// Set config
	return m_bRunning;
}

/**
*  @brief
*    Exit application
*/
inline void CoreApplication::Exit(int nResult)
{
	// Set result
	m_nResult = nResult;

	// Stop application
	m_bRunning = false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
