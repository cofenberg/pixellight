/*********************************************************\
 *  File: LoadableManager.cpp                            *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include "PLCore/Tools/Loader.h"
#include "PLCore/Tools/LoadableType.h"
#include "PLCore/Tools/LoadableManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
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
*    Returns a loadable type
*/
LoadableType *LoadableManager::GetType(uint32 nIndex)
{
	RegisterClasses();
	return m_lstTypes.Get(nIndex);
}

/**
*  @brief
*    Returns a loadable type by using it's name
*/
LoadableType *LoadableManager::GetType(const String &sName)
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
Loader *LoadableManager::GetLoader(uint32 nIndex)
{
	RegisterClasses();
	return m_lstLoaders.Get(nIndex);
}

/**
*  @brief
*    Returns a loader by using a extension
*/
Loader *LoadableManager::GetLoader(const String &sExtension)
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
		const LoadableType *pLoadableType = GetType(sType);
		if (pLoadableType) {
			const Loader *pLoader = pLoadableType->GetLoader(sExtension);
			if (pLoader)
				return pLoader->CanLoad();
		}
	} else {
		const Loader *pLoader = GetLoader(sExtension);
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
		const LoadableType *pLoadableType = GetType(sType);
		if (pLoadableType) {
			const Loader *pLoader = pLoadableType->GetLoader(sExtension);
			if (pLoader)
				return pLoader->CanSave();
		}
	} else {
		const Loader *pLoader = GetLoader(sExtension);
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
				String sNextPath     = cDir.GetUrl().GetUrl() + "/" + sNextFilename;

				// Add all found files to the base-directories (meaning these must be packages ...)
				if (File(sNextPath).IsFile())
					AddBaseDir(sNextPath + "/");
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
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
	ClassManager::GetInstance()->EventClassLoaded.Connect(&SlotClassLoaded);

	// Register all loaders
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, "PLCore::Loader", Recursive, NoBase, NoAbstract);
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
*    Register a class
*/
void LoadableManager::OnClassLoaded(const Class *pClass)
{
	// Just put the new class on the queue - because we can't assume that this class is or can be initialized
	// already, we can't even excpect "IsDerivedFrom" to work, so, just REALLY note this class in here!
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

			// Check parameter and base class
			static const String sClassString = "PLCore::Loader";
			if (pClass->IsDerivedFrom(sClassString)) {
				// Create loader instance
				const String sType = pClass->GetProperties().Get("Type");
				if (sType.GetLength()) {
					Loader *pLoader = (Loader*)pClass->Create();
					if (pLoader) {
						// Try to get an instance of the loadable type
						LoadableType *pLoadableType = m_mapTypes.Get(sType);
						if (!pLoadableType) {
							// Currently, there's no such loadable type, add one

							// Find the base class, all loader implementations of this type are derived from
							const Class *pLoaderClass = ClassManager::GetInstance()->GetClass(sClassString);
							const Class *pLoaderTypeClass = pClass->GetBaseClass();
							while (pLoaderTypeClass && pLoaderTypeClass->GetBaseClass() != pLoaderClass)
								pLoaderTypeClass = pLoaderTypeClass->GetBaseClass();

							// Create type
							if (pLoaderTypeClass) {
								pLoadableType = new LoadableType(sType, *pLoaderTypeClass);
								m_lstTypes.Add(pLoadableType);
								m_mapTypes.Add(sType, pLoadableType);
							}
						}

						// Add loader to this loadable type
						if (pLoadableType)
							pLoadableType->AddLoader(*pLoader);
					}
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
