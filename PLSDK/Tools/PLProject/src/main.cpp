/*********************************************************\
 *  File: main.cpp                                       *
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
#include <PLGeneral/Main.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/String/String.h>
#include <PLGeneral/String/RegEx.h>
#include <PLGeneral/Registry/Registry.h>
#include <PLCore/Core.h>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Module.h>
#include <PLCore/Tools/LocalizationLoaderPL.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LocalizationGroup.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;


//[-------------------------------------------------------]
//[ Externals                                             ]
//[-------------------------------------------------------]
extern bool Publish(const String &sTargetDirectory);


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// Output types
static const int MESSAGE	=  0;	/**< Message */
static const int STATUS		=  1;	/**< Status message */
static const int ERR		=  2;	/**< Error message */
static const int DEBUG		= 10;	/**< Debug message (only if debug mode is on) */


//[-------------------------------------------------------]
//[ Data types                                            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Project infos
*/
struct Project {
	String sPath;					/**< Path to project*/
	String sName;					/**< Project name */
	String sSuffix;					/**< Project suffix */
	String sModuleName;				/**< Module name (should be same as project name usually) */
	String sModuleVersion;			/**< Module version */
	String sModuleVendor;			/**< Vendor name */
	String sModuleLicense;			/**< License */
	String sModuleDescription;		/**< Module description */
	bool   bModulePlugin;			/**< Is the module a plugin? */
	bool   bModuleActive;			/**< Is the module active? */
	bool   bModuleDelayed;			/**< Is the module delayed? */
	String sLibWin32Release;		/**< Output file name for Win32 Release */
	String sLibWin32Debug;			/**< Output file name for Win32 Debug */
	String sLibWin64Release;		/**< Output file name for Win64 Release */
	String sLibWin64Debug;			/**< Output file name for Win64 Debug */
	String sLibLinuxRelease;		/**< Output file name for Linux Release */
	String sLibLinuxDebug;			/**< Output file name for Linux Debug */
	String sDependWin32Release;		/**< Dependencies for Win32 Release */
	String sDependWin32Debug;		/**< Dependencies for Win32 Debug */
	String sDependWin64Release;		/**< Dependencies for Win64 Release */
	String sDependWin64Debug;		/**< Dependencies for Win64 Debug */
	String sDependLinuxRelease;		/**< Dependencies for Linux Release */
	String sDependLinuxDebug;		/**< Dependencies for Linux Debug */
	String sMainSrc;				/**< Main source file */
	String sSourcePath;				/**< Directory containing the project's source files */
	String sIncludePath;			/**< Directory containing the project's include files */
	String sOutputPath;				/**< Path to output directory */
	String sOutputPlugin;			/**< Plugin output filename */
};


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
// Debug mode
bool g_bDebug = false;
// Verbose mode
bool g_bVerbose = false;


//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Output message
*/
void Message(int nType, const String &sMessage)
{
	// Print beginning of line
	if (nType == STATUS && !g_bVerbose) return;
	if (nType == DEBUG && !g_bDebug) return;
	if (nType == STATUS) System::GetInstance()->GetConsole().Print("-- ");
	if (nType == DEBUG)  System::GetInstance()->GetConsole().Print("** ");
	if (nType == ERR)    System::GetInstance()->GetConsole().Print("!! ");

	// Print message
	System::GetInstance()->GetConsole().Print(sMessage);
	System::GetInstance()->GetConsole().Print('\n');
}

/**
*  @brief
*    Write to file
*/
void Write(File &cFile, const String &sString)
{
	// Write string to file
	cFile.PutS(sString + '\n');

	// Debug output
	Message(DEBUG, sString);
}

/**
*  @brief
*    Check if an argument is a valid option
*/
bool IsOption(const String &sArgument)
{
	// Check if the argument is a known option
	return (sArgument == "--debug" ||
			sArgument == "--verbose" ||
			sArgument == "--suffix" ||
			sArgument == "--output-path" ||
			sArgument == "--write-plugin");
}

