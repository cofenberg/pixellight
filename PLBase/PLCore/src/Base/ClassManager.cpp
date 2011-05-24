/*********************************************************\
 *  File: ClassManager.cpp                               *
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
#include <PLGeneral/System/System.h>
#include "PLGeneral/System/DynLib.h"
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/Log/Log.h>
#include "PLCore/Tools/Loader.h"
#include "PLCore/Base/Module.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/Rtti.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Global definitions                                    ]
//[-------------------------------------------------------]
// Plugin API functions
typedef bool (*PLIsPluginDebugBuildFunc) ();
typedef int  (*PLGetPluginInfoFunc) ();


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get all registered modules
*/
const List<const Module*> &ClassManager::GetModules() const
{
	// Return module list
	return m_lstModules;
}

/**
*  @brief
*    Get module by ID
*/
const Module *ClassManager::GetModule(uint32 nModuleID) const
{
	// Get module with given ID (can be a null pointer)
	return m_mapModules.Get(nModuleID);
}

/**
*  @brief
*    Scan a directory for compatible plugins and load them in
*/
bool ClassManager::ScanPlugins(const String &sPath, ERecursive nRecursive)
{
	// Get URL from path
	Url cUrl(sPath);
	if (!cUrl.IsDirectory())
		cUrl = sPath + '/';
	const String sUrl = cUrl.GetUrl();

	// Open directory
	Directory cDir(sUrl);
	if (cDir.Exists() && cDir.IsDirectory()) {
		// List files
		FileSearch cSearch(sUrl);
		while (cSearch.HasNextFile()) {
			// Get filename
			const String sFilename = cSearch.GetNextFile();
			if (sFilename != "." && sFilename != "..") {
				// Get absolute filename
				const String sFile = sUrl + sFilename;

				// Check extension
				const String sExtension = Url(sFile).GetExtension();
				if (sExtension == "plugin") {
					// Try to load plugin
					LoadPlugin(sFile);

				// Scan recursively?
				} else if (nRecursive == Recursive) {
					// Check if this is a directory
					File cFile(sFile);
					if (cFile.Exists() && cFile.IsDirectory()) {
						// Scan sub-directory
						ScanPlugins(sFile, nRecursive);
					}
				}
			}
		}

		// Return success
		return true;
	}

	// Error! Couldn't open directory
	return false;
}

