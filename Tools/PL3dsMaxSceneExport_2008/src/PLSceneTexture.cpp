/*********************************************************\
 *  File: PLSceneTexture.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Xml/Xml.h>
#include <PLCore/File/Url.h>
#include <PLCore/File/Directory.h>
#include <max.h>
#include <bmmlib.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"
#include "PL3dsMaxSceneExport/PLSceneTexture.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the texture name
*/
String PLSceneTexture::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns the reference count of this texture
*/
unsigned int PLSceneTexture::GetReferenceCount() const
{
	return m_nReferenceCount;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneTexture::PLSceneTexture(PLScene &cScene, const String &sName, bool bNormalMap_xGxR) :
	m_pScene(&cScene),
	m_sName(sName),
	m_nReferenceCount(0)
{
	// Cut of the path of the map name - if there's one
	String sAbsBitmapFilename = m_sName;

	// Get the texture name
	m_sName = sName;

	// Check options
	if (g_SEOptions.bCopyTextures) {
		// Can we use the given absolute filename?
		HANDLE hFile = CreateFileW(sAbsBitmapFilename.GetUnicode(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE) {
			// Get the current path of the loaded 3ds Max scene
			String sCurFilePath = Url(GetCOREInterface()->GetCurFilePath().data()).CutFilename();
			if (sCurFilePath.GetLength()) {
				// Compose absolute filename by just concatenating the two filenames (for relative filenames)
				String sBitmapFilename = sCurFilePath + sAbsBitmapFilename;
				hFile = CreateFileW(sBitmapFilename.GetUnicode(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (hFile == INVALID_HANDLE_VALUE) {
					// Get the filename without any path information
					String sFilenameOnly  = Url(sName).GetFilename().GetASCII();

					// Compose absolute filename
					if (sFilenameOnly.GetLength()) {
						char nLastCharacter = sCurFilePath[sCurFilePath.GetLength()-1];
						if (nLastCharacter == '\\' || nLastCharacter == '/')
							sBitmapFilename = sCurFilePath + sFilenameOnly;
						else
							sBitmapFilename = sCurFilePath + "\\" + sFilenameOnly;
						hFile = CreateFileW(sBitmapFilename.GetUnicode(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
						if (hFile == INVALID_HANDLE_VALUE) {
							// Check map directories
							int nMapDirCount = TheManager->GetMapDirCount();
							for (int nMapDir=0; nMapDir<nMapDirCount; nMapDir++) {
								const TCHAR *pMapDir = TheManager->GetMapDir(nMapDir);
								size_t nLength = strlen(pMapDir);
								if (nLength) {
									nLastCharacter = pMapDir[nLength-1];
									if (nLastCharacter == '\\' || nLastCharacter == '/')
										sBitmapFilename = pMapDir + sFilenameOnly;
									else
										sBitmapFilename = pMapDir + String('\\') + sFilenameOnly;
									hFile = CreateFileW(sBitmapFilename.GetUnicode(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
									if (hFile != INVALID_HANDLE_VALUE)
										break;
									else
										sAbsBitmapFilename = sBitmapFilename;
								}
							}
						} else {
							sAbsBitmapFilename = sBitmapFilename;
						}
					}
				} else {
					sAbsBitmapFilename = sBitmapFilename;
				}
			}
		}
		if (hFile != INVALID_HANDLE_VALUE) {
			// Get source file time and close it
			FILETIME sSourceCreationTime;
			FILETIME sSourceLastAccessTime;
			FILETIME sSourceLastWriteTime;
			GetFileTime(hFile, &sSourceCreationTime, &sSourceLastAccessTime, &sSourceLastWriteTime);
			CloseHandle(hFile);

			// Cut of the filename
			String sFilename = Url(g_SEOptions.sFilename).CutFilename();

			// Construct the absolute target filename
			uint32 nLength = sFilename.GetLength();
			if (nLength) {
				sFilename = sFilename + m_sName;

				// Is there already such a file? If yes, check the file times...
				hFile = CreateFileW(sFilename.GetUnicode(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (hFile != INVALID_HANDLE_VALUE) {
					// Get target file time and close it
					FILETIME sTargetCreationTime;
					FILETIME sTargetLastAccessTime;
					FILETIME sTargetLastWriteTime;
					GetFileTime(hFile, &sTargetCreationTime, &sTargetLastAccessTime, &sTargetLastWriteTime);
					CloseHandle(hFile);

					// Compare file time
					long nResult = CompareFileTime(&sTargetLastWriteTime, &sSourceLastWriteTime);
					if (nResult >= 0)
						return; // Nothing to do :)
				}

				{ // Before we copy, we need to ensure that the target directory is there, else 'CopyFile()' will fail!
					Directory cDirectory(Url(sFilename).CutFilename());
					cDirectory.CreateRecursive();
				}

				// Copy the texture (bitmap)
				CopyFileW(sAbsBitmapFilename.GetUnicode(), sFilename.GetUnicode(), false);

				// If there's a 'plt'-file for the texture, copy it, too
				int nIndex = sFilename.LastIndexOf(".");
				if (nIndex >= 0) {
					sFilename.Delete(nIndex);
					sFilename += ".plt";
					nIndex = sAbsBitmapFilename.LastIndexOf(".");
					if (nIndex >= 0) {
						sAbsBitmapFilename.Delete(nIndex);
						sAbsBitmapFilename += ".plt";
						if (!CopyFileW(sAbsBitmapFilename.GetUnicode(), sFilename.GetUnicode(), false)) {
							// Failed to copy the 'plt'-file...
							if (bNormalMap_xGxR) {
								// Create an automatic 'plt'-file...
								// Create XML document
								XmlDocument cDocument;

								// Add declaration
								XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "ISO-8859-1", "");
								cDocument.LinkEndChild(*pDeclaration);

								// Add texture
								XmlElement *pTextureElement = new XmlElement("Texture");

								// Setup attribute
								pTextureElement->SetAttribute("Version", "1");

								// Add general
								XmlElement *pGeneralElement = new XmlElement("Node");
								pGeneralElement->SetAttribute("Compression", "DXT5_xGxR");

								// Link general element
								pTextureElement->LinkEndChild(*pGeneralElement);

								// Link material element
								cDocument.LinkEndChild(*pTextureElement);

								// Save settings
								if (cDocument.Save(sFilename))
									g_pLog->LogFLine(PLLog::Hint, "Created '%s'", sFilename.GetASCII());
								else
									g_pLog->LogFLine(PLLog::Error, "Can't create '%s'!", sFilename.GetASCII());
							}
						}
					}
				}
			}
		} else {
			g_pLog->LogFLine(PLLog::Error, "Can't find texture (bitmap) '%s'!", m_sName.GetASCII());
		}
	}
}

/**
*  @brief
*    Destructor
*/
PLSceneTexture::~PLSceneTexture()
{
}