/**
*  @brief
*    Find files in a directory tree
*/
void Find(Array<String> &lstNames, const String &sPath, const String &sPattern, bool bRecursive)
{
	// Open directory
	Directory cDir(sPath);

	// Find files
	FileSearch cSearch(cDir, sPattern);
	while (cSearch.HasNextFile()) {
		String sFilename =  cSearch.GetNextFile();
		String sFile = sPath + '/' + sFilename;
		lstNames.Add(sFile);
	}

	// Recurse into subdirectories
	if (bRecursive) {
		FileSearch cSearch2(cDir);
		while (cSearch2.HasNextFile()) {
			String sFilename =  cSearch2.GetNextFile();
			String sFile = sPath + '/' + sFilename;
			if (FileObject(sFile).IsDirectory() && bRecursive && sFilename != "." && sFilename != "..") {
				Find(lstNames, sFile, sPattern, bRecursive);
			}
		}
	}
}

/**
*  @brief
*    Print out a list of strings
*/
void PrintList(int nType, const String &sPrefix, Array<String> &lstNames)
{
	// Loop through list
	Iterator<String> cIterator = lstNames.GetIterator();
	while (cIterator.HasNext()) {
		// Print string
		String sName = cIterator.Next();
		Message(nType, sPrefix + '\'' + sName + '\'');
	}
}

/**
*  @brief
*    Escape a string
*/
String EscapeString(const String &sValue)
{
	String sResult = sValue;
	sResult.Replace(':', "\\:");
	return sResult;
}

/**
*  @brief
*    Get quoted string
*/
String GetQuotedString(const String &sValue)
{
	String sResult;
	if (sValue.GetLength() > 2 && sValue.GetSubstring(0, 1) == '\"' && sValue.GetSubstring(sValue.GetLength()-1, 1) == '\"')
		sResult = sValue.GetSubstring(1, sValue.GetLength()-2);
	return sResult;
}


//[-------------------------------------------------------]
//[ Program functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parse all files of a project
*/
bool ParseFiles(Project &cProject, Array<String> &lstFiles)
{
	// This function does:
	// - Parse for comments like '//<<nodebug>>' and add information to the registry for Microsoft Visual Studio options
	// - Parse Text-Macros for localization

	// Setup regular expressions
	RegEx cRegExNoStepInto("\\w*<<nostepinto>>\\w*(?<exp>.*)\\w*$");
	RegEx cRegExStepInto  ("\\w*<<stepinto>>\\w*(?<exp>.*)\\w*$");
	RegEx cRegExI18n	  ("_TEXT\\(\\\"((\\w|\\s|[-!\"#$%&'()*+,./:;<=>?@[\\\\\\]_`{|}~]|(\\\"))*)\\\"\\)");
	LocalizationGroup *pLocalizationGroup = Localization::GetInstance()->AddGroup("test");

	// Loop through files
	Iterator<String> cIterator = lstFiles.GetIterator();
	while (cIterator.HasNext()) {
		// Parse file
		String sFilename = cIterator.Next();
		Message(STATUS, "Parsing source file at '" + sFilename + '\'');

		// Open file
		File cFile(sFilename);
		if (!cFile.Open(File::FileRead | File::FileText)) {
			Message(ERR, "Could not open file '" + sFilename + "'!");
			return false;
		}

		// Parse file
		while (!cFile.IsEof()) {
			// Read line
			String sLine = cFile.GetS();
			Message(DEBUG, sLine);

			// Check for <<nostepinto>>
			if (cRegExNoStepInto.Match(sLine)) {
				// Get expression
				String sExpression = cRegExNoStepInto.GetNameResult("exp");
				Message(STATUS, "NoStepInto: '" + sExpression + '\'');

				// Write to registry
				Registry cReg;
				String sValue = EscapeString(sExpression) + "=NoStepInto";
				if (cReg.Open(Registry::KeyLocalMachine, "SOFTWARE\\Microsoft\\VisualStudio\\10.0\\NativeDE\\StepOver",
								Registry::RegRead | Registry::RegWrite)) {
					cReg.SetValueString(sExpression, sValue);
					cReg.Close();
				}
			}

			// Check for <<stepinto>>
			if (cRegExStepInto.Match(sLine)) {
				// Get expression
				String sExpression = cRegExStepInto.GetNameResult("exp");
				Message(STATUS, "StepInto: '" + sExpression + '\'');

				// Write to registry
				Registry cReg;
				String sValue = EscapeString(sExpression) + "=NoStepInto";
				if (cReg.Open(Registry::KeyLocalMachine, "SOFTWARE\\Microsoft\\VisualStudio\\10.0\\NativeDE\\StepOver",
								Registry::RegRead | Registry::RegWrite)) {
					cReg.SetValueString(sExpression, sValue);
					cReg.Close();
				}
			}

			// Check for localization string
			if (cRegExI18n.Match(sLine)) {
				String sString = cRegExI18n.GetResult(0);
				Message(STATUS, "Localization String: '" + sString + '\'');
				pLocalizationGroup->AddText(sString, sString);
			}
		}

		// Close file
		cFile.Close();
	}

//	String sLocFile = cProject.sPath + "/test.loc";
//	pLocalizationGroup->Save(sLocFile);

	// Done
	return true;
}

