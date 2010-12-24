/*********************************************************\
 *  File: ApplicationContext.h                           *
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


#ifndef __PLCORE_APPLICATIONCONTEXT_H__
#define __PLCORE_APPLICATIONCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application context
*
*  @remarks
*    The application context store data and information for an application,
*    such as startup information (what was the current directory when the
*    application started) or paths to needed resources.
*/
class ApplicationContext {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API ApplicationContext();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ApplicationContext();


		//[-------------------------------------------------------]
		//[ Options and data                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get absolute path of application executable
		*
		*  @return
		*    Path to executable (e.g. on Windows: 'C:\MyApplication\Test.exe')
		*/
		PLCORE_API PLGeneral::String GetExecutableFilename() const;

		/**
		*  @brief
		*    Set absolute path of application executable
		*
		*  @param[in] sExecutableFilename
		*    Path to executable (e.g. on Windows: 'C:\MyApplication\Test.exe')
		*/
		PLCORE_API void SetExecutableFilename(const PLGeneral::String &sExecutableFilename);

		/**
		*  @brief
		*    Get directory of application executable
		*
		*  @return
		*    Directory in which the application executable is (e.g. on Windows: 'C:\MyApplication')
		*
		*  @remarks
		*    This is just a convenience function and is the same as using
		*      Url(GetExecutableFile()).CutFilename()
		*/
		PLCORE_API PLGeneral::String GetAppDirectory() const;

		/**
		*  @brief
		*    Get current directory when the application constructor was called
		*
		*  @return
		*    Current directory that was set when the application constructor was called (e.g. on Windows: 'C:\MyApplication')
		*/
		PLCORE_API PLGeneral::String GetStartupDirectory() const;

		/**
		*  @brief
		*    Set current directory when the application constructor was called
		*
		*  @param[in] sStartupDirectory
		*    Current directory that was set when the application constructor was called
		*/
		PLCORE_API void SetStartupDirectory(const PLGeneral::String &sStartupDirectory);

		/**
		*  @brief
		*    Get log filename
		*
		*  @return
		*    Absolute path to log file, empty if log has not been opened
		*/
		PLCORE_API PLGeneral::String GetLogFilename() const;

		/**
		*  @brief
		*    Set log filename
		*
		*  @param[in] sLog
		*    Absolute path to log file, empty if log has not been opened
		*/
		PLCORE_API void SetLogFilename(const PLGeneral::String &sLog);

		/**
		*  @brief
		*    Get config filename
		*
		*  @return
		*    Absolute path to config file, empty if no config is used
		*/
		PLCORE_API PLGeneral::String GetConfigFilename() const;

		/**
		*  @brief
		*    Set config filename
		*
		*  @param[in] sConfig
		*    Absolute path to config file, empty if no config is used
		*/
		PLCORE_API void SetConfigFilename(const PLGeneral::String &sConfig);

		/**
		*  @brief
		*    Get command line arguments
		*
		*  @return
		*    List of command line arguments that were passed to the program
		*/
		PLCORE_API const PLGeneral::Array<PLGeneral::String> &GetArguments() const;

		/**
		*  @brief
		*    Set command line arguments
		*
		*  @param[in] lstArguments
		*    List of command line arguments that were passed to the program
		*/
		PLCORE_API void SetArguments(const PLGeneral::Array<PLGeneral::String> &lstArguments);


		//[-------------------------------------------------------]
		//[ Tool functions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Sets the current directory to the path of the application executable
		*
		*  @note
		*    - Whenever possible, do not manipulate the current directory, this may backfire when you don't expect it
		*    - Because the executable filename is used, which is set within "ConsoleApplication::Run()",
		*      calling this method from inside a application constructor is not recommended
		*/
		PLCORE_API void ChangeIntoAppDirectory() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String					m_sExecutableFilename;	/**< Absolute executable filename of the application */
		PLGeneral::String					m_sAppDirectory;		/**< Application directory */
		PLGeneral::String					m_sStartupDirectory;	/**< The current directory when the application constructor was called */
		PLGeneral::String					m_sLog;					/**< Absolute path to log file, empty if log has not been opened */
		PLGeneral::String					m_sConfig;				/**< Absolute path to config file, empty if no config is used */
		PLGeneral::Array<PLGeneral::String>	m_lstArguments;			/**< Argument list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_APPLICATIONCONTEXT_H__
