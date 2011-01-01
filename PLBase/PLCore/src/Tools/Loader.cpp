/*********************************************************\
 *  File: Loader.cpp                                     *
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
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/String/Tokenizer.h>
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Tools/LoadableType.h"
#include "PLCore/Tools/Loader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String Loader::UnknownFormatVersion			= "Format version is unknown (too new), you may need to update your PixelLight version";
const String Loader::DeprecatedFormatVersion		= "Deprecated format version";
const String Loader::NoLongerSupportedFormatVersion	= "Format version is no longer supported";
const String Loader::InvalidFormatVersion			= "Invalid format version";


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Loader)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the loadable type
*/
LoadableType *Loader::GetType() const
{
	return m_pLoadableType;
}

/**
*  @brief
*    Returns the name of the loadable type
*/
String Loader::GetTypeName() const
{
	const Class *pClass = GetClass();
	return (pClass != NULL) ? pClass->GetProperties().Get("Type") : "";
}

/**
*  @brief
*    Returns the number of supported formats
*/
uint32 Loader::GetNumOfFormats()
{
	InitFormatsList();
	return m_lstFormats.GetNumOfElements();
}

/**
*  @brief
*    Returns a supported format
*/
String Loader::GetFormat(uint32 nIndex)
{
	InitFormatsList();
	return m_lstFormats[nIndex];
}

/**
*  @brief
*    Checks if a format is supported in a list of extensions
*/
bool Loader::IsFormatSupported(const String &sExtension)
{
	// Check all supported formats
	InitFormatsList();
	for (uint32 i=0; i<m_lstFormats.GetNumOfElements(); i++) {
		if (m_lstFormats[i] == sExtension)
			return true; // Format found
	}

	// The format is not supported
	return false;
}

/**
*  @brief
*    Returns the formats string
*/
String Loader::GetFormats() const
{
	const Class *pClass = GetClass();
	return (pClass != NULL) ? pClass->GetProperties().Get("Formats") : "";
}

/**
*  @brief
*    Returns the description string
*/
String Loader::GetDescription() const
{
	const Class *pClass = GetClass();
	return (pClass != NULL) ? pClass->GetDescription() : "";
}

/**
*  @brief
*    Returns the whether loading is supported
*/
bool Loader::CanLoad() const
{
	const Class *pClass = GetClass();
	return (pClass != NULL) ? pClass->GetProperties().Get("Load").GetBool() : false;
}

/**
*  @brief
*    Returns the whether saving is supported
*/
bool Loader::CanSave() const
{
	const Class *pClass = GetClass();
	return (pClass != NULL) ? pClass->GetProperties().Get("Save").GetBool() : false;
}

/**
*  @brief
*    Opens a file
*/
bool Loader::OpenFile(File &cFile, const String &sUrl, bool bCreate) const
{
	// Because absolute filenames can be accessed fastest by the file system, we first give
	// the file system an absolute filename which is hopefully the correct one... if
	// not, we must search the file which is quite slow...
	const Url cUrl(sUrl);
	if (cUrl.IsAbsolute()) {
		// The given filename is already absolute! :)
		cFile.Assign(cUrl);
	} else {
		// Get the loadable manager instance
		LoadableManager *pLoadableManager = LoadableManager::GetInstance();

		// Are there any base directories?
		const uint32 nNumOfBaseDirs = pLoadableManager->GetNumOfBaseDirs();
		if (nNumOfBaseDirs) {
			// Reset file
			cFile.Assign("");

			// Loop through all base directories
			bool bFileFound = false;
			for (uint32 nBaseDir=0; nBaseDir<nNumOfBaseDirs && !bFileFound; nBaseDir++) {
				// Try to open the file directly
				const String sAbsFilename = pLoadableManager->GetBaseDir(nBaseDir) + sUrl;
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


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Loader::Loader() :
	m_pLoadableType(NULL)
{
}

/**
*  @brief
*    Destructor
*/
Loader::~Loader()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes the formats list
*/
void Loader::InitFormatsList()
{
	// Is the list already initialized?
	if (!m_lstFormats.GetNumOfElements()) {
		// Parse formats all supported formats
		const String sFormats = GetFormats();
		if (sFormats.GetLength()) {
			Tokenizer cTokenizer;
			cTokenizer.Start(sFormats);
			cTokenizer.SetDelimiters(" ,\t\r\n");
			cTokenizer.SetSingleChars("");
			String sToken = cTokenizer.GetNextToken();
			while (sToken.GetLength()) {
				m_lstFormats.Add(sToken);
				sToken = cTokenizer.GetNextToken();
			}
			cTokenizer.Stop();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
