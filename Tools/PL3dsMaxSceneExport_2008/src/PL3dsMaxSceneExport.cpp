/*********************************************************\
 *  File: PL3dsMaxSceneExport.cpp                        *
 *      Scene export plugin for 3ds Max - main plugin stuff
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include "PL3dsMaxSceneExport/PLToolbar.h"
#include "PL3dsMaxSceneExport/PLSceneEnumProc.h"


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
HINSTANCE g_hInstance;
extern ClassDesc *GetPLToolbarDesc();


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class PLSceneExport : public SceneExport {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		PLSceneExport()
		{
		}

		virtual ~PLSceneExport()
		{
		}

		int ExtCount()
		{
			return 1;
		}

		const TCHAR *Ext(int i)
		{
			return (i == 0) ? _T("scene") : _T("");
		}

		const TCHAR *LongDesc()
		{
			return _T("PixelLight scene export plugin http://www.pixellight.org");
		}

		const TCHAR *ShortDesc()
		{
			return _T("PixelLight scene export");
		}

		const TCHAR *AuthorName()
		{
			return _T("Copyright (C) 2002-2013 by The PixelLight Team");
		}

		const TCHAR *CopyrightMessage()
		{
			return _T("");
		}

		const TCHAR *OtherMessage1()
		{
			return _T("");
		}

		const TCHAR *OtherMessage2()
		{
			return _T("");
		}

		unsigned int Version()
		{
			return 84;
		}

		void ShowAbout(HWND hWnd)
		{
			MessageBox(hWnd, _T("PixelLight scene export plugin\nhttp://www.pixellight.org"), _T("about"), MB_OK);
		}

		BOOL SupportsOptions(int ext,DWORD options)
		{
			return (options == SCENE_EXPORT_SELECTED);
		}

		int DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = false, DWORD options = 0)
		{
			if (name && i) {
				// We REALLY need to set the locale to a known setting... else we may get floats like "1,123" instead of "1.123"!
				char *pSaveLocale = _strdup(setlocale(LC_ALL, nullptr));	// Get the current set locale, we REALLY need to backup the locale because it "may" be changed by "setlocale"
				setlocale(LC_ALL, "C");

				// Export
				PLSceneEnumProc cExporter(PLCore::String(name).GetASCII(), *i, options);

				// Be polite and restore the previously set locale
				setlocale(LC_ALL, pSaveLocale);
				free(pSaveLocale);	// ... and don't forget to free the memory of our locale backup...
			}
			return 1;
		}


};

class PLSceneClassDesc : public ClassDesc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		int IsPublic()
		{
			return 1;
		}

		void *Create(BOOL loading = false)
		{
			return new PLSceneExport();
		}

		const TCHAR *ClassName()
		{
			return _T("PixelLight scene export");
		}

		SClass_ID SuperClassID()
		{
			return SCENE_EXPORT_CLASS_ID;
		}

		Class_ID ClassID()
		{
			return Class_ID(0xdeadbeff, 0x7b5a93fb);
		}

		const TCHAR *Category()
		{
			return _T("");
		}


};

static PLSceneClassDesc PLSceneDesc;

extern "C" {

	__declspec(dllexport) const TCHAR *LibDescription()
	{
		return _T("PixelLight scene export plugin");
	}

	__declspec(dllexport) int LibNumberClasses()
	{
		return 2;
	}

	__declspec(dllexport) ClassDesc *LibClassDesc(int i)
	{
		switch(i) {
			case 0:
				return &PLSceneDesc;

			case 1:
				return GetPLToolbarDesc();

			default:
				return 0;
		}
	}

	__declspec(dllexport) ULONG LibVersion()
	{
		return VERSION_3DSMAX;
	}

	__declspec(dllexport )ULONG CanAutoDefer()
	{
		return 1;
	}

}


//[-------------------------------------------------------]
//[ DllMain                                               ]
//[-------------------------------------------------------]
int bControlsInit = false;
BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved)
{
	g_hInstance = hinstDLL;
	if (!bControlsInit) {
		bControlsInit = true;
		InitCommonControls();
	}
	return true;
}
