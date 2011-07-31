/*********************************************************\
 *  File: ConsoleApplication.h                           *
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


#ifndef __PLCORE_CONSOLE_APPLICATION_H__
#define __PLCORE_CONSOLE_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Object.h"
#include "PLCore/Tools/Version.h"
#include "PLCore/Tools/CommandLine.h"
#include "PLCore/Application/ApplicationContext.h"
#include "PLCore/Config/Config.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*
*  @remarks
*    An application class is a template for all kind of applications.
*    It controls the main loop of the program and provides all typical data that
*    is needed for an application. Derived classes are provided for specific tasks,
*    e.g. GUI or server applications.
*
*    This class provides a most basic framework for console applications.
*    It keeps the filename and startup directory of the executable for later use and
*    provides a name, title and version of the application. It also provides an instance
*    of the command line parser to work with command line parameters (see CommandLine
*    for further explanations).
*
*  @note
*    - Implementation of the template method design pattern (although this class is not abstract)
*/
class ConsoleApplication : public Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, ConsoleApplication, "PLCore", PLCore::Object, "Application class")
		#ifdef PLCORE_EXPORTS	// The following is only required when compiling PLCore
			// Constructors
			pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
			// Methods
			pl_method_1(Exit,	pl_ret_type(void),	int,	"Exit application. Return code for application as first parameter (usually 0 means no error).",	"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Signal
		*/
		enum ESignal {
			SignalInterrupt = 1,	/**< Application interrupted (caused by ctrl-c) */
			SignalTerm				/**< Exit application */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get pointer to current application
		*
		*  @return
		*    Pointer to application
		*
		*  @remarks
		*    The global application pointer is set when the constructor of an Application
		*    is called and reset when it's destructor is called. While this makes it safe
		*    to use two or more Application instances after each other, you should *never*
		*    use more than one Application instance at a time!
		*/
		PLCORE_API static ConsoleApplication *GetApplication();


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static ConsoleApplication *g_pApplication;		/**< Pointer to the current application instance */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API ConsoleApplication();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ConsoleApplication();

		/**
		*  @brief
		*    Get application context
		*
		*  @return
		*    Application context
		*/
		PLCORE_API const ApplicationContext &GetApplicationContext() const;

		/**
		*  @brief
		*    Get application name
		*
		*  @return
		*    Name of the application
		*/
		PLCORE_API String GetName() const;

		/**
		*  @brief
		*    Set application name
		*
		*  @param[in] sName
		*    Name of the application
		*/
		PLCORE_API void SetName(const String &sName);

		/**
		*  @brief
		*    Get application title
		*
		*  @return
		*    Title of the application
		*/
		PLCORE_API String GetTitle() const;

		/**
		*  @brief
		*    Set application title
		*
		*  @param[in] sTitle
		*    Title of the application
		*/
		PLCORE_API void SetTitle(const String &sTitle);

		/**
		*  @brief
		*    Get version of application
		*
		*  @return
		*    Version of the program
		*/
		PLCORE_API const Version &GetVersion() const;

		/**
		*  @brief
		*    Set version of application
		*
		*  @param[in] cVersion
		*    Version of the program
		*/
		PLCORE_API void SetVersion(const Version &cVersion);

		/**
		*  @brief
		*    Check if application uses multi-user environment
		*
		*  @return
		*    'true' if multi-user environment is used, else 'false'
		*/
		PLCORE_API bool GetMultiUser() const;

		/**
		*  @brief
		*    Set if application uses multi-user environment
		*
		*  @param[in] bMultiUser
		*    'true' if multi-user environment is used, else 'false'
		*
		*  @remarks
		*    By default, multi-user environment is used.
		*    If on, e.g. config and log files are loaded and saved in the user directory
		*/
		PLCORE_API void SetMultiUser(bool bMultiUser);

		/**
		*  @brief
		*    Check if application uses the PixelLight runtime
		*
		*  @return
		*    'true' if PixelLight runtime is used, else 'false'
		*/
		PLCORE_API bool GetUseRuntime() const;

		/**
		*  @brief
		*    Set if application uses the PixelLight runtime
		*
		*  @param[in] bUseRuntime
		*    'true' if PixelLight runtime is used, else 'false'
		*
		*  @remarks
		*    By default, the PixelLight runtime is used. If so, the plugins contained in the
		*    installed runtime directory will be loaded and data packages will be added to the
		*    loadable manager. If you don't want to scan for and use an installed PixelLight
		*    runtime version, set this to false. Note also that a default configuration option
		*    exists for this, if it is found it will set the value of this flag.
		*/
		PLCORE_API void SetUseRuntime(bool bUseRuntime);

		/**
		*  @brief
		*    Check if application allows delayed shared library loading to speed up the program start
		*
		*  @return
		*    'true' if application allows delayed shared library loading to speed up the program start, else 'false'
		*/
		PLCORE_API bool GetDelayedPluginLoading() const;

		/**
		*  @brief
		*    Set if application allows delayed shared library loading to speed up the program start
		*
		*  @param[in] bDelayedPluginLoading
		*    'true' if it's allowed to perform delayed shared library loading to speed up the program start, else 'false'
		*/
		PLCORE_API void SetDelayedPluginLoading(bool bDelayedPluginLoading);

		/**
		*  @brief
		*    Get name of config file
		*
		*  @return
		*    Config filename (only filename, not a path!)
		*/
		PLCORE_API String GetConfigName() const;

		/**
		*  @brief
		*    Set name of config file
		*
		*  @param[in] sConfigName
		*    Config filename (only filename, not a path!)
		*
		*  @remarks
		*    Default is "<appname>.cfg"
		*/
		PLCORE_API void SetConfigName(const String &sConfigName);

		/**
		*  @brief
		*    Get name of log file
		*
		*  @return
		*    Log filename (only filename, not a path!)
		*/
		PLCORE_API String GetLogName() const;

		/**
		*  @brief
		*    Set name of log file
		*
		*  @param[in] sLogName
		*    Log filename (only filename, not a path!)
		*
		*  @remarks
		*    Default is "<appname>.log"
		*/
		PLCORE_API void SetLogName(const String &sLogName);

		/**
		*  @brief
		*    Get subdirectory for application data files
		*
		*  @return
		*    Subdirectory (relative path)
		*/
		PLCORE_API String GetAppDataSubdir() const;

		/**
		*  @brief
		*    Set subdirectory for application data files
		*
		*  @param[in] sSubdir
		*    Subdirectory (relative path)
		*
		*  @remarks
		*    Default is "<appname>" (Windows) resp. ".<appname>" (Linux).
		*    If you change this, you should use System::GetDataDirName(), to convert your name
		*    into the typical style for the used OS.
		*/
		PLCORE_API void SetAppDataSubdir(const String &sSubdir);

		/**
		*  @brief
		*    Returns the configuration instance
		*
		*  @return
		*    The configuration instance
		*/
		PLCORE_API Config &GetConfig();

		/**
		*  @brief
		*    Returns whether or not the application is currently running
		*
		*  @return
		*    'true' if the application is currently running, else 'false'
		*/
		PLCORE_API bool IsRunning() const;

		/**
		*  @brief
		*    Exit application
		*
		*  @param[in] nResult
		*    Return code for application (usually 0 means no error)
		*
		*  @remarks
		*    This will set the application return code and set m_bRunning to 'false', so that the application
		*    should exit as soon as possible. To immediatly terminate the execution, use System::Exit()
		*/
		PLCORE_API void Exit(int nResult);

		/**
		*  @brief
		*    Run the application
		*
		*  @param[in] sExecutableFilename
		*    Absolute application executable filename
		*  @param[in] lstArguments
		*    List of arguments to the program
		*
		*  @remarks
		*    The implementation does the following tasks:
		*    - Connect Linux signals
		*    - Fill application context
		*    - Call Init()
		*    - Call OnInit()
		*    - Call Main()
		*    - Call OnDeInit()
		*    - Call DeInit()
		*
		*  @return
		*    Exit code
		*/
		PLCORE_API int Run(const String &sExecutableFilename, const Array<String> &lstArguments);


	//[-------------------------------------------------------]
	//[ Protected virtual ConsoleApplication functions        ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initialization function that is called prior to OnInit()
		*
		*  @return
		*    'true' if all went fine, else 'false' which will stop the application
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Parse the command line (m_cCommandLine), set your options in the constructor
		*    - Call OnInitLog()
		*    - Call OnInitCmdLine()
		*    - Call OnInitConfig()
		*    - Call OnInitPlugins()
		*    - Call OnInitData()
		*    - Return and go on with OnInit()
		*/
		PLCORE_API virtual bool Init();

		/**
		*  @brief
		*    Main function
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - none (implement in derived classes)
		*/
		PLCORE_API virtual void Main();

		/**
		*  @brief
		*    De-initialization function that is called after OnDeInit()
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Save configuration
		*    - Close log
		*/
		PLCORE_API virtual void DeInit();

		/**
		*  @brief
		*    Called when application should initialize it's log
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Open log file according to parameter '--logfile' (default: <appname>.log)
		*    - Set verbose mode according to parameter '--verbose'
		*    - Write some general information into the log
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*/
		PLCORE_API virtual void OnInitLog();

		/**
		*  @brief
		*    Called when application should check command line options
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Check for command line errors or the parameters --help or --version
		*      - On '--help' or on error, call OnPrintHelp() and exit
		*      - On '--version', call OnPrintVersion() and exit
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*    - To end the application here, use Application::Exit()
		*/
		PLCORE_API virtual void OnInitCmdLine();

		/**
		*  @brief
		*    Called when application should initialize it's configuration
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Load configuration from file <appname>.cfg
		*    - Save config file name to ApplicationContext
		*    - If a config has been loaded or created:
		*      - Read 'FirstRun' and call OnFirstRun() if set
		*      - Read 'UsePixelLightRuntime' and update m_bUseRuntime accordingly
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*/
		PLCORE_API virtual void OnInitConfig();

		/**
		*  @brief
		*    Called when application should load it's plugins
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Scan for plugins in application directory non-recursively
		*    - Scan for plugins in application directory "Plugins/" recursively
		*    - If UseRuntime is set to 'true':
		*      - Scan for plugins in PixelLight runtime directory non-recursively
		*      - Scan for plugins in PixelLight runtime directory "Plugins/" recursively
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*/
		PLCORE_API virtual void OnInitPlugins();

		/**
		*  @brief
		*    Called when application should set it's data paths
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Set '.' as base path in LoadableManager
		*    - Scan for packages in "Data/" directory
		*    - Set application directory as base path in LoadableManager
		*    - Scan for packages in application directory "Data/" directory
		*    - If UseRuntime is set to 'true':
		*      - Set PixelLight runtime directory as base path in LoadableManager
		*      - Scan for data packages in PixelLight runtime directory
		*    - Get current language and load PixelLight localization file, if no language is defined, English is used as default
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*/
		PLCORE_API virtual void OnInitData();

		/**
		*  @brief
		*    Called when application should initialize itself
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Reset timing class
		*    - Return and go on with Main()
		*/
		PLCORE_API virtual void OnInit();

		/**
		*  @brief
		*    Called when application should de-initialize itself
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - none (implement in derived classes)
		*    - Return and go on with DeInit()
		*/
		PLCORE_API virtual void OnDeInit();

		/**
		*  @brief
		*    Function that is called when the program has been started for the first time
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Write message into log
		*/
		PLCORE_API virtual void OnFirstProgramStart();

		/**
		*  @brief
		*    Function that is called to display a help message about the application
		*
		*  @remarks
		*    The default implementation prints the application title and it's command line
		*    options onto the screen
		*/
		PLCORE_API virtual void OnPrintHelp();

		/**
		*  @brief
		*    Function that is called to display version information of the application
		*
		*  @remarks
		*    The default implementation prints the application title and version that is
		*    stored in Application
		*/
		PLCORE_API virtual void OnPrintVersion();

		/**
		*  @brief
		*    Function that is called when a signal has arrive
		*
		*  @param[in] nSignal
		*    Signal
		*  @return
		*    'true' to go on with the signal (e.g. terminate application), 'false' to cancel
		*
		*  @remarks
		*    This function is called when the operation system has sent a signal to the process.
		*    Use this to make your application exit gracefully, e.g. set a flag that lets your main function exit
		*    after finishing the current task and cleaning up the application. Otherwise, your process is likely to
		*    be killed by the system.
		*
		*  @remarks
		*    The default implementation sets m_bRunning to 'false', be sure to react to this flag!
		*/
		PLCORE_API virtual bool OnSignal(ESignal nSignal);


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Signal handler callback
		*
		*  @param[in] nSignal
		*    Signal
		*/
		static void SignalHandler(int nSignal);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		ApplicationContext	m_cApplicationContext;		/**< Application context */
		String				m_sName;					/**< Name of application */
		String				m_sTitle;					/**< Title of application */
		Version				m_cVersion;					/**< Version of application */
		bool				m_bMultiUser;				/**< Use multi-user environment? */
		bool				m_bUseRuntime;				/**< Use PixelLight runtime? */
		bool				m_bDelayedPluginLoading;	/**< 'true' if it's allowed to perform delayed shared library loading to speed up the program start, else 'false' */
		String				m_sConfigName;				/**< File name (not path) of config */
		String				m_sLogName;					/**< File name (not path) of log */
		String				m_sAppDataSubdir;			/**< Subdirectory for application data */
		Config				m_cConfig;					/**< Configuration instance */
		CommandLine			m_cCommandLine;				/**< Command line arguments */
		bool				m_bRunning;					/**< Is the application currently running? */
		int					m_nResult;					/**< Return code */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONSOLE_APPLICATION_H__