/**
*  @brief
*    Parse main source file
*/
bool ParseModule(Project &cProject)
{
	// Parse main source file
	String sMainSrc = cProject.sMainSrc;
	Message(STATUS, "Parsing main source file at '" + sMainSrc + '\'');

	// Open file
	File cFile(sMainSrc);
	if (!cFile.Open(File::FileRead | File::FileText)) {
		Message(ERR, "Could not open file '" + sMainSrc + "'!");
		return false;
	}

	// Setup regular expressions
	RegEx cRegExModule("^\\s*pl_module\\(\\s*\\\"(?<name>\\w*)\\\"\\s*\\)\\s*$");
	RegEx cRegExModulePlugin("^\\s*pl_module_plugin\\(\\s*\\\"(?<name>\\w*)\\\"\\s*\\)\\s*$");
	RegEx cRegExVendor("^\\s*pl_module_vendor\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExLicense("^\\s*pl_module_license\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDescription("^\\s*pl_module_description\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExVersion("^\\s*pl_module_version\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDepsWin32Release("^\\s*pl_module_dependencies_win32_release\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDepsWin32Debug("^\\s*pl_module_dependencies_win32_debug\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDepsWin64Release("^\\s*pl_module_dependencies_win64_release\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDepsWin64Debug("^\\s*pl_module_dependencies_win64_debug\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDepsLinuxRelease("^\\s*pl_module_dependencies_linux_release\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDepsLinuxDebug("^\\s*pl_module_dependencies_linux_debug\\s*\\(\\s*(?<text>\".*\")\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExActive("^\\s*pl_module_active\\s*\\((?<num>\\d)\\)\\s*$");
	RegEx cRegExDelayed("^\\s*pl_module_delayed\\s*\\((?<num>\\d)\\)\\s*$");

	// Parse file
	while (!cFile.IsEof()) {
		// Read line
		String sLine = cFile.GetS();
		Message(DEBUG, sLine);

		// Check for pl_module
		if (cRegExModule.Match(sLine)) {
			cProject.sModuleName = cRegExModule.GetNameResult("name");
			cProject.bModulePlugin = false;
			Message(STATUS, "Module name = '" + cProject.sModuleName + '\'');
		}

		// Check for pl_module_plugin
		if (cRegExModulePlugin.Match(sLine)) {
			cProject.sModuleName = cRegExModulePlugin.GetNameResult("name");
			cProject.bModulePlugin = true;
			Message(STATUS, "Module name = '" + cProject.sModuleName + '\'');
			Message(STATUS, "This module is a plugin");
		}

		// Check for pl_module_vendor
		if (cRegExVendor.Match(sLine)) {
			cProject.sModuleVendor = GetQuotedString(cRegExVendor.GetNameResult("text"));
			Message(STATUS, "Vendor name = '" + cProject.sModuleVendor + '\'');
		}

		// Check for pl_module_license
		if (cRegExLicense.Match(sLine)) {
			cProject.sModuleLicense = GetQuotedString(cRegExLicense.GetNameResult("text"));
			Message(STATUS, "License = '" + cProject.sModuleLicense + '\'');
		}

		// Check for pl_module_description
		if (cRegExDescription.Match(sLine)) {
			cProject.sModuleDescription = GetQuotedString(cRegExDescription.GetNameResult("text"));
			Message(STATUS, "Description = '" + cProject.sModuleDescription + '\'');
		}

		// Check for pl_module_version
		if (cRegExVersion.Match(sLine)) {
			cProject.sModuleVersion = GetQuotedString(cRegExVersion.GetNameResult("text"));
			Message(STATUS, "Version = '" + cProject.sModuleVersion + '\'');
		}

		// Check for pl_module_dependencies_win32_release
		if (cRegExDepsWin32Release.Match(sLine)) {
			cProject.sDependWin32Release = GetQuotedString(cRegExDepsWin32Release.GetNameResult("text"));
			Message(STATUS, "Win32 release dependencies = '" + cProject.sDependWin32Release + '\'');
		}

		// Check for pl_module_dependencies_win32_debug
		if (cRegExDepsWin32Debug.Match(sLine)) {
			cProject.sDependWin32Debug = GetQuotedString(cRegExDepsWin32Debug.GetNameResult("text"));
			Message(STATUS, "Win32 debug dependencies = '" + cProject.sDependWin32Debug + '\'');
		}

		// Check for pl_module_dependencies_win64_release
		if (cRegExDepsWin64Release.Match(sLine)) {
			cProject.sDependWin64Release = GetQuotedString(cRegExDepsWin64Release.GetNameResult("text"));
			Message(STATUS, "Win64 release dependencies = '" + cProject.sDependWin64Release + '\'');
		}

		// Check for pl_module_dependencies_win64_debug
		if (cRegExDepsWin64Debug.Match(sLine)) {
			cProject.sDependWin64Debug = GetQuotedString(cRegExDepsWin64Debug.GetNameResult("text"));
			Message(STATUS, "Win64 debug dependencies = '" + cProject.sDependWin64Debug + '\'');
		}

		// Check for pl_module_dependencies_linux_release
		if (cRegExDepsLinuxRelease.Match(sLine)) {
			cProject.sDependLinuxRelease = GetQuotedString(cRegExDepsLinuxRelease.GetNameResult("text"));
			Message(STATUS, "Linux release dependencies = '" + cProject.sDependLinuxRelease + '\'');
		}

		// Check for pl_module_dependencies_linux_debug
		if (cRegExDepsLinuxDebug.Match(sLine)) {
			cProject.sDependLinuxDebug = GetQuotedString(cRegExDepsLinuxDebug.GetNameResult("text"));
			Message(STATUS, "Linux debug dependencies = '" + cProject.sDependLinuxDebug + '\'');
		}

		// Check for pl_module_active
		if (cRegExActive.Match(sLine)) {
			String sActive = cRegExActive.GetNameResult("num");
			cProject.bModuleActive = (sActive == "1");
			Message(STATUS, String("Active = '") + (cProject.bModuleActive ? "yes" : "no") + '\'');
		}

		// Check for pl_module_delayed
		if (cRegExDelayed.Match(sLine)) {
			String sDelayed = cRegExDelayed.GetNameResult("num");
			cProject.bModuleDelayed = (sDelayed == "1");
			Message(STATUS, String("Delayed = '") + (cProject.bModuleDelayed ? "yes" : "no") + '\'');
		}
	}

	// Close file
	cFile.Close();

	// Compose library names
	if (cProject.bModulePlugin) {
		// Compose file names
		cProject.sLibWin32Release	= cProject.sName + cProject.sSuffix + ".dll";
		cProject.sLibWin32Debug		= cProject.sName + cProject.sSuffix + "D.dll";
		cProject.sLibWin64Release	= cProject.sName + cProject.sSuffix + "64.dll";
		cProject.sLibWin64Debug		= cProject.sName + cProject.sSuffix + "D64.dll";
		cProject.sLibLinuxRelease	= "lib" + cProject.sName + cProject.sSuffix + ".so";
		cProject.sLibLinuxDebug		= "lib" + cProject.sName + cProject.sSuffix + "D.so";

		// Output file names
		Message(STATUS, "Win32 release library = '" + cProject.sLibWin32Release);
		Message(STATUS, "Win32 debug   library = '" + cProject.sLibWin32Debug);
		Message(STATUS, "Win64 release library = '" + cProject.sLibWin64Release);
		Message(STATUS, "Win64 debug   library = '" + cProject.sLibWin64Debug);
		Message(STATUS, "Linux release library = '" + cProject.sLibLinuxRelease);
		Message(STATUS, "Linux debug   library = '" + cProject.sLibLinuxDebug);
	}

	// Done
	return true;
}

/**
*  @brief
*    Parse a project source tree
*/
bool ParseProject(Project &cProject)
{
	// Parse project
	String sPath = cProject.sPath;
	Message(STATUS, "Parsing project at '" + sPath + '\'');

	// Find VC projects
	Message(STATUS, "Looking for project files");
	Array<String> lstProjects;
	Find(lstProjects, sPath, "*.vcxproj", false);
	PrintList(DEBUG, "found ", lstProjects);

	// Find out name of project
	String sName;
	Iterator<String> cIterator = lstProjects.GetIterator();
	while (cIterator.HasNext()) {
		String sFilename = Url(cIterator.Next()).GetFilename();
		Message(DEBUG, String("Project ") + '\'' + sFilename + '\'');
		if (sFilename.IndexOf("Stat") > -1) {
			Message(DEBUG, "This is a static lib version, ignoring ...");
		} else if (sFilename.IndexOf("Internal") > -1) {
			Message(DEBUG, "This is an internal project file, ignoring ...");
		} else {
			sName = Url(sFilename).CutExtension();
			Message(DEBUG, "Taking '" + sName + "' as project name");
		}
	}

	// Recognize suffix
	if (cProject.sSuffix.GetLength() > 0) {
		Message(STATUS, "Using project suffix '" + cProject.sSuffix + '\'');
	}

	// Check if a project name has been found
	if (sName.GetLength() > 0) {
		Message(STATUS, "Found project '" + sName + '\'');
		cProject.sName = sName;
	} else {
		Message(ERR, "Could not determine project name!");
		return false;
	}

	// Find main source file
	String sMainSrc = sPath + "/src/" + sName + ".cpp";
	if (FileObject(sMainSrc).Exists()) {
		Message(STATUS, "Found main source file '" + sMainSrc + '\'');
		cProject.sMainSrc = sMainSrc;
	} else {
		Message(ERR, "Could not determine main source file!");
		return false;
	}

	// Parse module file
	if (!ParseModule(cProject)) {
		// Error parsing module file
		return false;
	}

	// Find source files
	String sSourcePath = sPath + "/src";
	FileObject cSrcFile(sSourcePath);
	if (cSrcFile.Exists() && cSrcFile.IsDirectory()) {
		Message(STATUS, "Found source files at '" + sSourcePath + '\'');
		cProject.sSourcePath = sSourcePath;
	} else {
		Message(ERR, "Could not find source files in '" + sSourcePath + "'!");
		Message(ERR, cSrcFile.Exists() ? "File exists" : "File does not exist");
		Message(ERR, cSrcFile.IsDirectory() ? "File is a directory" : "File is not a directory");
		return false;
	}

	// Find include files
	String sIncludePath = sPath + "/include";
	FileObject cIncFile(sIncludePath);
	if (cIncFile.Exists() && cIncFile.IsDirectory()) {
		Message(STATUS, "Found include files at '" + sIncludePath + '\'');
	} else {
		Message(STATUS, "Could not find include files, taking '" + sSourcePath + '\'');
		sIncludePath = sSourcePath;
		cProject.sIncludePath = sIncludePath;
	}

	// Add all source, header and inline files
	Array<String> lstFiles;
	Find(lstFiles, sSourcePath, "*.cpp", true);
	Find(lstFiles, sIncludePath, "*.h", true);
	Find(lstFiles, sIncludePath, "*.inl", true);
	PrintList(DEBUG, "- Found file ", lstFiles);

	// And now, pass all these files :-)
	if (!ParseFiles(cProject, lstFiles)) {
		// Error parsing files
		return false;
	}

	// Done
	return true;
}

/**
*  @brief
*    Create plugin file for a project
*/
bool CreatePluginFile(Project &cProject)
{
	// Compose output filename
	cProject.sOutputPlugin = cProject.sOutputPath + '/' + cProject.sName + cProject.sSuffix + ".plugin";
	Message(STATUS, "Writing plugin file '" + cProject.sOutputPlugin + '\'');

	// Open plugin file
	File cFile(cProject.sOutputPlugin);
	if (cFile.Open(File::FileCreate | File::FileWrite | File::FileText)) {
		// Get the filename of the shared library
		String sSharedLibraryFilename;
		#ifdef WIN32
			#ifdef WIN64
				#ifdef _DEBUG
					sSharedLibraryFilename = cProject.sLibWin64Debug;
				#else
					sSharedLibraryFilename = cProject.sLibWin64Release;
				#endif
			#else
				#ifdef _DEBUG
					sSharedLibraryFilename = cProject.sLibWin32Debug;
				#else
					sSharedLibraryFilename = cProject.sLibWin32Release;
				#endif
			#endif
		#endif
		#ifdef LINUX
			#ifdef _DEBUG
				sSharedLibraryFilename = cProject.sLibLinuxDebug;
			#else
				sSharedLibraryFilename = cProject.sLibLinuxRelease;
			#endif
		#endif

		// Get the absolute filename of the shared library
		const Url cUrl(cProject.sOutputPlugin);
		const String sAbsSharedLibraryFilename = (cUrl.IsAbsolute() ? cUrl : (System::GetInstance()->GetCurrentDir() + '/' + cUrl.GetUrl())).CutFilename() + sSharedLibraryFilename;

		// Load the module
		// [TODO] Currently this solution is not working under Linux because the so file can't be loaded (delayed is set to 0)... uff, maybe it's really required to parse the cpp file...
		const Module *pModule = ClassManager::GetInstance()->LoadModule(sAbsSharedLibraryFilename);

		// Write plugin file
		Write(cFile, "<?xml version=\"1.0\" ?>");
		Write(cFile, "<Plugin Version=\"1\" PixelLightVersion=\"" + Core::GetVersion().ToString() + "\">");
		Write(cFile, String("	<Active>") + (cProject.bModuleActive ? "1" : "0") + "</Active>");
		Write(cFile, String("	<Delayed>") + (cProject.bModuleDelayed && pModule ? "1" : "0") + "</Delayed>");
		Write(cFile, "	<Name>" + cProject.sModuleName + "</Name>");

		// Version
		if (cProject.sModuleVersion.GetLength())
			Write(cFile, "	<Version>" + cProject.sModuleVersion + "</Version>");

		// Vendor
		if (cProject.sModuleVendor.GetLength())
			Write(cFile, "	<Vendor>" + cProject.sModuleVendor + "</Vendor>");

		// License
		if (cProject.sModuleLicense.GetLength())
			Write(cFile, "	<License>" + cProject.sModuleLicense + "</License>");

		// Description
		if (cProject.sModuleDescription.GetLength())
			Write(cFile, "	<Description>" + cProject.sModuleDescription + "</Description>");

		{ // Platform: Win32
			Write(cFile, "	<Platform Name=\"Win32\">");

			// Library: Release
			if (cProject.sDependWin32Release.GetLength())
				Write(cFile, "		<Library Type=\"Release\" Dependency=\"" + cProject.sDependWin32Release + "\">" + cProject.sLibWin32Release + "</Library>");
			else
				Write(cFile, "		<Library Type=\"Release\">" + cProject.sLibWin32Release + "</Library>");

			// Library: Debug
			if (cProject.sDependWin32Debug.GetLength())
				Write(cFile, "		<Library Type=\"Debug\" Dependency=\"" + cProject.sDependWin32Debug + "\">" + cProject.sLibWin32Debug + "</Library>");
			else
				Write(cFile, "		<Library Type=\"Debug\">" + cProject.sLibWin32Debug + "</Library>");

			// Platform end tag
			Write(cFile, "	</Platform>");
		}

		{ // Platform: Win64
			Write(cFile, "	<Platform Name=\"Win64\">");

			// Library: Release
			if (cProject.sDependWin64Release.GetLength())
				Write(cFile, "		<Library Type=\"Release\" Dependency=\"" + cProject.sDependWin64Release + "\">" + cProject.sLibWin64Release + "</Library>");
			else
				Write(cFile, "		<Library Type=\"Release\">" + cProject.sLibWin64Release + "</Library>");

			// Library: Debug
			if (cProject.sDependWin64Debug.GetLength())
				Write(cFile, "		<Library Type=\"Debug\" Dependency=\"" + cProject.sDependWin64Debug + "\">" + cProject.sLibWin64Debug + "</Library>");
			else
				Write(cFile, "		<Library Type=\"Debug\">" + cProject.sLibWin64Debug + "</Library>");

			// Platform end tag
			Write(cFile, "	</Platform>");
		}

		{ // Platform: Linux
			Write(cFile, "	<Platform Name=\"Linux\">");

			// Library: Release
			if (cProject.sDependLinuxRelease.GetLength())
				Write(cFile, "		<Library Type=\"Release\" Dependency=\"" + cProject.sDependLinuxRelease + "\">" + cProject.sLibLinuxRelease + "</Library>");
			else
				Write(cFile, "		<Library Type=\"Release\">" + cProject.sLibLinuxRelease + "</Library>");

			// Library: Debug
			if (cProject.sDependLinuxDebug.GetLength())
				Write(cFile, "		<Library Type=\"Debug\" Dependency=\"" + cProject.sDependLinuxDebug   + "\">" + cProject.sLibLinuxDebug   + "</Library>");
			else
				Write(cFile, "		<Library Type=\"Debug\">" + cProject.sLibLinuxDebug + "</Library>");

			// Platform end tag
			Write(cFile, "	</Platform>");
		}

		// Classes
		if (pModule) {
			// Get classes of module
			const List<const Class*> &lstClasses = pModule->GetClasses();
			if (lstClasses.GetNumOfElements()) {
				// Classes start tag
				Write(cFile, "	<Classes>");

				// Iterate through all classes
				Iterator<const Class*> cIterator = lstClasses.GetIterator();
				while (cIterator.HasNext()) {
					// Get the class instance
					const Class *pClass = cIterator.Next();

					// Class start tag
					Write(cFile, String("		<Class Name=\"") + pClass->GetName() + "\" Namespace=\"" + pClass->GetNamespace() + "\" BaseClassName=\"" + pClass->GetBaseClassName() + "\" Description=\"" + pClass->GetDescription() + "\" HasConstructor=\"" + pClass->HasConstructor() + "\" HasDefaultConstructor=\"" + pClass->HasDefaultConstructor() + "\">");

					{ // Properties
						const HashMap<String, String> &mapProperties = pClass->GetProperties();
						if (mapProperties.GetNumOfElements()) {
							// Properties start tag
							Write(cFile, "			<Properties>");

							// Iterate over all RTTI class properties
							Iterator<String> cIterator = pClass->GetProperties().GetKeyIterator();
							while (cIterator.HasNext()) {
								// Get the name of the current property
								const String sName = cIterator.Next();

								// Get the value of the current property
								const String sValue = pClass->GetProperties().Get(sName);

								// Write down the property
								Write(cFile, String("				<Property Name=\"") + sName + "\">" + sValue + "</Property>");
							}

							// Properties end tag
							Write(cFile, "			</Properties>");
						}
					}

					// Class end tag
					Write(cFile, "		</Class>");
				}

				// Classes end tag
				Write(cFile, "	</Classes>");
			}
		}

		// Plugin end tag
		Write(cFile, "</Plugin>");

		cFile.Close();
		return true;
	} else {
		// Close not open file
		Message(ERR, "Could not write to file!");
		return false;
	}
}


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sFilename, const Array<String> &lstArguments)
{
	// [HACK] Force the linker to keep this class!
	LocalizationLoaderPL cHack;

	// Output startup info
	Message(MESSAGE, "PLProject " + Core::GetVersion().ToString());
	Message(MESSAGE, "Current dir is '" + System::GetInstance()->GetCurrentDir() + '\'');

	// Parse command line
	String sPath;
	String sOutputPath;
	String sSuffix;
	bool bWritePlugin = false;
	bool bError = false;
	if (lstArguments.GetNumOfElements() > 0) {
		// Get path to project
		sPath = lstArguments[0];

		if (!IsOption(sPath)) {
			// Parse other argument
			for (uint32 i=1; i<lstArguments.GetNumOfElements() && !bError; i++) {
				String sArgument = lstArguments[i];
				if (IsOption(sArgument)) {
					if (sArgument == "--debug") {
						// Set debug mode
						g_bDebug = true;
					} else if (sArgument == "--verbose") {
						// Set verbose mode
						g_bVerbose = true;
					} else if (sArgument == "--suffix") {
						// Get project suffix
						sSuffix = '-' + lstArguments[i+1];
						if (i+1 >= lstArguments.GetNumOfElements() || IsOption(sSuffix)) bError = true;
						i++;
					} else if (sArgument == "--output-path") {
						// Get output path
						sOutputPath = lstArguments[i+1];
						if (i+1 >= lstArguments.GetNumOfElements() || IsOption(sOutputPath)) bError = true;
						i++;

						// If there's a slash or backslash at the end of the output path, remove it
						const uint32 nLastCharacter = sOutputPath.GetLength() - 1;
						if (sOutputPath[nLastCharacter] == '\\' || sOutputPath[nLastCharacter] == '/')
							sOutputPath.Delete(nLastCharacter);
					} else if (sArgument == "--write-plugin") {
						// Write plugin file
						bWritePlugin = true;
					}
				} else bError = true;
			}
		} else bError = true;
	} else bError = true;

	// [DEBUG] Static options
	/*
		// Ignore command line
		bError = false;

		// Path
		sPath = "C:\\workspace\\projekte\\PixelLight\\PLEngine\\PLSoundOpenAL";
		// sPath = "C:\\workspace\\projekte\\PixelLight\\PLBase\\PLMath";
		// sPath = "C:\\workspace\\projekte\\PixelLight\\Lab\\BaseTest";

		// Suffix
		sSuffix = "-dev";

		// Output path
		sOutputPath = "C:\\workspace\\projekte\\PixelLight\\Bin\\PLRuntime\\Plugins\\PLSound";

		// Write plugin
		bWritePlugin = true;

		// Debug
		// g_bDebug = true;
	*/

	// Were all command line arguments valid?
	if (!bError) {
		// Parse project
		Project cProject;
		cProject.sPath          = sPath;
		cProject.sSuffix        = sSuffix;
		cProject.bModulePlugin  = false;
		cProject.bModuleActive  = true; // By default, projects are active
		cProject.bModuleDelayed = true; // By default, projects are delayed
		if (ParseProject(cProject)) {
			// Write plugin file
			if (bWritePlugin && sOutputPath.GetLength() > 0) {
				cProject.sOutputPath = sOutputPath;
				if (!CreatePluginFile(cProject)) return 1;
			}
		} else {
			// If we just start PLProject with a path to a directory -> perform publish
			// -> This way, we can just 'drop' a directory over PLProject in order to publish the project within this directory

			// Publish
			Publish(sPath);
		}
	} else {
		// Output help
		Message(MESSAGE, "");
		Message(MESSAGE, "Usage:");
		Message(MESSAGE, "  PLProject <path> [--write-plugin] [--output-path <filename>] [--suffix <suffix>] [--debug] [--verbose]");
		Message(MESSAGE, "");

		// Error!
		return 1;
	}

	// Done
	return 0;
}
