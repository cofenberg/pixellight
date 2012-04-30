/*********************************************************\
 *  File: PLSceneExportOptions.cpp                       *
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
#include <PLCore/File/File.h>
#include <string.h>
#include <windows.h>
#include <max.h>
#include <IPathConfigMgr.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
PLSceneExportOptions g_SEOptions;


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String PLSceneExportOptions::DefaultOptionsFilename = "PixelLight_SceneExporterSettings.ini";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
PLSceneExportOptions::PLSceneExportOptions()
{
	SetDefaultSettings();
}

PLSceneExportOptions::~PLSceneExportOptions()
{
	ClearSceneContainers();
	ClearSceneRenderers();
}

void PLSceneExportOptions::SetDefaultSettings()
{
	ClearSceneContainers();
	ClearSceneRenderers();
	AddDefaultOptions();

	// General
	sFilename					= "";
	bLog						= false;
	bLogOpen					= true;
	nLogFlags					= PLLog::Error | PLLog::Warning | PLLog::Hint;
	bRemoveSpaces				= false;
	bCorrectPortals				= false;
	bPLDirectories				= true;
	bSubdirectories				= true; // The experience showed, this is the most useful default setting
	bOverwriteAmbientColor		= true;
	fOverwrittenAmbientColor[0]	= 1.0f;
	fOverwrittenAmbientColor[1]	= 1.0f;
	fOverwrittenAmbientColor[2]	= 1.0f;
	bAnimationPlayback			= true;
	bShowExportedScene			= true;
	bPublish					= false;
	sSceneContainer				= "";
	sSceneRenderer				= "Forward.sr";

	// As default 'viewer', try to find 'PLViewer.exe'
	sViewer = PLTools::GetPLViewerFilename();

	// User properties
	bUserPropVariables = true;
	bUserPropModifiers = true;

	// Materials
	bExportMaterials		 = true;
	bCreateMaterials		 = true;
	bSmartMaterialParameters = true;
	bCopyTextures			 = true;

	// Meshes
	bExportMeshes		   = true;
	nTexCoordComponents[0] = 2;
	for (int i=1; i<MaxTexCoords; i++)
		nTexCoordComponents[i] = 2;
	bNormals			     = true;
	bTangents			     = true;
	bBinormals			     = true;
}

void PLSceneExportOptions::WriteIntoLog()
{
	g_pLog->PrintLine("");
	g_pLog->PrintLine("Export options:");

	// General
	g_pLog->PrintLine("General");
	g_pLog->PrintFLine("  Filename:             %s", sFilename.GetASCII());
	g_pLog->PrintFLine("  Log:                  %d", bLog);			// :)
	g_pLog->PrintFLine("  Log open:             %d", bLogOpen);
	g_pLog->PrintFLine("  Log flags:");
	if (nLogFlags & PLLog::Error)
		g_pLog->PrintFLine("    - Error");
	if (nLogFlags & PLLog::Warning)
		g_pLog->PrintFLine("    - Warning");
	if (nLogFlags & PLLog::Hint)
		g_pLog->PrintFLine("    - Hint");
	if (nLogFlags & PLLog::Scene)
		g_pLog->PrintFLine("    - Scene");
	g_pLog->PrintFLine("  Remove spaces/tabs within names: %d", bRemoveSpaces);
	g_pLog->PrintFLine("  Correct portals: %d", bCorrectPortals);
	g_pLog->PrintFLine("  PL directories:          %d", bPLDirectories);
	g_pLog->PrintFLine("  Subdirectories:          %d", bSubdirectories);
	g_pLog->PrintFLine("  Overwrite ambient color: %d", bOverwriteAmbientColor);
	if (bOverwriteAmbientColor)
		g_pLog->PrintFLine("  Overwritten ambient color:  %g %g %g", fOverwrittenAmbientColor[0], fOverwrittenAmbientColor[1], fOverwrittenAmbientColor[2]);
	g_pLog->PrintFLine("  Animation playback:   %d", bAnimationPlayback);
	g_pLog->PrintFLine("  Show exported scene:  %d", bShowExportedScene);
	g_pLog->PrintFLine("  Publish:              %d", bPublish);
	g_pLog->PrintFLine("  Scene container:      %s", sSceneContainer.GetASCII());
	g_pLog->PrintFLine("  Scene renderer:       %s", sSceneRenderer.GetASCII());
	g_pLog->PrintFLine("  Viewer:               %s", sViewer.GetASCII());

	// User properties
	g_pLog->PrintLine("User properties");
	g_pLog->PrintFLine("  Variables: %d", bUserPropVariables);
	g_pLog->PrintFLine("  Modifiers: %d", bUserPropModifiers);

	// Materials
	g_pLog->PrintLine("Materials");
	g_pLog->PrintFLine("  Export materials:          %d", bExportMaterials);
	g_pLog->PrintFLine("  Create materials:          %d", bCreateMaterials);
	g_pLog->PrintFLine("  Smart material parameters: %d", bSmartMaterialParameters);
	g_pLog->PrintFLine("  Copy textures:             %d", bCopyTextures);

	// Meshes
	g_pLog->PrintLine("Mesh");
	g_pLog->PrintFLine("  Export meshes:  %d", bExportMeshes);
	for (int i=0; i<MaxTexCoords; i++)
		g_pLog->PrintFLine("  Texture coordinate %d components: %d", i, nTexCoordComponents[i]);
	g_pLog->PrintFLine("  Normals:   %d", bNormals);
	g_pLog->PrintFLine("  Tangents:  %d", bTangents);
	g_pLog->PrintFLine("  Binormals: %d", bBinormals);
	g_pLog->PrintLine("");
}

void PLSceneExportOptions::Load(const String &sFilename)
{
	// Get the absolute filename
	String sAbsFilename;
	GetAbsoluteFilename(sFilename, sAbsFilename);
	const char *pszAbsFilename = sAbsFilename.GetASCII();

	// First at all, is the configuration file existing?
	File cFile(pszAbsFilename);
	if (cFile.Exists()) {
		char szTemp[256];

		// Get version
		int nVersion = 0; // 'Initial version'
		if (GetPrivateProfileStringA("Version", "Version", nullptr, szTemp, 256, pszAbsFilename))
			nVersion = atoi(szTemp);

		// Unknown
		if (nVersion > 2) {
			// Show an error message box
			String sError = String(pszAbsFilename) + ":\nFormat version is unknown (too new), you may need to update your PixelLight 3ds Max scene exporter version\n... default settings are used...";
			MessageBoxW(nullptr, sError.GetUnicode(), L"PixelLight scene export error", MB_OK);

			// Set default settings
			SetDefaultSettings();

		// 2 (current)
		} else if (nVersion == 2) {
			LoadV2(sFilename);

		// ""/0
		} else if (nVersion == 0 || nVersion == 1) {
			// [DEPRECATED] Show an warning message box
			String sWarning = String(pszAbsFilename) + ":\nDeprecated format version";
			MessageBoxW(nullptr, sWarning.GetUnicode(), L"PixelLight scene export warning", MB_OK);
			LoadV0orV1(sFilename);

		// No longer supported format version
		} else if (nVersion >= 0) {
			// Show an error message box
			String sError = String(pszAbsFilename) + ":\nFormat version is no longer supported\n... default settings are used...";
			MessageBoxW(nullptr, sError.GetUnicode(), L"PixelLight scene export error", MB_OK);

			// Set default settings
			SetDefaultSettings();

		// Invalid format version (negative!)
		} else {
			// Show an error message box
			String sError = String(pszAbsFilename) + ":\nInvalid format version\n... default settings are used...";
			MessageBoxW(nullptr, sError.GetUnicode(), L"PixelLight scene export error", MB_OK);

			// Set default settings
			SetDefaultSettings();
		}
	} else {
		AddDefaultOptions();
	}
}

void PLSceneExportOptions::Save(const String &sFilename)
{
	// Get the absolute filename
	String sAbsFilename;
	GetAbsoluteFilename(sFilename, sAbsFilename);
	const char *pszAbsFilename = sAbsFilename.GetASCII();
	char szTemp[256], szTemp2[256];

	// Version
	WritePrivateProfileStringA("Version", "Version", "2", pszAbsFilename);

	// General
	sprintf(szTemp, "%d", bRemoveSpaces);
	WritePrivateProfileStringA("General", "RemoveSpaces", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bCorrectPortals);
	WritePrivateProfileStringA("General", "CorrectPortals", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bPLDirectories);
	WritePrivateProfileStringA("Materials", "PLDirectories", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bSubdirectories);
	WritePrivateProfileStringA("Materials", "SubDirectories", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bOverwriteAmbientColor);
	WritePrivateProfileStringA("General", "OverwriteAmbientColor", szTemp, pszAbsFilename);
	sprintf(szTemp, "%g", fOverwrittenAmbientColor[0]);
	WritePrivateProfileStringA("General", "OverwrittenAmbientColorR", szTemp, pszAbsFilename);
	sprintf(szTemp, "%g", fOverwrittenAmbientColor[1]);
	WritePrivateProfileStringA("General", "OverwrittenAmbientColorG", szTemp, pszAbsFilename);
	sprintf(szTemp, "%g", fOverwrittenAmbientColor[2]);
	WritePrivateProfileStringA("General", "OverwrittenAmbientColorB", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bAnimationPlayback);
	WritePrivateProfileStringA("General", "AnimationPlayback", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bShowExportedScene);
	WritePrivateProfileStringA("General", "ShowExportedScene", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bPublish);
	WritePrivateProfileStringA("General", "Publish", szTemp, pszAbsFilename);
	sprintf(szTemp, "%s", sSceneContainer.GetASCII());
	WritePrivateProfileStringA("General", "SceneContainer", szTemp, pszAbsFilename);
	sprintf(szTemp, "%s", sSceneRenderer.GetASCII());
	WritePrivateProfileStringA("General", "SceneRenderer", szTemp, pszAbsFilename);
	sprintf(szTemp, "%s", sViewer.GetASCII());
	WritePrivateProfileStringA("General", "Viewer", szTemp, pszAbsFilename);

	// Log
	sprintf(szTemp, "%d", bLog);
	WritePrivateProfileStringA("Log", "Log", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bLogOpen);
	WritePrivateProfileStringA("Log", "LogOpen", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", nLogFlags);
	WritePrivateProfileStringA("Log", "LogFlags", szTemp, pszAbsFilename);

	// User properties
	sprintf(szTemp, "%d", bUserPropVariables);
	WritePrivateProfileStringA("UserProperties", "UserPropVariables", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bUserPropModifiers);
	WritePrivateProfileStringA("UserProperties", "UserPropModifiers", szTemp, pszAbsFilename);

	// Materials
	sprintf(szTemp, "%d", bExportMaterials);
	WritePrivateProfileStringA("Materials", "ExportMaterials", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bCreateMaterials);
	WritePrivateProfileStringA("Materials", "CreateMaterials", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bSmartMaterialParameters);
	WritePrivateProfileStringA("Materials", "SmartMaterialParameters", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bCopyTextures);
	WritePrivateProfileStringA("Materials", "CopyTextures", szTemp, pszAbsFilename);

	// Meshes
	sprintf(szTemp, "%d", bExportMeshes);
	WritePrivateProfileStringA("Meshes", "ExportMeshes", szTemp, pszAbsFilename);
	for (int i=0; i<MaxTexCoords; i++) {
		sprintf(szTemp2, "TexCoordComponents%d", i);
		sprintf(szTemp, "%d", nTexCoordComponents[i]);
		WritePrivateProfileStringA("Meshes", szTemp2, szTemp, pszAbsFilename);
	}
	sprintf(szTemp, "%d", bNormals);
	WritePrivateProfileStringA("Meshes", "Normals", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bTangents);
	WritePrivateProfileStringA("Meshes", "Tangents", szTemp, pszAbsFilename);
	sprintf(szTemp, "%d", bBinormals);
	WritePrivateProfileStringA("Meshes", "Binormals", szTemp, pszAbsFilename);

	// Scene containers
	for (std::vector<String*>::size_type i=0; i<m_lstSceneContainers.size(); i++) {
		const String *psString = m_lstSceneContainers[i];
		if (psString) {
			sprintf(szTemp, "%d", i);
			WritePrivateProfileStringA("SceneContainers", szTemp, psString->GetASCII(), pszAbsFilename);
		}
	}

	// Scene renderers
	for (std::vector<String*>::size_type i=0; i<m_lstSceneRenderers.size(); i++) {
		const String *psString = m_lstSceneRenderers[i];
		if (psString) {
			sprintf(szTemp, "%d", i);
			WritePrivateProfileStringA("SceneRenderers", szTemp, psString->GetASCII(), pszAbsFilename);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns an absolute configuration filename
*/
void PLSceneExportOptions::GetAbsoluteFilename(const String &sFilename, String &sAbsFilename) const
{
	// Is this already an absolute filename?
	char szApplicationDrive[_MAX_DRIVE], szApplicationDir[_MAX_DIR];
	_splitpath(sFilename.GetASCII(), szApplicationDrive, szApplicationDir, nullptr, nullptr);
	if (!strlen(szApplicationDrive)) {
		// Must be a relative filename
		const char *pDir = String(IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR)).GetASCII();
		if (pDir) {
			const size_t nDirLength = strlen(pDir);
			if (nDirLength) {
				if (pDir[nDirLength-1] == '\\' || pDir[nDirLength-1] == '/')
					sAbsFilename = String(pDir) + sFilename;
				else
					sAbsFilename = String(pDir) + "\\" + sFilename;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Must be a absolute filename
		sAbsFilename = sFilename;
	}
}

/**
*  @brief
*    Clears all scene containers
*/
void PLSceneExportOptions::ClearSceneContainers()
{
	for (std::vector<String*>::size_type i=0; i<m_lstSceneContainers.size(); i++) {
		String *psString = m_lstSceneContainers[i];
		if (psString)
			delete psString;
	}
	m_lstSceneContainers.clear();
}

/**
*  @brief
*    Clears all scene renderers
*/
void PLSceneExportOptions::ClearSceneRenderers()
{
	for (std::vector<String*>::size_type i=0; i<m_lstSceneRenderers.size(); i++) {
		String *psString = m_lstSceneRenderers[i];
		if (psString)
			delete psString;
	}
	m_lstSceneRenderers.clear();
}

/**
*  @brief
*    Adds default options if the options are empty (scene renderer and so on)
*/
void PLSceneExportOptions::AddDefaultOptions()
{
	if (m_lstSceneContainers.empty()) {
		// Add default PixelLight scene containers
		m_lstSceneContainers.push_back(new String(""));
		m_lstSceneContainers.push_back(new String("PLPhysics::SCPhysicsWorld"));
	}
	if (m_lstSceneRenderers.empty()) {
		// Add default PixelLight scene renderers
		m_lstSceneRenderers.push_back(new String("FixedFunctions.sr"));
		m_lstSceneRenderers.push_back(new String("Forward.sr"));
		m_lstSceneRenderers.push_back(new String("Deferred.sr"));
	}
}

/**
*  @brief
*    Loader implementation for format version 2
*/
void PLSceneExportOptions::LoadV2(const String &sFilename)
{
	// Get the absolute filename
	String sAbsFilename;
	GetAbsoluteFilename(sFilename, sAbsFilename);
	const char *pszAbsFilename = sAbsFilename.GetASCII();
	char szTemp[256], szTemp2[256];

	// General
	bool bCanRead = false;
	if (GetPrivateProfileStringA("General", "RemoveSpaces", nullptr, szTemp, 256, pszAbsFilename)) {
		bRemoveSpaces = atoi(szTemp) != 0;
		bCanRead = true;
	}
	if (GetPrivateProfileStringA("General", "CorrectPortals", nullptr, szTemp, 256, pszAbsFilename))
		bCorrectPortals = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Materials", "PLDirectories", nullptr, szTemp, 256, pszAbsFilename))
		bPLDirectories = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Materials", "SubDirectories", nullptr, szTemp, 256, pszAbsFilename))
		bSubdirectories = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("General", "AnimationPlayback", nullptr, szTemp, 256, pszAbsFilename))
		bAnimationPlayback = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("General", "ShowExportedScene", nullptr, szTemp, 256, pszAbsFilename))
		bShowExportedScene = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("General", "Publish", nullptr, szTemp, 256, pszAbsFilename))
		bPublish = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("General", "OverwriteAmbientColor", nullptr, szTemp, 256, pszAbsFilename))
		bOverwriteAmbientColor = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("General", "OverwrittenAmbientColorR", nullptr, szTemp, 256, pszAbsFilename))
		fOverwrittenAmbientColor[0] = static_cast<float>(atof(szTemp));
	if (GetPrivateProfileStringA("General", "OverwrittenAmbientColorG", nullptr, szTemp, 256, pszAbsFilename))
		fOverwrittenAmbientColor[1] = static_cast<float>(atof(szTemp));
	if (GetPrivateProfileStringA("General", "OverwrittenAmbientColorB", nullptr, szTemp, 256, pszAbsFilename))
		fOverwrittenAmbientColor[2] = static_cast<float>(atof(szTemp));
	if (GetPrivateProfileStringA("General", "SceneContainer", bCanRead ? "" : nullptr, szTemp, 256, pszAbsFilename))
		sSceneContainer = szTemp;
	if (GetPrivateProfileStringA("General", "SceneRenderer", bCanRead ? "" : nullptr, szTemp, 256, pszAbsFilename))
		sSceneRenderer = szTemp;
	if (GetPrivateProfileStringA("General", "Viewer", bCanRead ? "" : nullptr, szTemp, 256, pszAbsFilename))
		sViewer = szTemp;

	// Log
	if (GetPrivateProfileStringA("Log", "Log", nullptr, szTemp, 256, pszAbsFilename))
		bLog = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Log", "LogOpen", nullptr, szTemp, 256, pszAbsFilename))
		bLogOpen = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Log", "LogFlags", nullptr, szTemp, 256, pszAbsFilename))
		nLogFlags = atoi(szTemp);

	// User properties
	if (GetPrivateProfileStringA("UserProperties", "UserPropVariables", nullptr, szTemp, 256, pszAbsFilename))
		bUserPropVariables = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("UserProperties", "UserPropModifiers", nullptr, szTemp, 256, pszAbsFilename))
		bUserPropModifiers = atoi(szTemp) != 0;

	// Materials
	if (GetPrivateProfileStringA("Materials", "ExportMaterials", nullptr, szTemp, 256, pszAbsFilename))
		bExportMaterials = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Materials", "CreateMaterials", nullptr, szTemp, 256, pszAbsFilename))
		bCreateMaterials = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Materials", "SmartMaterialParameters", nullptr, szTemp, 256, pszAbsFilename))
		bSmartMaterialParameters = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Materials", "CopyTextures", nullptr, szTemp, 256, pszAbsFilename))
		bCopyTextures = atoi(szTemp) != 0;

	// Meshes
	if (GetPrivateProfileStringA("Meshes", "ExportMeshes", nullptr, szTemp, 256, pszAbsFilename))
		bExportMeshes = atoi(szTemp) != 0;
	for (int i=0; i<MaxTexCoords; i++) {
		sprintf(szTemp2, "TexCoordComponents%d", i);
		if (GetPrivateProfileStringA("Meshes", szTemp2, nullptr, szTemp, 256, pszAbsFilename))
			nTexCoordComponents[i] = atoi(szTemp);
	}
	if (GetPrivateProfileStringA("Meshes", "Normals", nullptr, szTemp, 256, pszAbsFilename))
		bNormals = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Meshes", "Tangents", nullptr, szTemp, 256, pszAbsFilename))
		bTangents = atoi(szTemp) != 0;
	if (GetPrivateProfileStringA("Meshes", "Binormals", nullptr, szTemp, 256, pszAbsFilename))
		bBinormals = atoi(szTemp) != 0;

	// Scene containers
	ClearSceneContainers();
	for (int i=0;; i++) {
		sprintf(szTemp2, "%d", i);
		if (GetPrivateProfileStringA("SceneContainers", szTemp2, nullptr, szTemp, 256, pszAbsFilename))
			m_lstSceneContainers.push_back(new String(szTemp));
		else
			break; // No more scene containers
	}

	// Scene renderers
	ClearSceneRenderers();
	for (int i=0;; i++) {
		sprintf(szTemp2, "%d", i);
		if (GetPrivateProfileStringA("SceneRenderers", szTemp2, nullptr, szTemp, 256, pszAbsFilename))
			m_lstSceneRenderers.push_back(new String(szTemp));
		else
			break; // No more scene renderers
	}

	// Add default options
	AddDefaultOptions();
}

/**
*  @brief
*    Loader implementation for format version 0 or version 1
*/
void PLSceneExportOptions::LoadV0orV1(const String &sFilename)
{
	// Same as version 0 and 1...
	LoadV2(sFilename);

	// To avoid troubles we need to reset the scene renderers! (previously: SRBasic, SRBasicLighting, SRShaderLighting)
	ClearSceneRenderers();
	sSceneRenderer = "Forward.sr";

	// Add default PixelLight scene renderers
	m_lstSceneRenderers.push_back(new String("FixedFunctions.sr"));
	m_lstSceneRenderers.push_back(new String("Forward.sr"));
	m_lstSceneRenderers.push_back(new String("Deferred.sr"));
}
