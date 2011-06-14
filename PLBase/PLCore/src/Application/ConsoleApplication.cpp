/*********************************************************\
 *  File: ConsoleApplication.cpp                         *
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
#include <PLGeneral/Log/Log.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include "PLCore/Core.h"
#include "PLCore/Tools/LoadableManager.h"
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LocalizationGroup.h>
#include "PLCore/Application/ConsoleApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ConsoleApplication)


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
ConsoleApplication *ConsoleApplication::g_pApplication = nullptr;	/**< Pointer to the current application instance */


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get pointer to current application
*/
ConsoleApplication *ConsoleApplication::GetApplication()
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
ConsoleApplication::ConsoleApplication() :
	m_bMultiUser(true),
	m_bUseRuntime(true),
	m_bDelayedPluginLoading(true),
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

	// Set default application data subdir
	m_sAppDataSubdir = System::GetInstance()->GetDataDirName(m_sName);

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
ConsoleApplication::~ConsoleApplication()
{
	// Reset global application pointer
	g_pApplication = nullptr;
}

/**
*  @brief
*    Get application context
*/
const ApplicationContext &ConsoleApplication::GetApplicationContext() const
{
	// Return application context
	return m_cApplicationContext;
}

/**
*  @brief
*    Get application name
*/
String ConsoleApplication::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Set application name
*/
void ConsoleApplication::SetName(const String &sName)
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
String ConsoleApplication::GetTitle() const
{
	// Return title
	return m_sTitle;
}

/**
*  @brief
*    Set application title
*/
void ConsoleApplication::SetTitle(const String &sTitle)
{
	// Set title
	m_sTitle = sTitle;
}

/**
*  @brief
*    Get version of application
*/
const Version &ConsoleApplication::GetVersion() const
{
	// Return version
	return m_cVersion;
}

/**
*  @brief
*    Set version of application
*/
void ConsoleApplication::SetVersion(const Version &cVersion)
{
	// Set version
	m_cVersion = cVersion;
}

/**
*  @brief
*    Check if application uses multi-user environment
*/
bool ConsoleApplication::GetMultiUser() const
{
	// Return multi-user flag
	return m_bMultiUser;
}

/**
*  @brief
*    Set if application uses multi-user environment
*/
void ConsoleApplication::SetMultiUser(bool bMultiUser)
{
	// Set multi-user flag
	m_bMultiUser = bMultiUser;
}

/**
*  @brief
*    Check if application uses the PixelLight runtime
*/
bool ConsoleApplication::GetUseRuntime() const
{
	// Return runtime flag
	return m_bUseRuntime;
}

/**
*  @brief
*    Set if application uses the PixelLight runtime
*/
void ConsoleApplication::SetUseRuntime(bool bUseRuntime)
{
	// Set runtime flag
	m_bUseRuntime = bUseRuntime;
}

/**
*  @brief
*    Check if application allows delayed shared library loading to speed up the program start
*/
bool ConsoleApplication::GetDelayedPluginLoading() const
{
	// Return the current value
	return m_bDelayedPluginLoading;
}

/**
*  @brief
*    Set if application allows delayed shared library loading to speed up the program start
*/
void ConsoleApplication::SetDelayedPluginLoading(bool bDelayedPluginLoading)
{
	// Set new value
	m_bDelayedPluginLoading = bDelayedPluginLoading;
}

/**
*  @brief
*    Get name of config file
*/
String ConsoleApplication::GetConfigName() const
{
	// Return config name
	return m_sConfigName;
}

/**
*  @brief
*    Set name of config file
*/
void ConsoleApplication::SetConfigName(const String &sConfigName)
{
	// Set config name
	m_sConfigName = sConfigName;
}

/**
*  @brief
*    Get name of log file
*/
String ConsoleApplication::GetLogName() const
{
	// Return log name
	return m_sLogName;
}

/**
*  @brief
*    Set name of log file
*/
void ConsoleApplication::SetLogName(const String &sLogName)
{
	// Set log name
	m_sLogName = sLogName;
}

/**
*  @brief
*    Get subdirectory for application data files
*/
String ConsoleApplication::GetAppDataSubdir() const
{
	// Return application data subdirectory
	return m_sAppDataSubdir;
}

/**
*  @brief
*    Set subdirectory for application data files
*/
void ConsoleApplication::SetAppDataSubdir(const String &sSubdir)
{
	// Set application data subdirectory
	m_sAppDataSubdir = sSubdir;
}

/**
*  @brief
*    Returns the configuration instance
*/
Config &ConsoleApplication::GetConfig()
{
	// Return config
	return m_cConfig;
}

/**
*  @brief
*    Returns whether or not the application is currently running
*/
bool ConsoleApplication::IsRunning() const
{
	// Set config
	return m_bRunning;
}

