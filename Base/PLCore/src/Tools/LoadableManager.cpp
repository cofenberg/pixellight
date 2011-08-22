/*********************************************************\
 *  File: LoadableManager.cpp                            *
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
#include "PLCore/Log/Log.h"
#include "PLCore/File/Url.h"
#include "PLCore/File/File.h"
#include "PLCore/File/Directory.h"
#include "PLCore/File/FileSearch.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Tools/Loader.h"
#include "PLCore/Tools/LoadableType.h"
#include "PLCore/Tools/LoadableManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of loadable types
*/
uint32 LoadableManager::GetNumOfTypes()
{
	RegisterClasses();
	return m_lstTypes.GetNumOfElements();
}

/**
*  @brief
*    Returns a loadable type by using an index
*/
LoadableType *LoadableManager::GetTypeByIndex(uint32 nIndex)
{
	RegisterClasses();
	return m_lstTypes.Get(nIndex);
}

/**
*  @brief
*    Returns a loadable type by using it's name
*/
LoadableType *LoadableManager::GetTypeByName(const String &sName)
{
	RegisterClasses();
	return m_mapTypes.Get(sName);
}

/**
*  @brief
*    Returns a loadable type by using a loadable extension
*/
LoadableType *LoadableManager::GetTypeByExtension(const String &sExtension)
{
	RegisterClasses();
	return m_mapTypesByExtension.Get(sExtension);
}

/**
*  @brief
*    Returns the number of loaders
*/
uint32 LoadableManager::GetNumOfLoaders()
{
	RegisterClasses();
	return m_lstLoaders.GetNumOfElements();
}

/**
*  @brief
*    Returns a loader by using an index
*/
Loader *LoadableManager::GetLoaderByIndex(uint32 nIndex)
{
	RegisterClasses();
	return m_lstLoaders.Get(nIndex);
}

/**
*  @brief
*    Returns a loader by using a extension
*/
Loader *LoadableManager::GetLoaderByExtension(const String &sExtension)
{
	RegisterClasses();
	return m_mapLoaders.Get(sExtension);
}

/**
*  @brief
*    Returns the number of supported formats
*/
uint32 LoadableManager::GetNumOfFormats()
{
	RegisterClasses();
	return m_lstFormats.GetNumOfElements();
}

/**
*  @brief
*    Returns a supported format
*/
String LoadableManager::GetFormat(uint32 nIndex)
{
	RegisterClasses();
	return m_lstFormats.Get(nIndex);
}

/**
*  @brief
*    Returns whether loading is supported for the given format
*/
bool LoadableManager::IsFormatLoadSupported(const String &sExtension, const String &sType)
{
	RegisterClasses();
	if (sType.GetLength()) {
		const LoadableType *pLoadableType = GetTypeByName(sType);
		if (pLoadableType) {
			const Loader *pLoader = pLoadableType->GetLoaderByExtension(sExtension);
			if (pLoader)
				return pLoader->CanLoad();
		}
	} else {
		const Loader *pLoader = GetLoaderByExtension(sExtension);
		if (pLoader)
			return pLoader->CanLoad();
	}

	// Loading is not supported for the given format
	return false;
}

/**
*  @brief
*    Returns whether saving is supported for the given format
*/
bool LoadableManager::IsFormatSaveSupported(const String &sExtension, const String &sType)
{
	RegisterClasses();
	if (sType.GetLength()) {
		const LoadableType *pLoadableType = GetTypeByName(sType);
		if (pLoadableType) {
			const Loader *pLoader = pLoadableType->GetLoaderByExtension(sExtension);
			if (pLoader)
				return pLoader->CanSave();
		}
	} else {
		const Loader *pLoader = GetLoaderByExtension(sExtension);
		if (pLoader)
			return pLoader->CanSave();
	}

	// Saving is not supported for the given format
	return false;
}

