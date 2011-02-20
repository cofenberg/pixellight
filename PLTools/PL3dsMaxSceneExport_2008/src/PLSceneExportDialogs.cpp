/*********************************************************\
 *  File: PLSceneExportDialogs.cpp                       *
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
#include <max.h>
#include <IPathConfigMgr.h>
#include "../resource.h"
#include <PLCore/Core.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PL3dsMaxSceneExport.h"
#include "PL3dsMaxSceneExport/PLSceneExportDialogs.h"
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
static INT_PTR CALLBACK AboutBoxDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)  {
		case WM_INITDIALOG:
			SetDlgItemText(hWnd, IDC_VERSION, PLCore::Core::GetVersion().ToString() + "\nPixelLight scene exporter\nCopyright (C) 2002-2011 by The PixelLight Team");
			SetDlgItemText(hWnd, IDC_BUILD, "Build:  Date: " __DATE__ "  Time: " __TIME__);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDC_ABOUT_OK:
					EndDialog(hWnd, 1);
					break;
			}
			break;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			break;

		default:
			return false;
	}

	return true;
}

void GetSettings(HWND hWnd)
{
	char szTemp[256];

	// General
	g_SEOptions.bRemoveSpaces	   = SendDlgItemMessage(hWnd, IDC_REMOVESPACES,		 BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bCorrectPortals	   = SendDlgItemMessage(hWnd, IDC_CORRECTPORTALS,	 BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bAnimationPlayback = SendDlgItemMessage(hWnd, IDC_ANIMATIONPLAYBACK, BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bShowExportedScene = SendDlgItemMessage(hWnd, IDC_SHOWEXPORTEDSCENE, BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bPublish		   = SendDlgItemMessage(hWnd, IDC_PUBLISH,			 BM_GETCHECK, 0, 0) != 0;
	GetDlgItemText(hWnd, IDC_SCENECONTAINER, szTemp, 256);
	g_SEOptions.sSceneContainer = szTemp;
	GetDlgItemText(hWnd, IDC_SCENERENDERER, szTemp, 256);
	g_SEOptions.sSceneRenderer = szTemp;
	GetDlgItemText(hWnd, IDC_SCENEVIEWER, szTemp, 256);
	g_SEOptions.sViewer = szTemp;

	// Log
	LRESULT nSelection = SendDlgItemMessage(hWnd, IDC_LOG, CB_GETCURSEL, 0, 0);
	switch (nSelection) {
		// Inactive
		case 0:
			g_SEOptions.bLog = false;
			break;

		// Errors
		case 1:
			g_SEOptions.bLog      = true;
			g_SEOptions.nLogFlags = PLLog::Error;
			break;

		// Warnings
		case 2:
			g_SEOptions.bLog      = true;
			g_SEOptions.nLogFlags = PLLog::Error | PLLog::Warning;
			break;

		// Hints
		case 3:
			g_SEOptions.bLog      = true;
			g_SEOptions.nLogFlags = PLLog::Error | PLLog::Warning | PLLog::Hint;
			break;

		// Scene data
		case 4:
			g_SEOptions.bLog      = true;
			g_SEOptions.nLogFlags = PLLog::Error | PLLog::Warning | PLLog::Hint | PLLog::Scene;
			break;
	}

	// User properties
	g_SEOptions.bUserPropVariables = SendDlgItemMessage(hWnd, IDC_USERPROP_VARIABLES, BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bUserPropModifiers = SendDlgItemMessage(hWnd, IDC_USERPROP_MODIFIERS, BM_GETCHECK, 0, 0) != 0;

	// Materials
	g_SEOptions.bCreateMaterials		 = SendDlgItemMessage(hWnd, IDC_CREATEMATERIALS,		 BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bSmartMaterialParameters = SendDlgItemMessage(hWnd, IDC_SMARTMATERIALPARAMETERS, BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bCopyTextures			 = SendDlgItemMessage(hWnd, IDC_COPYTEXTURES,			 BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bPLDirectories			 = SendDlgItemMessage(hWnd, IDC_PLDIRECTORIES,			 BM_GETCHECK, 0, 0) != 0;
	g_SEOptions.bSubDirectories			 = SendDlgItemMessage(hWnd, IDC_SUBDIRECTORIES,			 BM_GETCHECK, 0, 0) != 0;

	// Meshes
	// Normals
	g_SEOptions.bNormals = SendDlgItemMessage(hWnd, IDC_NORMALS, BM_GETCHECK, 0, 0) != 0;
	// Tangents
	g_SEOptions.bTangents = SendDlgItemMessage(hWnd, IDC_TANGENTS, BM_GETCHECK, 0, 0) != 0;
	// Binormals
	g_SEOptions.bBinormals = SendDlgItemMessage(hWnd, IDC_BINORMALS, BM_GETCHECK, 0, 0) != 0;
}

void SetupDialog(HWND hWnd)
{
	char szTemp[256];

	// General
	SendDlgItemMessage(hWnd, IDC_REMOVESPACES,			BM_SETCHECK, g_SEOptions.bRemoveSpaces,			 0);
	SendDlgItemMessage(hWnd, IDC_CORRECTPORTALS,		BM_SETCHECK, g_SEOptions.bCorrectPortals,		 0);
	SendDlgItemMessage(hWnd, IDC_OVERWRITEAMBIENTCOLOR,	BM_SETCHECK, g_SEOptions.bOverwriteAmbientColor, 0);
	EnableWindow(GetDlgItem(hWnd, IDC_PICKAMBIENTCOLOR), g_SEOptions.bOverwriteAmbientColor);
	SendDlgItemMessage(hWnd, IDC_ANIMATIONPLAYBACK,	BM_SETCHECK, g_SEOptions.bAnimationPlayback, 0);
	SendDlgItemMessage(hWnd, IDC_SHOWEXPORTEDSCENE, BM_SETCHECK, g_SEOptions.bShowExportedScene, 0);

	// 'Publishing' possible?
	bool bRuntimeDirectoryFound = false;
	char *pszBuffer = PLTools::GetPixelLightRuntimeDirectory();
	if (pszBuffer && strlen(pszBuffer)) {
		delete [] pszBuffer;
		bRuntimeDirectoryFound = true;
	}
	EnableWindow(GetDlgItem(hWnd, IDC_PUBLISH), bRuntimeDirectoryFound);
	SendDlgItemMessage(hWnd, IDC_PUBLISH, BM_SETCHECK, g_SEOptions.bPublish && bRuntimeDirectoryFound, 0);

	// Scene container
	SendDlgItemMessage(hWnd, IDC_SCENECONTAINER, CB_RESETCONTENT, 0, 0);
	int nSelection = 0;
	for (std::vector<std::string*>::size_type i=0; i<g_SEOptions.m_lstSceneContainers.size(); i++) {
		std::string *psString = g_SEOptions.m_lstSceneContainers[i];
		if (psString) {
			SendDlgItemMessage(hWnd, IDC_SCENECONTAINER, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>(psString->c_str())));
			if (!_stricmp(psString->c_str(), g_SEOptions.sSceneContainer.c_str()))
				nSelection = static_cast<int>(i);
		}
	}
	SendDlgItemMessage(hWnd, IDC_SCENECONTAINER, CB_SETCURSEL, nSelection, 0);
	// Scene renderer
	SendDlgItemMessage(hWnd, IDC_SCENERENDERER, CB_RESETCONTENT, 0, 0);
	nSelection = 0;
	for (std::vector<std::string*>::size_type i=0; i<g_SEOptions.m_lstSceneRenderers.size(); i++) {
		std::string *psString = g_SEOptions.m_lstSceneRenderers[i];
		if (psString) {
			SendDlgItemMessage(hWnd, IDC_SCENERENDERER, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>(psString->c_str())));
			if (!_stricmp(psString->c_str(), g_SEOptions.sSceneRenderer.c_str()))
				nSelection = static_cast<int>(i);
		}
	}
	SendDlgItemMessage(hWnd, IDC_SCENERENDERER, CB_SETCURSEL, nSelection, 0);
	// Viewer
	SetDlgItemText(hWnd, IDC_SCENEVIEWER, g_SEOptions.sViewer.c_str());

	// Log
	SendDlgItemMessage(hWnd, IDC_LOG, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(hWnd, IDC_LOG, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("1: Inactive")));
	SendDlgItemMessage(hWnd, IDC_LOG, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("2: Errors")));
	SendDlgItemMessage(hWnd, IDC_LOG, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("3: Warnings")));
	SendDlgItemMessage(hWnd, IDC_LOG, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("4: Hits")));
	SendDlgItemMessage(hWnd, IDC_LOG, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("5: Scene data")));
	int nLogSelection = 0;
	if (g_SEOptions.bLog) {
		// Scene data
		if (g_SEOptions.nLogFlags & PLLog::Scene)
			nLogSelection = 4;
		// Hints
		else if (g_SEOptions.nLogFlags & PLLog::Hint)
			nLogSelection = 3;
		// Warnings
		else if (g_SEOptions.nLogFlags & PLLog::Warning)
			nLogSelection = 2;
		// Errors
		else if (g_SEOptions.nLogFlags & PLLog::Error)
			nLogSelection = 1;
	}
	SendDlgItemMessage(hWnd, IDC_LOG, CB_SETCURSEL, nLogSelection, 0);

	// User properties
	SendDlgItemMessage(hWnd, IDC_USERPROP_VARIABLES, BM_SETCHECK,	g_SEOptions.bUserPropVariables,  0);
	SendDlgItemMessage(hWnd, IDC_USERPROP_MODIFIERS, BM_SETCHECK,	g_SEOptions.bUserPropModifiers,  0);

	// Materials
	SendDlgItemMessage(hWnd, IDC_EXPORTMATERIALS,	BM_SETCHECK,	g_SEOptions.bExportMaterials,	 0);
	EnableWindow(GetDlgItem(hWnd, IDC_MATERIALS),				g_SEOptions.bExportMaterials);
	EnableWindow(GetDlgItem(hWnd, IDC_CREATEMATERIALS),			g_SEOptions.bExportMaterials);
	EnableWindow(GetDlgItem(hWnd, IDC_SMARTMATERIALPARAMETERS),	g_SEOptions.bExportMaterials);
	EnableWindow(GetDlgItem(hWnd, IDC_COPYTEXTURES),			g_SEOptions.bExportMaterials);
	EnableWindow(GetDlgItem(hWnd, IDC_SUBDIRECTORIES),			g_SEOptions.bPLDirectories);
	SendDlgItemMessage(hWnd, IDC_CREATEMATERIALS,		  BM_SETCHECK, g_SEOptions.bCreateMaterials,		 0);
	SendDlgItemMessage(hWnd, IDC_SMARTMATERIALPARAMETERS, BM_SETCHECK, g_SEOptions.bSmartMaterialParameters, 0);
	SendDlgItemMessage(hWnd, IDC_COPYTEXTURES,			  BM_SETCHECK, g_SEOptions.bCopyTextures,			 0);
	SendDlgItemMessage(hWnd, IDC_PLDIRECTORIES,			  BM_SETCHECK, g_SEOptions.bPLDirectories,			 0);
	SendDlgItemMessage(hWnd, IDC_SUBDIRECTORIES,		  BM_SETCHECK, g_SEOptions.bSubDirectories,			 0);

	// Meshes
	SendDlgItemMessage(hWnd, IDC_EXPORTMESHES,     BM_SETCHECK,		g_SEOptions.bExportMeshes,	   0);
	EnableWindow(GetDlgItem(hWnd, IDC_MESH),			   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_NORMALS),			   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_TANGENTS),		   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_BINORMALS),		   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_TEXCOORDLAYERS),	   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_TEXCOORDLAYER),	   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_COMPONENTS),		   g_SEOptions.bExportMeshes);
	EnableWindow(GetDlgItem(hWnd, IDC_TEXCOORDCOMPONENTS), g_SEOptions.bExportMeshes);
	SendDlgItemMessage(hWnd, IDC_TEXCOORDLAYER, CB_RESETCONTENT, 0, 0);
	for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++) {
		sprintf(szTemp, "%d", i + 1); // The artists want to see 1 instead 0 for the first texture layer :)
		SendDlgItemMessage(hWnd, IDC_TEXCOORDLAYER, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>(szTemp)));
	}
	SendDlgItemMessage(hWnd, IDC_TEXCOORDLAYER, CB_SETCURSEL, 0, 0L);
	SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("-")));
	SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("u")));
	SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("uv")));
	SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_ADDSTRING, 0, reinterpret_cast<LONG>(const_cast<LPSTR>("uvw")));
	SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_SETCURSEL, g_SEOptions.nTexCoordComponents[0], 0L);
	// Normals
	SendDlgItemMessage(hWnd, IDC_NORMALS,   BM_SETCHECK, g_SEOptions.bNormals,   0);
	// Tangents
	SendDlgItemMessage(hWnd, IDC_TANGENTS,  BM_SETCHECK, g_SEOptions.bTangents,  0);
	// Binormals
	SendDlgItemMessage(hWnd, IDC_BINORMALS, BM_SETCHECK, g_SEOptions.bBinormals, 0);

	{ // Setup the ambient color control
		HWND hwnd = GetDlgItem(hWnd, IDC_PICKAMBIENTCOLOR);
		if (hwnd) {
			IColorSwatch *pColorSwatch = GetIColorSwatch(hwnd,
														 RGB(g_SEOptions.fOverwrittenAmbientColor[0]*255,
															 g_SEOptions.fOverwrittenAmbientColor[1]*255,
															 g_SEOptions.fOverwrittenAmbientColor[2]*255),
														 _T("Overwrite ambient color"));
			if (pColorSwatch) {
				pColorSwatch->SetModal();
				ReleaseIColorSwatch(pColorSwatch);
			}
		}
	}
}

void UpdateDialog(HWND hWnd)
{
	GetSettings(hWnd);
	SetupDialog(hWnd);
}

static INT_PTR CALLBACK ExportOptionsDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_INITDIALOG:
			CenterWindow(hWnd, GetParent(hWnd));
			SetupDialog(hWnd);
			break;

		case CC_COLOR_CHANGE:
			switch (LOWORD(wParam)) {
				case IDC_PICKAMBIENTCOLOR:
				{
					HWND hwnd = GetDlgItem(hWnd, IDC_PICKAMBIENTCOLOR);
					if (hwnd) {
						IColorSwatch *pColorSwatch = GetIColorSwatch(hwnd);
						if (pColorSwatch) {
							AColor cAmbientColor = pColorSwatch->GetAColor();
							g_SEOptions.fOverwrittenAmbientColor[0] = cAmbientColor.r;
							g_SEOptions.fOverwrittenAmbientColor[1] = cAmbientColor.g;
							g_SEOptions.fOverwrittenAmbientColor[2] = cAmbientColor.b;
							ReleaseIColorSwatch(pColorSwatch);
						}
					}
					break;
				}
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDC_OVERWRITEAMBIENTCOLOR:
					g_SEOptions.bOverwriteAmbientColor = SendDlgItemMessage(hWnd, IDC_OVERWRITEAMBIENTCOLOR, BM_GETCHECK, 0, 0) != 0;
					UpdateDialog(hWnd);
					break;

				case IDC_SCENECONTAINER:
				{
					int i = static_cast<int>(SendDlgItemMessage(hWnd, IDC_SCENECONTAINER, CB_GETCURSEL, 0, 0L));
					if (i >= 0 && i < static_cast<int>(g_SEOptions.m_lstSceneContainers.size())) {
						std::string *psString = g_SEOptions.m_lstSceneContainers[i];
						if (psString)
							g_SEOptions.sSceneContainer = *psString;
					}
					break;
				}

				case IDC_SCENERENDERER:
				{
					int i = static_cast<int>(SendDlgItemMessage(hWnd, IDC_SCENERENDERER, CB_GETCURSEL, 0, 0L));
					if (i >= 0 && i < static_cast<int>(g_SEOptions.m_lstSceneRenderers.size())) {
						std::string *psString = g_SEOptions.m_lstSceneRenderers[i];
						if (psString)
							g_SEOptions.sSceneRenderer = *psString;
					}
					break;
				}

				case IDC_EXPORTMATERIALS:
					g_SEOptions.bExportMaterials = SendDlgItemMessage(hWnd, IDC_EXPORTMATERIALS, BM_GETCHECK, 0, 0) != 0;
					UpdateDialog(hWnd);
					break;

				case IDC_PLDIRECTORIES:
					g_SEOptions.bPLDirectories = SendDlgItemMessage(hWnd, IDC_PLDIRECTORIES, BM_GETCHECK, 0, 0) != 0;
					UpdateDialog(hWnd);
					break;

				case IDC_EXPORTMESHES:
					g_SEOptions.bExportMeshes = SendDlgItemMessage(hWnd, IDC_EXPORTMESHES, BM_GETCHECK, 0, 0) != 0;
					UpdateDialog(hWnd);
					break;

				case IDC_TEXCOORDLAYER:
				{
					int i = static_cast<int>(SendDlgItemMessage(hWnd, IDC_TEXCOORDLAYER, CB_GETCURSEL, 0, 0L));
					if (i >= 0 && i < PLSceneExportOptions::MaxTexCoords)
						SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_SETCURSEL, g_SEOptions.nTexCoordComponents[i], 0L);
					break;
				}

				case IDC_TEXCOORDCOMPONENTS:
				{
					int i = static_cast<int>(SendDlgItemMessage(hWnd, IDC_TEXCOORDLAYER, CB_GETCURSEL, 0, 0L));
					if (i >= 0 && i < PLSceneExportOptions::MaxTexCoords) {
						int j = static_cast<int>(SendDlgItemMessage(hWnd, IDC_TEXCOORDCOMPONENTS, CB_GETCURSEL, 0, 0L));
						if (j >= 0 && j < 4)
							g_SEOptions.nTexCoordComponents[i] = j;
					}
					break;
				}

				case IDC_CHOOSESCENEVIEWER:
				{
					char szFilename[_MAX_PATH] = "";
					char szFilters[] = "Executable (*.exe)" "\0" "*.exe" "\0" "All files (*.*)" "\0" "*.*" "\0" "\0";
					OPENFILENAME of;

					memset(&of, 0, sizeof(OPENFILENAME));
					of.lStructSize  = sizeof(OPENFILENAME);
					of.hwndOwner    = hWnd;
					of.lpstrFilter  = szFilters;
					of.nFilterIndex = 1;
					of.lpstrFile    = szFilename;
					of.nMaxFile     = 256;
					of.lpstrTitle   = "Select viewer";
					of.Flags        = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
					of.lpstrDefExt  = "exe";
					if (GetOpenFileName(&of)) {
						SetDlgItemText(hWnd, IDC_SCENEVIEWER, szFilename);
						g_SEOptions.sViewer = szFilename;
					}
					break;
				}

				case IDC_OK:
					GetSettings(hWnd);
					EndDialog(hWnd, 1);
					break;

				case IDC_CANCEL:
					EndDialog(hWnd, 0);
					break;

				case IDC_DEFAULT:
					g_SEOptions.SetDefaultSettings();
					SetupDialog(hWnd);
					break;

				case IDC_LOAD:
				{
					char szFilename[_MAX_PATH] = "";
					char szFilters[] = "Settings (*.ini)" "\0" "*.ini" "\0" "All files (*.*)" "\0" "*.*" "\0" "\0";
					OPENFILENAME of;

					memset(&of, 0, sizeof(OPENFILENAME));
					of.lStructSize  = sizeof(OPENFILENAME);
					of.hwndOwner    = hWnd;
					of.lpstrFilter  = szFilters;
					of.nFilterIndex = 1;
					of.lpstrFile    = szFilename;
					of.nMaxFile     = 256;
					of.lpstrInitialDir = IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR);
					of.lpstrTitle   = "Load exporter settings";
					of.Flags        = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
					of.lpstrDefExt  = "ini";
					if (GetOpenFileName(&of)) {
						g_SEOptions.Load(szFilename);
						UpdateDialog(hWnd);
					}
					break;
				}

				case IDC_SAVE:
				{
					char szFilename[_MAX_PATH] = "";
					char szFilters[] = "Settings (*.ini)" "\0" "*.ini" "\0" "All files (*.*)" "\0" "*.*" "\0" "\0";
					OPENFILENAME of;

					memset(&of, 0, sizeof(OPENFILENAME));
					of.lStructSize  = sizeof(OPENFILENAME);
					of.hwndOwner    = hWnd;
					of.lpstrFilter  = szFilters;
					of.nFilterIndex = 1;
					of.lpstrFile    = szFilename;
					of.nMaxFile     = 256;
					of.lpstrInitialDir = IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR);
					of.lpstrTitle   = "Save exporter settings";
					of.Flags        = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
					of.lpstrDefExt  = "ini";
					if (GetOpenFileName(&of))
						g_SEOptions.Save(szFilename);
					break;
				}

				case IDC_HELPDOCUMENT:
				{
					// Get get runtime directory
					char *pszBuffer = PLTools::GetPixelLightRuntimeDirectory();
					if (pszBuffer) {
						// Is there a '\' or '//' at the end?
						size_t nLength = strlen(pszBuffer);
						if (pszBuffer[nLength-1] == '\\' || pszBuffer[nLength-1] == '/') {
							pszBuffer[nLength-1] = '\0';
							nLength--;
						}

						// Document file
						std::string sDocumentFile;

						// Maybe this is your internal developer version?
						size_t nRuntimeLength = strlen("PLRuntime");
						if (nLength > nRuntimeLength && !_stricmp(&pszBuffer[nLength-nRuntimeLength], "PLRuntime")) {
							// Remove the 'PLRuntime'
							nLength -= nRuntimeLength;
							pszBuffer[nLength] = '\0';

							// Construct the absolute filename
							sDocumentFile = std::string(pszBuffer) + "Doc\\PL3dsMaxSceneExport.pdf";

						// There MUST be a 'Runtime' at the end (first, we check for the public SDK structure)
						} else {
							nRuntimeLength = strlen("Runtime");
							if (nLength > nRuntimeLength && !_stricmp(&pszBuffer[nLength-nRuntimeLength], "Runtime")) {
								// Remove the 'Runtime'
								nLength -= nRuntimeLength;
								pszBuffer[nLength] = '\0';

								// Construct the absolute filename
								sDocumentFile = std::string(pszBuffer) + "Doc\\PL3dsMaxSceneExport.pdf";
							}
						}

						// Cleanup
						delete [] pszBuffer;

						// Open the help document
						if (!sDocumentFile.empty())
							ShellExecute(0, "open", sDocumentFile.c_str(), 0, 0, SW_SHOW);
					}
					break;
				}

				case IDC_ABOUT:
					DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutBoxDlgProc, 0);
					break;
			}
			break;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return true;

		default:
			return false;
	}

	return true;
}

int PLSceneOpenExportDialog(Interface &cInterface)
{
	if (!DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_EXPORTOPTIONS), cInterface.GetMAXHWnd(), ExportOptionsDlgProc, (LPARAM)nullptr))
		return 1;
	else
		return 0;
}
