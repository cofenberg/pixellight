/*********************************************************\
 *  File: ApplicationContext.cpp                         *
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
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ApplicationContext)


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
*    Set absolute path of application executable
*/
void ApplicationContext::SetExecutableFilename(const String &sExecutableFilename)
{
	// Set absolute executable filename, ensure it's native path style
	m_sExecutableFilename = Url(sExecutableFilename).GetNativePath();

	// Save application directory, if there's no given executable filename, do nothing special in here
	m_sAppDirectory = m_sExecutableFilename.GetLength() ? Url(Url(m_sExecutableFilename).CutFilename() + "../").Collapse().GetNativePath() : "";

	// Remove the '/' at the end (due usage of the Url-class, we know there's a '/' at the end!)
	m_sAppDirectory.Delete(m_sAppDirectory.GetLength() - 1);

	// No empty string, please (it should always be possible to add e.g. '/Data' without problems)
	if (!m_sAppDirectory.GetLength())
		m_sAppDirectory = '.';
}

/**
*  @brief
*    Set current directory when the application constructor was called
*/
void ApplicationContext::SetStartupDirectory(const String &sStartupDirectory)
{
	// Set startup directory, ensure it's native path style
	m_sStartupDirectory = Url(sStartupDirectory).GetNativePath();
}

/**
*  @brief
*    Set log filename
*/
void ApplicationContext::SetLogFilename(const String &sLog)
{
	// Set log filename, ensure it's native path style
	m_sLog = Url(sLog).GetNativePath();
}

/**
*  @brief
*    Set config filename
*/
void ApplicationContext::SetConfigFilename(const String &sConfig)
{
	// Set config filename, ensure it's native path style
	m_sConfig = Url(sConfig).GetNativePath();
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