/**
*  @brief
*    Exit application
*/
void ConsoleApplication::Exit(int nResult)
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
int ConsoleApplication::Run(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Connect Linux signals
	#ifdef LINUX
		signal(SIGINT,  ConsoleApplication::SignalHandler);
		signal(SIGTERM, ConsoleApplication::SignalHandler);
	#endif

	// Fill application context
	m_cApplicationContext.SetStartupDirectory(System::GetInstance()->GetCurrentDir());
	m_cApplicationContext.SetExecutableFilename(sExecutableFilename);
	m_cApplicationContext.SetArguments(lstArguments);

	// The application is now running
	m_bRunning = true;

	// Initialize application
	m_nResult  = 0;
	if (Init()) {
		// Call application-specific initialization routine
		OnInit();

		// Run application
		Main();

		// Call application-specific de-initialization routine
		OnDeInit();

		// De-Initialize application
		DeInit();
	}

	// The application is no longer running
	m_bRunning = false;

	// Exit
	return m_nResult;
}


//[-------------------------------------------------------]
//[ Protected virtual ConsoleApplication functions        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization function that is called prior to Main()
*/
bool ConsoleApplication::Init()
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
*    Main function
*/
void ConsoleApplication::Main()
{
	// No default implementation
}

/**
*  @brief
*    De-initialization function that is called after Main()
*/
void ConsoleApplication::DeInit()
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
*    Called when application should initialize it's log
*/
void ConsoleApplication::OnInitLog()
{
	// Create log
	Log *pLog = Log::GetInstance();
	if (pLog) {
		// Check if a log file has been given on the commandline
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
					// Not successfull, so try current directory instead
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
		PL_LOG(Info, "< " + Core::GetVersion().ToString() + " >")
		PL_LOG(Info, "PLCore build: "__DATE__" "__TIME__"")
		PL_LOG(Info, "Application start time: " + System::GetInstance()->GetTime().ToString())
		PL_LOG(Info, "\nPLGeneral infomation:\n" + System::GetInstance()->GetInfo() + '\n')
		PL_LOG(Quiet, '\n')

		{ // Print out directory information:
			// System directories
			PL_LOG(Info, "System directories:");
			PL_LOG(Info, "- Executable: " + System::GetInstance()->GetExecutableFilename());
			PL_LOG(Info, "- Home:       " + System::GetInstance()->GetUserHomeDir());
			PL_LOG(Info, "- Data:       " + System::GetInstance()->GetUserDataDir());
			PL_LOG(Info, "- Current:    " + System::GetInstance()->GetCurrentDir());
			PL_LOG(Quiet, '\n');

			// PixelLight directories
			PL_LOG(Info, "PixelLight directories:");
			PL_LOG(Info, "- Runtime:    " + PLCore::Core::GetRuntimeDirectory());
			PL_LOG(Quiet, '\n');

			// Application context
			PL_LOG(Info, "Application context:");
			PL_LOG(Info, "- Executable: " + GetApplicationContext().GetExecutableFilename());
			PL_LOG(Info, "- Startup:    " + GetApplicationContext().GetStartupDirectory());
			PL_LOG(Info, "- AppDir:     " + GetApplicationContext().GetAppDirectory());
			PL_LOG(Quiet, '\n');
		}

		// Print out the general system info:
		PL_LOG(Info, String::Format("CPU: %d Mhz", System::GetInstance()->GetCPUMhz()))

		// Start enumerate messages
		PL_LOG(Quiet, "\n\n")
		PL_LOG(Info, "Messages:")
	}
}

/**
*  @brief
*    Called when application should check command line options
*/
void ConsoleApplication::OnInitCmdLine()
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
void ConsoleApplication::OnInitConfig()
{
	// Check if a config file has been given on the commandline
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
				// Not successfull, so try application directory instead
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

	// Analize config
	if (m_sConfigName.GetLength()) {
		// Is this the first program start?
		if (m_cConfig.GetVar("PLCore::CoreGeneralConfig", "FirstRun").GetBool()) {
			// Call virtual function
			OnFirstProgramStart();

			// Reset flag
			m_cConfig.SetVar("PLCore::CoreGeneralConfig", "FirstRun", "0");
		}

		// Use PixelLight runtime?
		m_bUseRuntime = m_cConfig.GetVar("PLCore::CoreGeneralConfig", "UsePixelLightRuntime").GetBool();

		// Allow delayed shared library loading to speed up the program start?
		m_bDelayedPluginLoading = m_cConfig.GetVar("PLCore::CoreGeneralConfig", "DelayedPluginLoading").GetBool();
	}
}