/**
*  @brief
*    Returns the number of base directories
*/
uint32 LoadableManager::GetNumOfBaseDirs() const
{
	return m_lstBaseDirs.GetNumOfElements();
}

/**
*  @brief
*    Returns one of the base directories
*/
String LoadableManager::GetBaseDir(uint32 nNum) const
{
	// Get directory
	return m_lstBaseDirs[nNum];
}

/**
*  @brief
*    Checks whether the given path is a base directory
*/
bool LoadableManager::IsBaseDir(const String &sPath) const
{
	// Correct path
	String sValidUrl = Url(sPath).GetUrl();
	if (!Url(sValidUrl).IsDirectory())
		sValidUrl += '/';

	// Loop through all base directories
	for (uint32 i=0; i<m_lstBaseDirs.GetNumOfElements(); i++) {
		if (m_lstBaseDirs[i] == sValidUrl)
			return true; // This is a base directory
	}

	// Done, the given path is no base directory
	return false;
}

/**
*  @brief
*    Adds a base directory
*/
bool LoadableManager::AddBaseDir(const String &sPath)
{
	// Correct path
	String sValidUrl = Url(sPath).GetUrl();
	if (!Url(sValidUrl).IsDirectory())
		sValidUrl += '/';

	// Check whether the given base directory is already registered
	for (uint32 i=0; i<m_lstBaseDirs.GetNumOfElements(); i++) {
		if (m_lstBaseDirs[i] == sValidUrl)
			return true; // Done
	}

	// Add directory
	m_lstBaseDirs.Add(sValidUrl);
	return true; // Done
}

