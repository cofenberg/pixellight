/*********************************************************\
 *  File: ApplicationContext.h                           *
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


#ifndef __PLCORE_APPLICATIONCONTEXT_H__
#define __PLCORE_APPLICATIONCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Object.h"
#include "PLCore/Core/AbstractContext.h"


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
*    The application context stores data and information for an application,
*    such as startup information (what was the current directory when the
*    application started) or paths to needed resources.
*/
class ApplicationContext : public Object, public AbstractContext {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, ApplicationContext, "PLCore", PLCore::Object, "Application context")
		#ifdef PLCORE_EXPORTS	// The following is only required when compiling PLCore
			// Methods
			pl_method_0(GetExecutableFilename,	pl_ret_type(String),	"Get absolute path of application executable (native path style, e.g. on Windows: 'C:\MyApplication\x86\Test.exe').",				"")
			pl_method_0(GetExecutableDirectory,	pl_ret_type(String),	"Get directory of executable (native path style, e.g. on Windows: 'C:\MyApplication\x86').",										"")
			pl_method_0(GetAppDirectory,		pl_ret_type(String),	"Get directory of application (native path style, e.g. on Windows: 'C:\MyApplication').",											"")
			pl_method_0(GetStartupDirectory,	pl_ret_type(String),	"Get current directory when the application constructor was called (native path style, e.g. on Windows: 'C:\MyApplication\x86').",	"")
			pl_method_0(GetLogFilename,			pl_ret_type(String),	"Get absolute path to log file, empty if log has not been opened (native path style).",												"")
			pl_method_0(GetConfigFilename,		pl_ret_type(String),	"Get absolute path to config file, empty if no config is used (native path style).",												"")
		#endif
	pl_class_end


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
		*    Path to executable (native path style, e.g. on Windows: 'C:\MyApplication\x86\Test.exe')
		*/
		inline String GetExecutableFilename() const;

		/**
		*  @brief
		*    Set absolute path of application executable
		*
		*  @param[in] sExecutableFilename
		*    Path to executable (e.g. on Windows: 'C:\MyApplication\x86\Test.exe', automatically converted internally to native path style)
		*/
		PLCORE_API void SetExecutableFilename(const String &sExecutableFilename);

		/**
		*  @brief
		*    Get command line arguments
		*
		*  @return
		*    List of command line arguments that were passed to the program
		*/
		inline const Array<String> &GetArguments() const;

		/**
		*  @brief
		*    Set command line arguments
		*
		*  @param[in] lstArguments
		*    List of command line arguments that were passed to the program
		*/
		inline void SetArguments(const Array<String> &lstArguments);

		/**
		*  @brief
		*    Get directory of application executable
		*
		*  @return
		*    Directory in which the application executable is (native path style, e.g. on Windows: 'C:\MyApplication\x86')
		*
		*  @remarks
		*    This is just a convenience function and is the same as using
		*      Url(Url(GetExecutableFile()).CutFilename()).Collapse().GetNativePath()
		*/
		inline String GetExecutableDirectory() const;

		/**
		*  @brief
		*    Get directory of application
		*
		*  @return
		*    Directory in which the application is (native path style, e.g. on Windows: 'C:\MyApplication')
		*
		*  @remarks
		*    This is just a convenience function and is the same as using
		*      Url(Url(GetExecutableFile()).CutFilename() + "../").Collapse().GetNativePath()
		*/
		inline String GetAppDirectory() const;

		/**
		*  @brief
		*    Get current directory when the application constructor was called
		*
		*  @return
		*    Current directory that was set when the application constructor was called (native path style, e.g. on Windows: 'C:\MyApplication\x86')
		*/
		inline String GetStartupDirectory() const;

		/**
		*  @brief
		*    Set current directory when the application constructor was called
		*
		*  @param[in] sStartupDirectory
		*    Current directory that was set when the application constructor was called (automatically converted internally to native path style)
		*/
		PLCORE_API void SetStartupDirectory(const String &sStartupDirectory);

		/**
		*  @brief
		*    Get log filename
		*
		*  @return
		*    Absolute path to log file, empty if log has not been opened (native path style)
		*/
		inline String GetLogFilename() const;

		/**
		*  @brief
		*    Set log filename
		*
		*  @param[in] sLog
		*    Absolute path to log file, empty if log has not been opened (automatically converted internally to native path style)
		*/
		PLCORE_API void SetLogFilename(const String &sLog);

		/**
		*  @brief
		*    Get config filename
		*
		*  @return
		*    Absolute path to config file, empty if no config is used (native path style)
		*/
		inline String GetConfigFilename() const;

		/**
		*  @brief
		*    Set config filename
		*
		*  @param[in] sConfig
		*    Absolute path to config file, empty if no config is used (automatically converted internally to native path style)
		*/
		PLCORE_API void SetConfigFilename(const String &sConfig);


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
		Array<String>	m_lstArguments;			/**< Argument list */
		String			m_sExecutableDirectory;	/**< Application directory (derived from "m_sExecutableFilename") */
		String			m_sAppDirectory;		/**< Application directory (derived from "m_sExecutableFilename") */
		String			m_sStartupDirectory;	/**< The current directory when the application constructor was called */
		String			m_sLog;					/**< Absolute path to log file, empty if log has not been opened */
		String			m_sConfig;				/**< Absolute path to config file, empty if no config is used */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Application/ApplicationContext.inl"


#endif // __PLCORE_APPLICATIONCONTEXT_H__
