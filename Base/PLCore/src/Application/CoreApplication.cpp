/*********************************************************\
 *  File: CoreApplication.cpp                            *
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
#ifdef LINUX
	#include <signal.h>
#endif
#include "PLCore/Runtime.h"
#include "PLCore/Log/Log.h"
#include "PLCore/File/Url.h"
#include "PLCore/File/Directory.h"
#include "PLCore/System/System.h"
#include "PLCore/System/Console.h"
#include "PLCore/Tools/Timing.h"
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Tools/Localization.h"
#include "PLCore/Tools/LocalizationGroup.h"
#include "PLCore/Application/CoreApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(CoreApplication)


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
CoreApplication *CoreApplication::g_pApplication = nullptr;	/**< Pointer to the current application instance */


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get pointer to current application
*/
CoreApplication *CoreApplication::GetApplication()
{
	// Return global application pointer
	return g_pApplication;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
CoreApplication::CoreApplication() :
	m_bMultiUser(true),
	m_bRunning(false),
	m_nResult(0)
{
	// Set global application pointer
	g_pApplication = this;

	// Set default application name and title
	m_sName  = Url(Url(System::GetInstance()->GetExecutableFilename()).GetFilename()).CutExtension();
	m_sTitle = m_sName;

	// Set default config and log filenames
	m_sConfigName = m_sName + ".cfg";
	m_sLogName = m_sName + ".log";

	// Set default application data subdir to "PixelLight" (Windows) respectively ".pixellight" (Linux)
	// -> Why this setting? At first, this was "m_sAppDataSubdir = System::GetInstance()->GetDataDirName(m_sName);" resulting in e.g.
	//    "C:\Users\COfenberg\AppData\Roaming\50RendererTriangleD", "C:\Users\COfenberg\AppData\Roaming\50RendererTriangle", "C:\Users\COfenberg\AppData\Roaming\XTest42"
	//    and so on. Worst case is, that in the end, "Roaming" is full of spam files and it's hard to figure out what's trash and what's important. So, by default, everything
	//    PixelLight based will be thrown into a common "PixelLight"-directory. More experienced users may then, explicitly, change this into an individual directory.
	m_sAppDataSubdir = System::GetInstance()->GetDataDirName("PixelLight");

	// Add standard command line options
	m_cCommandLine.AddFlag(		"Help",			"-h", "--help",			"Display help");
	m_cCommandLine.AddFlag(		"About",		"-V", "--version",		"Display version");
	m_cCommandLine.AddFlag(		"Verbose",		"-v", "--verbose",		"Write log messages onto the console");
	m_cCommandLine.AddParameter("LogFile",		"-l", "--logfile",		"Log filename",		"");
	m_cCommandLine.AddParameter("ConfigFile",	"-c", "--configfile",	"Config filename",	"");
}

/**
*  @brief
*    Destructor
*/
CoreApplication::~CoreApplication()
{
	// Reset global application pointer
	g_pApplication = nullptr;
}

/**
*  @brief
*    Get application context
*/
const ApplicationContext &CoreApplication::GetApplicationContext() const
{
	// Return application context
	return m_cApplicationContext;
}

/**
*  @brief
*    Get application name
*/
String CoreApplication::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Set application name
*/
void CoreApplication::SetName(const String &sName)
{
	// Semi-hack: Adjust config and log filenames, if they are set to their default values
	if (m_sConfigName == m_sName + ".cfg")
		m_sConfigName = sName + ".cfg";
	if (m_sLogName == m_sName + ".log")
		m_sLogName = sName + ".log";

	// Set new name
	m_sName = sName;
}

/**
*  @brief
*    Get application title
*/
String CoreApplication::GetTitle() const
{
	// Return title
	return m_sTitle;
}

/**
*  @brief
*    Set application title
*/
void CoreApplication::SetTitle(const String &sTitle)
{
	// Set title
	m_sTitle = sTitle;
}

/**
*  @brief
*    Get version of application
*/
const Version &CoreApplication::GetVersion() const
{
	// Return version
	return m_cVersion;
}

/**
*  @brief
*    Set version of application
*/
void CoreApplication::SetVersion(const Version &cVersion)
{
	// Set version
	m_cVersion = cVersion;
}

/**
*  @brief
*    Check if application uses multi-user environment
*/
bool CoreApplication::GetMultiUser() const
{
	// Return multi-user flag
	return m_bMultiUser;
}

/**
*  @brief
*    Set if application uses multi-user environment
*/
void CoreApplication::SetMultiUser(bool bMultiUser)
{
	// Set multi-user flag
	m_bMultiUser = bMultiUser;
}

/**
*  @brief
*    Get name of config file
*/
String CoreApplication::GetConfigName() const
{
	// Return config name
	return m_sConfigName;
}

/**
*  @brief
*    Set name of config file
*/
void CoreApplication::SetConfigName(const String &sConfigName)
{
	// Set config name
	m_sConfigName = sConfigName;
}

/**
*  @brief
*    Get name of log file
*/
String CoreApplication::GetLogName() const
{
	// Return log name
	return m_sLogName;
}

/**
*  @brief
*    Set name of log file
*/
void CoreApplication::SetLogName(const String &sLogName)
{
	// Set log name
	m_sLogName = sLogName;
}

/**
*  @brief
*    Get subdirectory for application data files
*/
String CoreApplication::GetAppDataSubdir() const
{
	// Return application data subdirectory
	return m_sAppDataSubdir;
}

/**
*  @brief
*    Set subdirectory for application data files
*/
void CoreApplication::SetAppDataSubdir(const String &sSubdir)
{
	// Set application data subdirectory
	m_sAppDataSubdir = sSubdir;
}

/**
*  @brief
*    Returns the configuration instance
*/
Config &CoreApplication::GetConfig()
{
	// Return config
	return m_cConfig;
}

/**
*  @brief
*    Returns whether or not the application is currently running
*/
bool CoreApplication::IsRunning() const
{
	// Set config
	return m_bRunning;
}

/**
*  @brief
*    Exit application
*/
void CoreApplication::Exit(int nResult)
{
	// Set result
	m_nResult = nResult;

	// Stop application
	m_bRunning = false;
}

/**
*  @brief
*    Run the application
*/
int CoreApplication::Run(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Connect Linux signals
	#ifdef LINUX
		signal(SIGINT,  CoreApplication::SignalHandler);
		signal(SIGTERM, CoreApplication::SignalHandler);
	#endif

	// Fill application context
	m_cApplicationContext.SetStartupDirectory(System::GetInstance()->GetCurrentDir());
	m_cApplicationContext.SetExecutableFilename(sExecutableFilename);
	m_cApplicationContext.SetArguments(lstArguments);

	// Do the life cycle thing - let the world know that we have been created (must be done in here instead of within the constructor)
	OnCreate();

	// The application is now running
	m_bRunning = true;

	// Initialize application
	m_nResult  = 0;
	if (OnStart()) {
		OnResume();

		// Call application-specific initialization routine
		OnInit();

		// Run application
		Main();

		// Call application-specific de-initialization routine
		OnDeInit();

		// Do the frontend life cycle thing - de-initialize
		OnPause();
		OnStop();
	}

	// The application is no longer running
	m_bRunning = false;

	// Do the life cycle thing - let the world know that we're going to die (should be done in here instead of within the destructor)
	OnDestroy();

	// Exit
	return m_nResult;
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractLifecycle functions         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called directly after the object has been created
*/
void CoreApplication::OnCreate()
{
	// No default implementation
}

/**
*  @brief
*    Called directly before a stopped object is going to start again (always followed by "OnStart()")
*/
void CoreApplication::OnRestart()
{
	// No default implementation
}

/**
*  @brief
*    Initialization function that is called prior to OnInit()
*/
bool CoreApplication::OnStart()
{
	// Parse command line
	m_cCommandLine.ParseCommandLine(GetApplicationContext().GetArguments());

	// Create log
	OnInitLog();
	if (!m_bRunning)
		return false;

	// Check command line
	OnInitCmdLine();
	if (!m_bRunning)
		return false;

	// Load configuration
	OnInitConfig();
	if (!m_bRunning)
		return false;

	// Init plugins
	OnInitPlugins();
	if (!m_bRunning)
		return false;

	// Init data
	OnInitData();
	if (!m_bRunning)
		return false;

	// No error
	return true;
}

/**
*  @brief
*    Called when the object has the focus (keep the implementation lightweight)
*/
void CoreApplication::OnResume()
{
	// No default implementation
}

/**
*  @brief
*    Called when the object has no longer the focus (keep the implementation lightweight)
*/
void CoreApplication::OnPause()
{
	// No default implementation
}

/**
*  @brief
*    De-initialization function that is called after OnDeInit()
*/
void CoreApplication::OnStop()
{
	// Save configuration
	String sConfig = m_cApplicationContext.GetConfigFilename();
	if (sConfig.GetLength())
		m_cConfig.Save(sConfig);

	// Close log
	Log::GetInstance()->Close();
}

/**
*  @brief
*    Called before the object is going to be finally destroyed
*/
void CoreApplication::OnDestroy()
{
	// No default implementation
}


//[-------------------------------------------------------]
//[ Protected virtual CoreApplication functions           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Main function
*/
void CoreApplication::Main()
{
	// No default implementation
}

/**
*  @brief
*    Called when application should initialize it's log
*/
void CoreApplication::OnInitLog()
{
	// Create log
	Log *pLog = Log::GetInstance();
	if (pLog) {
		// Check if a log file has been given on the command line
		String sLog = m_cCommandLine.GetValue("--logfile");
		if (sLog.GetLength()) {
			// Try to open log, do nothing if that fails - command line is command line ;-)
			pLog->Open(sLog);
		} else {
			// Could not open log, try standard locations
			if (m_sLogName.GetLength()) {
				// Create user data directory, if it does not yet exist
				Directory cDir(System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir);
				if (!cDir.Exists())
					cDir.Create();

				// Try user directory first, then use current directory
				sLog = System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir + '/' + m_sLogName;
				if (!(m_bMultiUser && pLog->Open(sLog))) {
					// Not successful, so try current directory instead
					sLog = System::GetInstance()->GetCurrentDir() + '/' + m_sLogName;
					if (!pLog->Open(sLog)) {
						// Error: Could not open log
						sLog = "";
					}
				}
			}
		}

		// Log opened?
		if (sLog.GetLength()) {
			// Save log filename in application context
			m_cApplicationContext.SetLogFilename(sLog);

			// Set verbose mode
			if (m_cCommandLine.IsValueSet("--verbose"))
				pLog->SetVerbose(true);
		}
	}

	{ // Write some general information into the log
		// Create the log header:
		PL_LOG(Info, "Log-system started")
		PL_LOG(Quiet, '\n')
		PL_LOG(Info, "< " + Runtime::GetVersion().ToString() + " >")
		PL_LOG(Info, "PLCore build: "__DATE__" "__TIME__"")
		PL_LOG(Info, "Application start time: " + System::GetInstance()->GetTime().ToString())
		PL_LOG(Info, "\nPLCore information:\n" + System::GetInstance()->GetInfo() + '\n')
		PL_LOG(Quiet, '\n')

		{ // Print out directory information:
			// System directories
			PL_LOG(Info, "System directories:")
			PL_LOG(Info, "- Executable: " + System::GetInstance()->GetExecutableFilename())
			PL_LOG(Info, "- Home:       " + System::GetInstance()->GetUserHomeDir())
			PL_LOG(Info, "- Data:       " + System::GetInstance()->GetUserDataDir())
			PL_LOG(Info, "- Current:    " + System::GetInstance()->GetCurrentDir())
			PL_LOG(Quiet, '\n')

			// PixelLight directories
			PL_LOG(Info, "PixelLight directories:")
			PL_LOG(Info, "- Runtime:    " + Runtime::GetDirectory())
			PL_LOG(Quiet, '\n')

			// Application context
			PL_LOG(Info, "Application context:")
			PL_LOG(Info, "- Executable: " + GetApplicationContext().GetExecutableFilename())
			PL_LOG(Info, "- Startup:    " + GetApplicationContext().GetStartupDirectory())
			PL_LOG(Info, "- AppDir:     " + GetApplicationContext().GetAppDirectory())
			PL_LOG(Quiet, '\n')
		}

		// Print out the general system info:
		PL_LOG(Info, String::Format("CPU: %d MHz", System::GetInstance()->GetCPUMhz()))

		// Start enumerate messages
		PL_LOG(Quiet, "\n\n")
		PL_LOG(Info, "Messages:")
	}
}

/**
*  @brief
*    Called when application should check command line options
*/
void CoreApplication::OnInitCmdLine()
{
	// Check command line
	if (m_cCommandLine.HasErrors() || m_cCommandLine.IsValueSet("--help")) {
		// Display help and exit
		OnPrintHelp();
		Exit(1);
	} else if (m_cCommandLine.IsValueSet("--version")) {
		// Display about and exit
		OnPrintVersion();
		Exit(0);
	}
}

/**
*  @brief
*    Called when application should initialize it's configuration
*/
void CoreApplication::OnInitConfig()
{
	// Check if a config file has been given on the command line
	String sConfig = m_cCommandLine.GetValue("--configfile");
	if (sConfig.GetLength()) {
		// Try to load, do nothing if that fails - command line is command line ;-)
		m_cConfig.Load(sConfig);
	} else {
		// Could not open config file, try standard locations
		if (m_sConfigName.GetLength()) {
			// Create user data directory, if it does not yet exist
			Directory cDir(System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir);
			if (!cDir.Exists())
				cDir.Create();

			// Try user directory first, then use application (!) directory
			sConfig = System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir + '/' + m_sConfigName;
			if (!(m_bMultiUser && m_cConfig.Load(sConfig))) {
				// Not successful, so try application directory instead
				sConfig = m_cApplicationContext.GetAppDirectory() + '/' + m_sConfigName;
				if (!m_cConfig.Load(sConfig)) {
					// Error: Could not open config file
					sConfig = "";
				}
			}
		}
	}

	// If no config file could be found, set a filename anyway so that the config can be saved later
	if (!sConfig.GetLength()) {
		// Only if we want a config at all
		if (m_sConfigName.GetLength()) {
			// Try user directory first, then use application directory
			Directory cDir(System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir);
			if (m_bMultiUser && cDir.Exists())
				sConfig = System::GetInstance()->GetUserDataDir() + '/' + m_sAppDataSubdir + '/' + m_sConfigName;
			else
				sConfig = m_cApplicationContext.GetAppDirectory() + '/' + m_sConfigName;
		}
	}

	// Save config filename in application context
	m_cApplicationContext.SetConfigFilename(sConfig);

	// Analyze configuration
	if (m_sConfigName.GetLength()) {
		// Is this the first program start?
		if (m_cConfig.GetVar("PLCore::CoreConfig", "FirstRun").GetBool()) {
			// Call virtual function
			OnFirstProgramStart();

			// Reset flag
			m_cConfig.SetVar("PLCore::CoreConfig", "FirstRun", "0");
		}
	}
}

/**
*  @brief
*    Called when application should load it's plugins
*/
void CoreApplication::OnInitPlugins()
{
	// Scan PL-runtime directory for compatible plugins and load them in
	Runtime::ScanDirectoryPlugins();

	// Scan for plugins in the application directory, but not recursively, please. This is quite useful
	// for shipping applications and putting all plugins inside the application root directory
	// (which is necessary due to VC manifest policy)
	ClassManager::GetInstance()->ScanPlugins(m_cApplicationContext.GetAppDirectory(), NonRecursive);

	// Scan for plugins in "Plugins" directory (recursively)
	ClassManager::GetInstance()->ScanPlugins(m_cApplicationContext.GetAppDirectory() + "/Plugins/", Recursive);
}

/**
*  @brief
*    Called when application should set it's data paths
*/
void CoreApplication::OnInitData()
{
	// Scan PL-runtime directory for compatible data and register it
	Runtime::ScanDirectoryData();

	// Is '.' (= the current directory) already a base directory? If not, add it right now...
	LoadableManager *pLoadableManager = LoadableManager::GetInstance();
	if (!pLoadableManager->IsBaseDir('.'))
		pLoadableManager->AddBaseDir('.');

	// Is the application directory already a base directory? If not, add it right now...
	if (!pLoadableManager->IsBaseDir(m_cApplicationContext.GetAppDirectory()))
		pLoadableManager->AddBaseDir(m_cApplicationContext.GetAppDirectory());

	// Scan for packages in current "Data" directory
	const String sCurrentDir = System::GetInstance()->GetCurrentDir();
	pLoadableManager->ScanPackages(sCurrentDir.GetLength() ? (sCurrentDir + "/Data") : "Data");

	// Scan for packages in application's "Data" directory
	if (sCurrentDir != m_cApplicationContext.GetAppDirectory())
		pLoadableManager->ScanPackages(m_cApplicationContext.GetAppDirectory().GetLength() ? (m_cApplicationContext.GetAppDirectory() + "/Data") : "Data");

	// Get localization language (from config or from default)
	String sLanguage = m_cConfig.GetVar("PLCore::CoreConfig", "Language");
	if (!sLanguage.GetLength()) {
		// Use always English instead of the current program locale language so that we have a known default behaviour
		sLanguage = "English";
	}

	// Setup localization system
	Localization::GetInstance()->SetLanguage(sLanguage);
	if (sLanguage.GetLength()) {
		LocalizationGroup *pLocalizationGroup = Localization::GetInstance()->AddGroup(Localization::PixelLight);
		if (pLocalizationGroup)
			pLocalizationGroup->Load("Data/Misc/" + Localization::PixelLight + '_' + sLanguage + ".loc");
	}
}

/**
*  @brief
*    Called when application should initialize itself
*/
void CoreApplication::OnInit()
{
	// Reset timing class
	Timing::GetInstance()->Reset();
}

/**
*  @brief
*    Called when application should de-initialize itself
*/
void CoreApplication::OnDeInit()
{
	// No default implementation
}

/**
*  @brief
*    Function that is called when the program has been started for the first time
*/
void CoreApplication::OnFirstProgramStart()
{
	// Write message into log
	PL_LOG(Info, "First application start detected")
}

/**
*  @brief
*    Function that is called to display a help message about the application
*/
void CoreApplication::OnPrintHelp()
{
	// Print application title
	System::GetInstance()->GetConsole().Print(m_sTitle + "\n\n");

	// Print available command line options
	m_cCommandLine.PrintHelp(m_sName);
}

/**
*  @brief
*    Function that is called to display version information of the application
*/
void CoreApplication::OnPrintVersion()
{
	// Print application title and version
	System::GetInstance()->GetConsole().Print(m_sTitle + " - V" + m_cVersion.ToString() + '\n');
}

/**
*  @brief
*    Function that is called when a signal has arrive
*/
bool CoreApplication::OnSignal(ESignal nSignal)
{
	// Catch signal
	switch (nSignal) {
		// Interrupt (exit application by ctrl-c)
		case SignalInterrupt:
			// Exit application gracefully
			m_bRunning = false;
			return false;

		// Terminate (exit application)
		case SignalTerm:
			// Exit application gracefully
			m_bRunning = false;
			return false;
	}

	// Signal not handled, go on with default action
	return true;
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Signal handler callback
*/
void CoreApplication::SignalHandler(int nSignal)
{
	// Linux implementation
	#ifdef LINUX
		// Catch signal
		switch (nSignal) {
			// Interrupt (exit application by ctrl-c)
			case SIGINT:
				// Send signal to application
				if (!CoreApplication::GetApplication()->OnSignal(SignalInterrupt)) {
					// Ignore signal and restore handler
					signal(SIGINT, CoreApplication::SignalHandler);
				} else {
					// Signal handler has done it's job, re-raise signal
					signal(nSignal, SIG_DFL);
					raise(nSignal);
				}
				break;

			// Terminate (exit application)
			case SIGTERM:
				// Send signal to application
				if (!CoreApplication::GetApplication()->OnSignal(SignalTerm)) {
					// Ignore signal and restore handler
					signal(SIGTERM, CoreApplication::SignalHandler);
				} else {
					// Signal handler has done it's job, re-raise signal
					signal(nSignal, SIG_DFL);
					raise(nSignal);
				}
				break;
		}
	#endif
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