/**
*  @brief
*    Load plugin
*/
bool ClassManager::LoadPlugin(const String &sFilename)
{
	// Get URL
	const Url cUrl = Url(sFilename);

	// Check file extension
	const String sExtension = cUrl.GetExtension();
	if (sExtension == "plugin") {
		// Load XML document
		XmlDocument cDocument;
		if (cDocument.Load(sFilename)) {
			// Get plugin element
			const XmlElement *pPluginElement = cDocument.GetFirstChildElement("Plugin");
			if (pPluginElement) {
				// Get format version
				const int nVersion = pPluginElement->GetAttribute("Version").GetInt();

				// Unkown
				if (nVersion > 1) {
					PL_LOG(Error, cDocument.GetValue() + ": " + Loader::UnknownFormatVersion)

				// 1 (current) or ""/0 (same format as 1)
				} else if (nVersion == 1 || nVersion == 0) {
					// [DEPRECATED]
					if (nVersion == 0)
						PL_LOG(Warning, cDocument.GetValue() + ": " + Loader::DeprecatedFormatVersion)

					// Load in the plugin
					return LoadPluginV1(cUrl, *pPluginElement);

				// No longer supported format version
				} else if (nVersion >= 0) {
					PL_LOG(Warning, cDocument.GetValue() + ": " + Loader::NoLongerSupportedFormatVersion)

				// Invalid format version (negative!)
				} else {
					PL_LOG(Error, cDocument.GetValue() + ": " + Loader::InvalidFormatVersion)
				}
			} else {
				PL_LOG(Error, "Can't find 'Plugin' element")
			}
		} else {
			PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Unload plugin
*/
bool ClassManager::UnloadPlugin(Module *pModule)
{
	// Is the module valid and a plugin?
	if (pModule && m_lstModules.IsElement(pModule) && pModule->IsPlugin()) {
		// Remove module
		UnregisterModule(pModule);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Unload all plugins
*/
bool ClassManager::UnloadAllPlugins()
{
	// Iterate through modules
	bool bError = false;
	for (uint32 i=0; i<m_lstModules.GetNumOfElements(); i++) {
		// Is that module a plugin?
		Module *pModule = const_cast<Module*>(m_lstModules[i]);
		if (pModule->IsPlugin()) {
			// Unload plugin
			if (!UnloadPlugin(pModule))
				bError = true;

			// As the module has been removed from the list, adjust counter variable
			i--;
		}
	}

	// Done
	return !bError;
}

/**
*  @brief
*    Get all registered classes
*/
const List<const Class*> &ClassManager::GetClasses() const
{
	// Return class list
	return m_lstClasses;
}

/**
*  @brief
*    Get classes based on their base class and/or module (search for classes)
*/
void ClassManager::GetClasses(List<const Class*> &lstClasses, const String &sClass, ERecursive nRecursive, EIncludeBase nIncludeBase, EIncludeAbstract nIncludeAbstract, PLGeneral::uint32 nModuleID) const
{
	// Iterate through classes
	Iterator<const Class*> cIterator = m_lstClasses.GetIterator();
	while (cIterator.HasNext()) {
		// Get class
		const Class *pClass = cIterator.Next();

		// Check base class
		if ( (sClass.GetLength() == 0) ||											// All classes wanted
			 (pClass->GetClassName() == sClass && nIncludeBase == IncludeBase) ||	// Base class itself
			 (pClass->GetBaseClassName() == sClass) ||								// Directly derived class
			 (nRecursive == Recursive && pClass->IsDerivedFrom(sClass))				// Derived class (recursive)
		   ) {
			// Only add classes of a specific module?
			if (nModuleID == 0 || (pClass->GetModule()->GetModuleID() == nModuleID)) {
				// Only add classes with a constructor?
				if (nIncludeAbstract == IncludeAbstract || pClass->HasConstructor()) {
					// Add class to list
					lstClasses.Add(pClass);
				}
			}
		}
	}
}

/**
*  @brief
*    Get class
*/
const Class *ClassManager::GetClass(const String &sClass) const
{
	// Get class
	return m_mapClasses.Get(sClass);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ClassManager::ClassManager() :
	m_nModuleID(10000)
{
}

/**
*  @brief
*    Destructor
*/
ClassManager::~ClassManager()
{
	// Clear list
	m_lstClasses.Clear();
}

/**
*  @brief
*    Get a unique module ID
*/
uint32 ClassManager::GetUniqueModuleID()
{
	// Return next module ID
	return m_nModuleID++;
}

/**
*  @brief
*    Create module
*/
Module *ClassManager::CreateModule(uint32 nModuleID)
{
	// Check if module is already there
	Module *pModule = const_cast<Module*>(m_mapModules.Get(nModuleID));
	if (!pModule) {
		// No, create new module
		pModule = new Module(nModuleID);

		// Add module to lists
		m_lstModules.Add(pModule);
		m_mapModules.Add(nModuleID, pModule);
	}

	// Return module
	return pModule;
}

/**
*  @brief
*    Register module
*/
void ClassManager::RegisterModule(uint32 nModuleID, const String &sName, const String &sVendor, const String &sLicense, const String &sDescription)
{
	// Get module
	Module *pModule = CreateModule(nModuleID);
	if (pModule) {
		// Set module info
		pModule->SetModuleInfo(sName, sVendor, sLicense, sDescription);

		// Module has been registered (emit event)
		EventModuleLoaded(pModule);
	}
}

/**
*  @brief
*    Unregister module
*/
void ClassManager::UnregisterModule(Module *pModule)
{
	// Check if module is valid
	if (pModule) {
		if (m_lstModules.IsElement(pModule)) {
			// Get list of classes (make a copy!)
			List<const Class*> lstClasses = pModule->GetClasses();

			// Remove all classes from that module
			Iterator<const Class*> cIterator = lstClasses.GetIterator();
			while (cIterator.HasNext())
				UnregisterClass(pModule->GetModuleID(), const_cast<Class*>(cIterator.Next()));
		}

		// Module has been unloaded (emit event)
		EventModuleUnloaded(pModule);

		// Remove module
		m_lstModules.Remove(pModule);
		m_mapModules.Remove(pModule->GetModuleID());
		delete pModule;
	}
}

/**
*  @brief
*    Register class
*/
void ClassManager::RegisterClass(uint32 nModuleID, Class *pClass)
{
	// Get module
	Module *pModule = CreateModule(nModuleID);

	// Check for duplicate class name
	const Class *pOldClass = m_mapClasses.Get(pClass->GetClassName());
	if (pOldClass) {
		// The class has a name that is already used by another class
		String sClass	  = pClass->GetClassName();
		String sModule	  = pModule->GetName();
		String sOldModule = pOldClass->GetModule()->GetName();

		// Add warning to log that the class will not be available through e.g. GetClass()
		PL_LOG(Warning, "Class '" + sClass + "' [module '" + sModule + "']: Name conflict with already registered class '" + sClass + "' [module '" + sOldModule + "']");
	}

	// Add class to list
	m_lstClasses.Add(pClass);
	if (!pOldClass)
		m_mapClasses.Add(pClass->GetClassName(), pClass);

	// Add class to module
	pModule->AddClass(pClass);

	// Class has been registered (emit event)
	EventClassLoaded(pClass);
}

/**
*  @brief
*    Unregister class
*/
void ClassManager::UnregisterClass(uint32 nModuleID, Class *pClass)
{
	// Get module
	Module *pModule = CreateModule(nModuleID);

	// Remove class from list
	m_lstClasses.Remove(pClass);
	m_mapClasses.Remove(pClass->GetClassName());

	// Remove class from module
	pModule->RemoveClass(pClass);

	// Class has been unloaded (emit event)
	EventClassUnloaded(pClass);
}

/**
*  @brief
*    Load file format version 1 plugin
*/
bool ClassManager::LoadPluginV1(const Url &cUrl, const XmlElement &cPluginElement)
{
	// Is plugin active?
	const XmlNode *pNode = cPluginElement.GetFirstChild("Active");
	if (pNode) {
		// Get node value
		const XmlNode *pValue = pNode->GetFirstChild();
		if (pValue && pValue->GetType() == XmlNode::Text) {
			const String sValue = pValue->GetValue();
			if (sValue.GetLength() && !sValue.GetBool()) {
				// Plugin is inactive
				PL_LOG(Info, cUrl.GetUrl() + ": Plugin is ignored because it's inactive")
				return false;
			}
		}
	}

	// Get plugin directory
	const String sPluginDirectory = cUrl.CutFilename();

	// By default, we do not force a build type match
	bool bForceBuildTypeMatch = false;

	// Iterate through all children and collect plugin meta information
	const XmlElement *pElement = cPluginElement.GetFirstChildElement();
	while (pElement) {
		// Get node name
		const String sNodeName = pElement->GetValue();

		// ForceBuildTypeMatch
		if (sNodeName == "ForceBuildTypeMatch") {
			// Get the value of the node
			const XmlNode *pValue = pElement->GetFirstChild();
			if (pValue && pValue->GetType() == XmlNode::Text) {
				const String sValue = pValue->GetValue();
				if (sValue.GetLength())
					bForceBuildTypeMatch = sValue.GetBool();
			}

		// Platform
		} else if (sNodeName == "Platform") {
			// Get platform name
			const String sPlatformName = pElement->GetAttribute("Name");

			// Platform match?
			if (sPlatformName.GetLength() && sPlatformName == System::GetInstance()->GetPlatform()) {
				const XmlElement *pPlatformElement = pElement->GetFirstChildElement();
				while (pPlatformElement) {
					// Get platform node name
					const String sPlatformNodeName = pPlatformElement->GetValue();

					// Library
					if (sPlatformNodeName == "Library") {
						// Get node value
						const XmlNode *pValue = pPlatformElement->GetFirstChild();
						if (pValue && pValue->GetType() == XmlNode::Text) {
							const String sValue = pValue->GetValue();
							if (sValue.GetLength()) {
								// Get type
								const String sType = pPlatformElement->GetAttribute("Type");

								// If we don't use this variable, we may receive a "conditional expression is constant"-warning (4127) from VC
								bool bDebugMode = PLCORE_IS_DEBUGMODE;
								if ((bDebugMode && sType == "Debug") || (!bDebugMode && sType == "Release")) {
									// Get absolute filename
									const String sAbsFilename = Url(sValue).IsAbsolute() ? sValue : sPluginDirectory + sValue;

									// Check if that library is already loaded
									bool bLibAlreadyLoaded = false;
									Iterator<const Module*> cIterator = m_lstModules.GetIterator();
									while (!bLibAlreadyLoaded && cIterator.HasNext()) {
										const Module *pModule = cIterator.Next();
										if (pModule->GetFilename() == sAbsFilename)
											bLibAlreadyLoaded = true;
									}

									// Library already loaded?
									if (!bLibAlreadyLoaded)
										LoadPluginLibrary(cUrl, sAbsFilename, bForceBuildTypeMatch);
								}
							}
						}
					}

					// Next element, please
					pPlatformElement = pPlatformElement->GetNextSiblingElement();
				}
			}
		}

		// Next element, please
		pElement = pElement->GetNextSiblingElement();
	}

	// Done
	return true;
}

/**
*  @brief
*    Load a plugin library
*/
void ClassManager::LoadPluginLibrary(const Url &cUrl, const String &sAbsFilename, bool bForceBuildTypeMatch)
{
	// Is the library existent?
	File cFile(sAbsFilename);
	if (cFile.Exists() && cFile.IsFile()) {
		// Load library
		DynLib *pDynLib = new DynLib();
		if (pDynLib->Load(sAbsFilename)) {
			bool bUseLibrary = true;

			// Check build type match
			if (bForceBuildTypeMatch) {
				PLIsPluginDebugBuildFunc pIsPluginDebugBuild = reinterpret_cast<PLIsPluginDebugBuildFunc>(pDynLib->GetSymbol("PLIsPluginDebugBuild"));
				if (pIsPluginDebugBuild) {
					if (PLCORE_IS_DEBUGMODE != pIsPluginDebugBuild()) {
						// Error!
						bUseLibrary = false;
						PL_LOG(Error, cUrl.GetUrl() + ": Plugin library '" + sAbsFilename + "': Release/debug missmatch")
					}
				} else {
					// Error!
					bUseLibrary = false;
					PL_LOG(Error, cUrl.GetUrl() + ": Plugin library '" + sAbsFilename + "': Forced build type match is active, but there's no 'PLIsPluginDebugBuild' function!")
				}
			}

			// Check if it is a valid PL plugin library
			if (bUseLibrary) {
				bUseLibrary = false;
				const String sLibraryFilename = Url(sAbsFilename).GetFilename();
				PLGetPluginInfoFunc pGetPluginInfo = reinterpret_cast<PLGetPluginInfoFunc>(pDynLib->GetSymbol("PLGetPluginInfo"));
				if (pGetPluginInfo) {
					// Get plugin info
					const int nModuleID = pGetPluginInfo();
					if (nModuleID > 0) {
						// Library successfully loaded
						PL_LOG(Info, cUrl.GetUrl() + ": Plugin library '" + sLibraryFilename + "' successfully loaded")
						Module *pModule = CreateModule(nModuleID);
						if (pModule) {
							// Set plugin information
							pModule->m_bPlugin	 = true;
							pModule->m_pDynLib   = pDynLib;
							pModule->m_sFilename = sAbsFilename;
							bUseLibrary = true;
						} else {
							// Error!
							PL_LOG(Error, cUrl.GetUrl() + ": Plugin library '" + sLibraryFilename + "': failed to create the module")
						}
					} else {
						// Error!
						PL_LOG(Error, cUrl.GetUrl() + ": Plugin library '" + sLibraryFilename + "': release/debug missmatch")
					}
				} else {
					// Error!
					PL_LOG(Error, cUrl.GetUrl() + ": The plugin library '" + sLibraryFilename + "' is no valid PixelLight plugin library")
				}
			}

			// Unload library if it is not used
			if (!bUseLibrary) {
				pDynLib->Unload();
				delete pDynLib;
			}
		} else {
			// Error!
			PL_LOG(Error, cUrl.GetUrl() + ": Can't load the plugin library '" + sAbsFilename + '\'')
			delete pDynLib;
		}
	} else {
		// Error!
		PL_LOG(Error, cUrl.GetUrl() + ": Can't find the plugin library '" + sAbsFilename + '\'')
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
