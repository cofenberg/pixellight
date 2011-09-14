/*********************************************************\
 *  File: ApplicationContext.cpp                         *
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
#include "PLCore/File/Url.h"
#include "PLCore/System/System.h"
#include "PLCore/Application/ApplicationContext.h"


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
ApplicationContext::ApplicationContext()
{
}

/**
*  @brief
*    Destructor
*/
ApplicationContext::~ApplicationContext()
{
}


//[-------------------------------------------------------]
//[ Options and data                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get absolute path of application executable
*/
String ApplicationContext::GetExecutableFilename() const
{
	// Return absolute executable filename
	return m_sExecutableFilename;
}

/**
*  @brief
*    Set absolute path of application executable
*/
void ApplicationContext::SetExecutableFilename(const String &sExecutableFilename)
{
	// Set absolute executable filename
	m_sExecutableFilename = sExecutableFilename;

	// Save application directory, if there's no given executable filename, do nothing special in here
	m_sAppDirectory = m_sExecutableFilename.GetLength() ? Url(Url(m_sExecutableFilename).CutFilename() + "../").Collapse().GetUrl() : "";

	// Remove the '/' at the end (due usage of the Url-class, we know there's a '/' at the end!)
	m_sAppDirectory.Delete(m_sAppDirectory.GetLength() - 1);
}

/**
*  @brief
*    Get command line arguments
*/
const Array<String> &ApplicationContext::GetArguments() const
{
	// Return argument list
	return m_lstArguments;
}

/**
*  @brief
*    Set command line arguments
*/
void ApplicationContext::SetArguments(const Array<String> &lstArguments)
{
	// Set argument list
	m_lstArguments = lstArguments;
}

/**
*  @brief
*    Get directory of application executable
*/
String ApplicationContext::GetAppDirectory() const
{
	// Return application directory
	return m_sAppDirectory;
}

/**
*  @brief
*    Get current directory when the application constructor was called
*/
String ApplicationContext::GetStartupDirectory() const
{
	// Return startup directory
	return m_sStartupDirectory;
}

/**
*  @brief
*    Set current directory when the application constructor was called
*/
void ApplicationContext::SetStartupDirectory(const String &sStartupDirectory)
{
	// Set startup directory
	m_sStartupDirectory = sStartupDirectory;
}

/**
*  @brief
*    Get log filename
*/
String ApplicationContext::GetLogFilename() const
{
	// Return log filename
	return m_sLog;
}

/**
*  @brief
*    Set log filename
*/
void ApplicationContext::SetLogFilename(const String &sLog)
{
	// Set log filename
	m_sLog = sLog;
}

/**
*  @brief
*    Get config filename
*/
String ApplicationContext::GetConfigFilename() const
{
	// Return config filename
	return m_sConfig;
}

/**
*  @brief
*    Set config filename
*/
void ApplicationContext::SetConfigFilename(const String &sConfig)
{
	// Set config filename
	m_sConfig = sConfig;
}


//[-------------------------------------------------------]
//[ Tool functions                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets the current directory to the path of the application executable
*/
void ApplicationContext::ChangeIntoAppDirectory() const
{
	// Use the executable directory as the current directory
	System::GetInstance()->SetCurrentDir(Url(m_sExecutableFilename).CutFilename());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
