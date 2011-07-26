/*********************************************************\
 *  File: LoadableType.cpp                               *
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
#include "PLCore/System/System.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Tools/Loader.h"
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Tools/LoadableType.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the name of the loadable type
*/
String LoadableType::GetName() const
{
	// Return description
	return m_sName;
}

/**
*  @brief
*    Returns the class of the loadable type
*/
const Class &LoadableType::GetClass() const
{
	return *m_pClass;
}

/**
*  @brief
*    Gets the relative version of an absolute file path
*/
String LoadableType::GetRelativeFilePath(const String &sPath) const
{
	// Check path
	if (!sPath.GetLength())
		return ""; // Nothing to do :)

	// Start with validated path
	String sValidPath = Url(sPath).GetUrl();

	// Loop through all base directories
	LoadableManager *pLoadableManager = LoadableManager::GetInstance();
	for (int i=-1; i<static_cast<int>(pLoadableManager->GetNumOfBaseDirs()); i++) {
		// Get base directory
		const String sBaseDir = (i < 0) ? System::GetInstance()->GetCurrentDir() : pLoadableManager->GetBaseDir(i);

		// Is this base directory used?
		if (sValidPath.Compare(sBaseDir, 0, sBaseDir.GetLength())) {
			// Cut off base directory
			sValidPath = sValidPath.GetSubstring(sBaseDir.GetLength()+1);

			// Haha, sometimes I'm using break, too ;-)
			break;
		}
	}

	// Return path
	return sValidPath;
}


//[-------------------------------------------------------]
//[ Formats & loaders                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of supported formats
*/
uint32 LoadableType::GetNumOfFormats() const
{
	return m_lstFormats.GetNumOfElements();
}

/**
*  @brief
*    Returns a supported formats
*/
String LoadableType::GetFormat(uint32 nIndex) const
{
	return m_lstFormats.Get(nIndex);
}

/**
*  @brief
*    Returns the number of loaders
*/
uint32 LoadableType::GetNumOfLoaders() const
{
	return m_lstLoaders.GetNumOfElements();
}

/**
*  @brief
*    Returns a loader by using an index
*/
Loader *LoadableType::GetLoaderByIndex(uint32 nIndex) const
{
	return m_lstLoaders.Get(nIndex);
}

/**
*  @brief
*    Returns a loader by using a loadable extension
*/
Loader *LoadableType::GetLoaderByExtension(const String &sExtension) const
{
	return m_mapLoaders.Get(sExtension);
}

/**
*  @brief
*    Returns a loader for loading by using a loadable file
*/
Loader *LoadableType::GetLoaderForLoadingByFile(File &cFile) const
{
	// Get the file URL
	const Url &cUrl = cFile.GetUrl();

	// Get file extension (e.g. "txt" if the filename was "readme.txt", "gz" if the filename was "archive.tar.gz")
	const String sExtension = cUrl.GetExtension();
	if (sExtension.GetLength()) {
		// Get a loader by using the loadable extension
		Loader *pLoader = m_mapLoaders.Get(sExtension);

		// Is there a loader and is this loader capable of loading?
		if (pLoader && pLoader->CanLoad()) {
			// Done
			return pLoader;
		} else {
			// Error: Loading of this file format is not supported!
		}
	} else {
		// Error: No filename extension
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LoadableType::LoadableType() :
	m_pClass(nullptr)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Constructor
*/
LoadableType::LoadableType(const String &sName, const Class &cClass) :
	m_sName(sName),
	m_pClass(&cClass)
{
}

/**
*  @brief
*    Destructor
*/
LoadableType::~LoadableType()
{
}

/**
*  @brief
*    Copy operator
*/
LoadableType &LoadableType::operator =(const LoadableType &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Adds loader to this loadable type
*/
void LoadableType::AddLoader(Loader &cLoader)
{
	// Check parameter
	if (cLoader.m_pLoadableType != this) {
		// Add loader
		cLoader.m_pLoadableType = this;
		m_lstLoaders.Add(&cLoader);
		LoadableManager *pLoadableManager = LoadableManager::GetInstance();
		pLoadableManager->m_lstLoaders.Add(&cLoader);

		// Add all formats of this loader
		for (uint32 i=0; i<cLoader.GetNumOfFormats(); i++) {
			// Is there already such a format within this loadable type?
			const String  sFormat = cLoader.GetFormat(i);
			const Loader *pLoader = m_mapLoaders.Get(sFormat);
			if (pLoader) {
				// Two loaders for the same format extension of the same loadable type? That's not ok! Sadly, in fact this can happen
				// due to the tons of available file formats and there's no chance to avoid such naming conflicts...
				PL_LOG(Info, "Loader '" + cLoader.m_pClass->GetClassName() + "': Format '" + sFormat + "' is already used by loader '" + pLoader->m_pClass->GetClassName() + '\'')
			} else {
				// Is there already such a format within the loadable manager?
				pLoader = pLoadableManager->m_mapLoaders.Get(sFormat);
				if (pLoader) {
					// Write a note into the log - but no error because that's a situation that CAN occur, this just means that we can't figure
					// out the loader type by just looking at a given filename extension (but that's usually not required anyway)
					PL_LOG(Debug, "Loader '" + cLoader.m_pClass->GetClassName() + "': Format '" + sFormat + "' is already used by loader '" + pLoader->m_pClass->GetClassName() + "' (uncritical due to different loader types)")

				// Add format to the loadable manager
				} else {
					pLoadableManager->m_mapLoaders.Add(sFormat, &cLoader);
					pLoadableManager->m_lstFormats.Add(sFormat);
					pLoadableManager->m_mapTypesByExtension.Add(sFormat, this);
				}

				// Add format to this loadable type
				m_mapLoaders.Add(sFormat, &cLoader);
				m_lstFormats.Add(sFormat);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
