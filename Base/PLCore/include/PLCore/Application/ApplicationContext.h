/*********************************************************\
 *  File: ApplicationContext.h                           *
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


#ifndef __PLCORE_APPLICATIONCONTEXT_H__
#define __PLCORE_APPLICATIONCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/Container/Array.h"
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
		PLCORE_API String GetExecutableFilename() const;

		/**
		*  @brief
		*    Set absolute path of application executable
		*
		*  @param[in] sExecutableFilename
		*    Path to executable (e.g. on Windows: 'C:\MyApplication\Test.exe')
		*/
		PLCORE_API void SetExecutableFilename(const String &sExecutableFilename);

		/**
		*  @brief
		*    Get directory of application executable
		*
		*  @return
		*    Directory in which the application executable is (e.g. on Windows: 'C:\MyApplication')
		*
		*  @remarks
		*    This is just a convenience function and is the same as using
		*      Url(Url(GetExecutableFile()).CutFilename() + "../").Collapse().GetUrl()
		*/
		PLCORE_API String GetAppDirectory() const;

		/**
		*  @brief
		*    Get current directory when the application constructor was called
		*
		*  @return
		*    Current directory that was set when the application constructor was called (e.g. on Windows: 'C:\MyApplication')
		*/
		PLCORE_API String GetStartupDirectory() const;

		/**
		*  @brief
		*    Set current directory when the application constructor was called
		*
		*  @param[in] sStartupDirectory
		*    Current directory that was set when the application constructor was called
		*/
		PLCORE_API void SetStartupDirectory(const String &sStartupDirectory);

		/**
		*  @brief
		*    Get log filename
		*
		*  @return
		*    Absolute path to log file, empty if log has not been opened
		*/
		PLCORE_API String GetLogFilename() const;

		/**
		*  @brief
		*    Set log filename
		*
		*  @param[in] sLog
		*    Absolute path to log file, empty if log has not been opened
		*/
		PLCORE_API void SetLogFilename(const String &sLog);

		/**
		*  @brief
		*    Get config filename
		*
		*  @return
		*    Absolute path to config file, empty if no config is used
		*/
		PLCORE_API String GetConfigFilename() const;

		/**
		*  @brief
		*    Set config filename
		*
		*  @param[in] sConfig
		*    Absolute path to config file, empty if no config is used
		*/
		PLCORE_API void SetConfigFilename(const String &sConfig);

		/**
		*  @brief
		*    Get command line arguments
		*
		*  @return
		*    List of command line arguments that were passed to the program
		*/
		PLCORE_API const Array<String> &GetArguments() const;

		/**
		*  @brief
		*    Set command line arguments
		*
		*  @param[in] lstArguments
		*    List of command line arguments that were passed to the program
		*/
		PLCORE_API void SetArguments(const Array<String> &lstArguments);


		//[-------------------------------------------------------]
		//[ Tool functions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Sets the current directory to the path of the application executable
		*
		*  @note
		*    - Whenever possible, do not manipulate the current directory, this may backfire when you don't expect it
		*    - Because the executable filename is used, which is set within "CoreApplication::Run()",
		*      calling this method from inside a application constructor is not recommended
		*/
		PLCORE_API void ChangeIntoAppDirectory() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		String			m_sExecutableFilename;	/**< Absolute executable filename of the application */
		String			m_sAppDirectory;		/**< Application directory */
		String			m_sStartupDirectory;	/**< The current directory when the application constructor was called */
		String			m_sLog;					/**< Absolute path to log file, empty if log has not been opened */
		String			m_sConfig;				/**< Absolute path to config file, empty if no config is used */
		Array<String>	m_lstArguments;			/**< Argument list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_APPLICATIONCONTEXT_H__