/**
*  @brief
*    Set the priority of base directories
*/
bool LoadableManager::SetBaseDirPriority(const String &sFirstPath, const String &sSecondPath)
{
	// Check parameters
	if (sFirstPath == sSecondPath)
		return true; // Done

	// Correct paths
	String sValidFirst  = Url(sFirstPath).GetUrl();
	if (!Url(sValidFirst).IsDirectory())
		sValidFirst += '/';
	String sValidSecond = Url(sSecondPath).GetUrl();
	if (!Url(sValidSecond).IsDirectory())
		sValidSecond += '/';

	// Get the first path
	for (uint32 nFirst=0; nFirst<m_lstBaseDirs.GetNumOfElements(); nFirst++) {
		const String &sFirstDirectory = m_lstBaseDirs[nFirst];
		if (sFirstDirectory == sValidFirst) {
			// Get the second path
			for (uint32 nSecond=0; nSecond<m_lstBaseDirs.GetNumOfElements(); nSecond++) {
				const String &sSecondDirectory = m_lstBaseDirs[nSecond];
				if (sSecondDirectory == sValidSecond) {
					// Already in order?
					if (nFirst > nSecond) {
						// Remove the first one
						m_lstBaseDirs.RemoveAtIndex(nFirst);

						// The first one replaces the second one
						m_lstBaseDirs.ReplaceAtIndex(nSecond, sValidFirst);

						// Add the second one directly after the first one
						m_lstBaseDirs.AddAtIndex(sValidSecond, nSecond + 1);
					}

					// Done
					return true;
				}
			}
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Remove a base directory
*/
bool LoadableManager::RemoveBaseDir(const String &sPath)
{
	// Correct path
	String sValidUrl = Url(sPath).GetUrl();
	if (!Url(sValidUrl).IsDirectory())
		sValidUrl += '/';

	// Search for base directory
	ConstIterator<String> cIterator = m_lstBaseDirs.GetConstIterator();
	while (cIterator.HasNext()) {
		// Check directory name
		const String &sDir = cIterator.Next();
		if (sValidUrl == sDir) {
			// Remove directory
			m_lstBaseDirs.Remove(sDir);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Remove a base directory
*/
bool LoadableManager::RemoveBaseDir(uint32 nNum)
{
	// Get directory
	String &sDir = m_lstBaseDirs[nNum];
	if (&sDir != &Array<String>::Null) {
		// Remove directory
		m_lstBaseDirs.Remove(sDir);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Removes all base directories
*/
bool LoadableManager::ClearBaseDirs()
{
	// Delete all base dirs
	m_lstBaseDirs.Clear();

	// Done
	return true;
}

/**
*  @brief
*    Gets the relative version of an absolute filename
*/
String LoadableManager::GetRelativeFilename(const String &sFilename)
{
	// Get file extension
	RegisterClasses();
	const String sExtension = Url(sFilename).GetExtension();
	if (sExtension.GetLength()) {
		// Get the loadable type
		const LoadableType *pLoadableType = m_mapTypesByExtension.Get(sExtension);
		if (pLoadableType)
			return pLoadableType->GetRelativeFilePath(sFilename);
	}

	// Error!
	return "";
}

/**
*  @brief
*    Scan a directory for data packages and add them as base paths to the loadable manager
*/
bool LoadableManager::ScanPackages(const String &sPath, const String &sExtension)
{
	// Check parameters
	if (sPath.GetLength() && sExtension.GetLength()) {
		// Add FS base directories
		Directory cDir(sPath);
		if (cDir.IsDirectory()) {
			FileSearch cSearch(cDir);
			while (cSearch.HasNextFile()) {
				// Get next file
				String sNextFilename = cSearch.GetNextFile();
				String sNextPath     = cDir.GetUrl().GetUrl() + '/' + sNextFilename;

				// Add all found files to the base-directories (meaning these must be packages ...)
				if (File(sNextPath).IsFile())
					AddBaseDir(sNextPath + '/');
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Opens a file by using base directories
*/
bool LoadableManager::OpenFile(File &cFile, const String &sFilename, bool bCreate) const
{
	// Because absolute filenames can be accessed fastest by the file system, we first give
	// the file system an absolute filename which is hopefully the correct one... if
	// not, we must search the file which is quite slow...
	const Url cUrl(sFilename);
	if (cUrl.IsAbsolute()) {
		// The given filename is already absolute! :)
		cFile.Assign(cUrl);
	} else {
		// Are there any base directories?
		const uint32 nNumOfBaseDirs = m_lstBaseDirs.GetNumOfElements();
		if (nNumOfBaseDirs) {
			// Reset file
			cFile.Assign("");

			// Loop through all base directories
			bool bFileFound = false;
			for (uint32 nBaseDir=0; nBaseDir<nNumOfBaseDirs && !bFileFound; nBaseDir++) {
				// Try to open the file directly
				const String sAbsFilename = m_lstBaseDirs[nBaseDir] + sFilename;
				cFile.Assign(sAbsFilename);

				// File found?
				bFileFound = cFile.IsFile();

				// Create the file?
				if (bCreate && !bFileFound)
					bFileFound = cFile.Create();
			}
		} else {
			// Try to open the file directly
			cFile.Assign(cUrl);
		}
	}

	// Check if the file has been found
	return cFile.Open(bCreate ? (File::FileWrite | File::FileCreate) : File::FileRead);
}

/**
*  @brief
*    Loads in a string by using a file
*/
String LoadableManager::LoadStringFromFile(const String &sFilename, String::EFormat nFormat) const
{
	// Open the file
	File cFile;
	if (OpenFile(cFile, sFilename, false))
		return cFile.GetContentAsString();

	// Error!
	return "";
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LoadableManager::LoadableManager() :
	SlotClassLoaded(&LoadableManager::OnClassLoaded, this)
{
	// The loadable manager MUST be informed if new classes are registered in order to register new loadable types!
	ClassManager::GetInstance()->EventClassLoaded.Connect(SlotClassLoaded);

	// Register all loaders
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, "PLCore::LoaderImpl", Recursive, NoBase, NoAbstract);
	Iterator<const Class*> cIterator = lstClasses.GetIterator();
	while (cIterator.HasNext())
		m_lstNewClasses.Add(cIterator.Next());
}

/**
*  @brief
*    Destructor
*/
LoadableManager::~LoadableManager()
{
	// Destroy all types
	for (uint32 i=0; i<m_lstTypes.GetNumOfElements(); i++)
		delete m_lstTypes[i];
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
LoadableManager &LoadableManager::operator =(const LoadableManager &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Register a class
*/
void LoadableManager::OnClassLoaded(const Class *pClass)
{
	// Just put the new class on the queue - because we can't assume that this class is or can be initialized
	// already, we can't even expect "IsDerivedFrom" to work, so, just REALLY note this class in here!
	m_lstNewClasses.Add(pClass);
}

/**
*  @brief
*    Registers queued classes
*/
void LoadableManager::RegisterClasses()
{
	// Is there anything on the register queue?
	if (m_lstNewClasses.GetNumOfElements()) {
		Iterator<const Class*> cIterator = m_lstNewClasses.GetIterator();
		while (cIterator.HasNext()) {
			// Get the class
			const Class *pClass = cIterator.Next();

			// Check base class, in here, we're only interested in loader implementation classes
			static const String sClassString = "PLCore::LoaderImpl";
			if (pClass->IsDerivedFrom(sClassString) && pClass->HasConstructor()) {
				// Get the loadable type ("Mesh", "Scene" etc.)
				const String sType = pClass->GetProperties().Get("Type");
				if (sType.GetLength()) {
					// Try to get an instance of the loadable type
					LoadableType *pLoadableType = m_mapTypes.Get(sType);
					if (!pLoadableType) {
						// Currently, there's no such loadable type, add one

						// Find the base class (the one directly derived from "PLCore::LoaderImpl"), all loader implementations of this type are derived from
						const Class *pLoaderTypeClass = pClass->GetBaseClass();
						const Class *pBaseLoaderClass = ClassManager::GetInstance()->GetClass(sClassString);
						while (pLoaderTypeClass && pLoaderTypeClass->GetBaseClass() != pBaseLoaderClass)
							pLoaderTypeClass = pLoaderTypeClass->GetBaseClass();
						if (pLoaderTypeClass) {
							// Get the loadable type of the loadable type class
							const String sBaseType = pLoaderTypeClass->GetProperties().Get("Type");
							if (sBaseType.GetLength()) {
								// Security check: The type of the loader class and it's loader base class must match
								if (sType == sBaseType) {
									// Create an instance of the loadable type
									pLoadableType = new LoadableType(sBaseType, *pLoaderTypeClass);
									m_lstTypes.Add(pLoadableType);
									m_mapTypes.Add(sBaseType, pLoadableType);
								} else {
									// Error!
									PL_LOG(Error, "Failed to register the loader class '" + pClass->GetClassName() + "': Loader base class 'Type'-property and loader class 'Type'-property mismatch")
								}
							} else {
								// Error!
								PL_LOG(Error, "Failed to register the loader class '" + pClass->GetClassName() + "': Loader base class has no 'Type'-property")
							}
						} else {
							// Error!
							PL_LOG(Error, "Failed to register the loader class '" + pClass->GetClassName() + "': Unable to find the loader base class")
						}
					}

					// Loadable type instance found?
					if (pLoadableType) {
						// Security check: All loader classes of a certain type must be derived from one and the same loader type class
						if (pClass->IsDerivedFrom(pLoadableType->GetClass())) {
							// Finally, create loader instance and add loader to this loadable type
							pLoadableType->AddLoader(*(new Loader(*pClass)));
						} else {
							// Error!
							PL_LOG(Error, "Failed to register the loader class '" + pClass->GetClassName() + "': Loader base class doesn't match the one specified by the 'Type'-property")
						}
					}
				} else {
					// Error!
					PL_LOG(Error, "Failed to register the loader class '" + pClass->GetClassName() + "': Class has no 'Type'-property")
				}
			}
		}
		m_lstNewClasses.Clear();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