/**
*  @brief
*    Called when application should load it's plugins
*/
void ConsoleApplication::OnInitPlugins()
{
	// Start the stopwatch
	Stopwatch cStopwatch(true);

	// Scan for plugins in the application directory, but not recursively, please. This is quite useful
	// for shipping applications and putting all plugins inside the application root directory
	// (which is necessary due to VC manifest policy)
	ClassManager::GetInstance()->ScanPlugins(m_cApplicationContext.GetAppDirectory(), NonRecursive, m_bDelayedPluginLoading);

	// Scan for plugins in "Plugins" directory (recursively)
	ClassManager::GetInstance()->ScanPlugins(m_cApplicationContext.GetAppDirectory() + "/Plugins/", Recursive, m_bDelayedPluginLoading);

	// Use PixelLight runtime?
	if (m_bUseRuntime) {
		// Get PixelLight runtime directory
		String sPLDirectory = Core::GetRuntimeDirectory();
		if (sPLDirectory.GetLength()) {
			// Scan for plugins in the PixelLight runtime directory, but not recursively, please. This is quite useful
			// for projects which can be used completely dynamically, but can also be used in other C++ projects
			// to access certain features.
			ClassManager::GetInstance()->ScanPlugins(sPLDirectory, NonRecursive, m_bDelayedPluginLoading);

			// Scan for plugins in PixelLight runtime directory
			ClassManager::GetInstance()->ScanPlugins(sPLDirectory + "/Plugins/", Recursive, m_bDelayedPluginLoading);
		}
	}

	// Write message into log
	PL_LOG(Info, String("Plugins loaded (required time: ") + cStopwatch.GetSeconds() + " sec)")
}

/**
*  @brief
*    Called when application should set it's data paths
*/
void ConsoleApplication::OnInitData()
{
	// Is '.' (= the current directory) already a base directory? If not, add it right now...
	LoadableManager *pLoadableManager = LoadableManager::GetInstance();
	if (!pLoadableManager->IsBaseDir("."))
		pLoadableManager->AddBaseDir(".");

	// Scan for packages in current "Data" directory
	LoadableManager::GetInstance()->ScanPackages(System::GetInstance()->GetCurrentDir() + "/Data/");

	// Is the application directory already a base directory? If not, add it right now...
	if (!pLoadableManager->IsBaseDir(m_cApplicationContext.GetAppDirectory()))
		pLoadableManager->AddBaseDir(m_cApplicationContext.GetAppDirectory());

	// Scan for packages in application's "Data" directory
	LoadableManager::GetInstance()->ScanPackages(m_cApplicationContext.GetAppDirectory() + "/Data/");

	// Use PixelLight runtime?
	if (m_bUseRuntime) {
		// Get PixelLight runtime directory
		String sPLDirectory = Core::GetRuntimeDirectory();
		if (sPLDirectory.GetLength()) {
			// Add runtime directory
			pLoadableManager->AddBaseDir(sPLDirectory + "/Data/");

			// Add packages from PixelLight runtime directory
			LoadableManager::GetInstance()->ScanPackages(sPLDirectory + "/Data/");
		}
	}

	// Get localization language (from config or from default)
	String sLanguage = m_cConfig.GetVar("PLCore::CoreGeneralConfig", "Language");
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
void ConsoleApplication::OnInit()
{
	// Reset timing class
	Timing::GetInstance()->Reset();
}

/**
*  @brief
*    Called when application should de-initialize itself
*/
void ConsoleApplication::OnDeInit()
{
	// No default implementation
}

/**
*  @brief
*    Function that is called when the program has been started for the first time
*/
void ConsoleApplication::OnFirstProgramStart()
{
	// Write message into log
	PL_LOG(Info, "First application start detected")
}

/**
*  @brief
*    Function that is called to display a help message about the application
*/
void ConsoleApplication::OnPrintHelp()
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
void ConsoleApplication::OnPrintVersion()
{
	// Print application title and version
	System::GetInstance()->GetConsole().Print(m_sTitle + " - V" + m_cVersion.ToString() + '\n');
}

/**
*  @brief
*    Function that is called when a signal has arrive
*/
bool ConsoleApplication::OnSignal(ESignal nSignal)
{
	// Catch signal
	switch(nSignal) {
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
void ConsoleApplication::SignalHandler(int nSignal)
{
	// Linux implementation
	#ifdef LINUX
		// Catch signal
		switch(nSignal) {
			// Interrupt (exit application by ctrl-c)
			case SIGINT:
				// Send signal to application
				if (!ConsoleApplication::GetApplication()->OnSignal(SignalInterrupt)) {
					// Ignore signal and restore handler
					signal(SIGINT, ConsoleApplication::SignalHandler);
				} else {
					// Signal handler has done it's job, re-raise signal
					signal(nSignal, SIG_DFL);
					raise(nSignal);
				}
				break;

			// Terminate (exit application)
			case SIGTERM:
				// Send signal to application
				if (!ConsoleApplication::GetApplication()->OnSignal(SignalTerm)) {
					// Ignore signal and restore handler
					signal(SIGTERM, ConsoleApplication::SignalHandler);
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
