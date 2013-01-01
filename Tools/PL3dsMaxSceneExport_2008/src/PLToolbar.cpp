/*********************************************************\
 *  File: PLToolbar.cpp                                  *
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
#include <max.h>
#include <maxicon.h>
#include <PLCore/String/String.h>
#include "PL3dsMaxSceneExport/PLSceneEnumProc.h"
#include "PL3dsMaxSceneExport/PLToolbar.h"


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
extern HINSTANCE g_hInstance;
static PLToolbar g_PLToolbar;


//[-------------------------------------------------------]
//[ Global definitions                                    ]
//[-------------------------------------------------------]
#define TBITEM(type, pIcon, cmd) \
		ToolButtonItem(type, pIcon, GetCUIFrameMgr()->GetImageSize(), GetCUIFrameMgr()->GetImageSize(), GetCUIFrameMgr()->GetButtonWidth(), GetCUIFrameMgr()->GetButtonHeight(), cmd, 0)
#define ID_TOOLBAR_0 11230
#define ID_TOOLBAR_1 11231
#define ID_TOOLBAR_2 11232


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class descriptor for the PixelLight toolbar plugin
*/
class PLToolbarClassDesc : public ClassDesc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		int IsPublic()
		{
			return 1;
		}

		void *Create(BOOL bLoading = FALSE)
		{
			return &g_PLToolbar;
		}

		const TCHAR *ClassName()
		{
			return _T("PixelLight Scene Exporter Toolbar");
		}

		SClass_ID SuperClassID()
		{
			return UTILITY_CLASS_ID;
		}

		Class_ID ClassID()
		{
			return Class_ID(0x2a369ba5, 0x271d0e6b);
		}

		const TCHAR *Category()
		{
			return _T("Utility Toolbar");
		}


};


static PLToolbarClassDesc PLToolbarDesc;
ClassDesc *GetPLToolbarDesc()
{
	return &PLToolbarDesc;
}


class TooltipMessageHandler : public CUIFrameMsgHandler {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		TooltipMessageHandler(PLToolbar *pToolbar)
		{
			m_pToolbar = pToolbar;
		}
		int ProcessMessage(UINT nMessage, WPARAM wParam, LPARAM lParam);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLToolbar *m_pToolbar;


};


static TooltipMessageHandler *g_pTooltipMessageHandler;


int TooltipMessageHandler::ProcessMessage(UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	switch(nMessage) {
		case WM_NOTIFY:
			// Provide the tooltip text for the toolbar buttons
			if (reinterpret_cast<LPNMHDR>(lParam)->code == TTN_NEEDTEXT) {
				LPTOOLTIPTEXT lpTooltipText = (LPTOOLTIPTEXT)lParam;
				switch (lpTooltipText->hdr.idFrom) {
					case ID_TOOLBAR_0:
						lpTooltipText->lpszText = _T("PixelLight export and preview");
						break;

					case ID_TOOLBAR_1:
						lpTooltipText->lpszText = _T("PixelLight export selected and preview");
						break;

					case ID_TOOLBAR_2:
						lpTooltipText->lpszText = _T("Open PixelLight export directory");
						break;
				}
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_TOOLBAR_0:
				case ID_TOOLBAR_1:
				case ID_TOOLBAR_2:
				{
					Interface *pMaxInterface = m_pToolbar->GetMaxInterface();
					String sFilename = pMaxInterface->GetDir(APP_EXPORT_DIR);
					sFilename += "\\PixelLight";
					CreateDirectoryW(sFilename.GetUnicode(), nullptr);
					if (LOWORD(wParam) == ID_TOOLBAR_2) {
						ShellExecute(0, _T("open"), sFilename, 0, 0, SW_SHOW);
					} else {
						sFilename += _T("\\Preview.scene");
						PLSceneEnumProc cExporter(sFilename, *pMaxInterface, (LOWORD(wParam) == ID_TOOLBAR_1) ? SCENE_EXPORT_SELECTED : 0);
					}
					break;
				}

				default:
					return FALSE;
			}
			break;
	}

	return FALSE;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
PLToolbar::PLToolbar() :
	m_pMaxInterface(nullptr),
	m_hToolbarWnd(nullptr)
{
}

PLToolbar::~PLToolbar()
{
}

ICUIFrame *PLToolbar::GetICUIFrame() const
{
	HWND hFrameWnd = GetParent(m_hToolbarWnd);
	return ::GetICUIFrame(hFrameWnd);
}

Interface *PLToolbar::GetMaxInterface() const
{
	return m_pMaxInterface;
}


//[-------------------------------------------------------]
//[ Public virtual UtilityObj functions                   ]
//[-------------------------------------------------------]
void PLToolbar::BeginEditParams(Interface *ip, IUtil *iu)
{
	m_pMaxInterface = ip;

	ICUIFrame *pFrame = GetICUIFrame();
	if (pFrame) {
		pFrame->Hide(FALSE);
		if (!pFrame->IsFloating())
			GetCUIFrameMgr()->RecalcLayout(TRUE);
	} else {
		// Create a quite simple toolbar
		// Create the frame
		HWND hParent = ip->GetMAXHWnd();
		HWND hWnd = CreateCUIFrameWindow(hParent, _T("PixelLight Scene Exporter Toolbar"), 0, 0, 100, 100);
		pFrame = ::GetICUIFrame(hWnd);
		pFrame->SetContentType(CUI_TOOLBAR);
		pFrame->SetPosType(CUI_HORIZ_DOCK | CUI_VERT_DOCK | CUI_FLOATABLE | CUI_SM_HANDLES);

		// Create the toolbar window
		HWND hToolbar = CreateWindow(
				CUSTTOOLBARWINDOWCLASS,
				nullptr,
				WS_CHILD | WS_VISIBLE,
				0, 0, 250, 100,
				hWnd,
				nullptr,
				g_hInstance,
				nullptr);
		m_hToolbarWnd = hToolbar;

		// Link the toolbar to the CUI frame
		ICustToolbar *pToolBar = GetICustToolbar(hToolbar);
		pToolBar->LinkToCUIFrame(hWnd, nullptr);
		pToolBar->SetBottomBorder(FALSE);
		pToolBar->SetTopBorder(FALSE);

		// Install the message handler to process the controls we'll add
		g_pTooltipMessageHandler = new TooltipMessageHandler(this);
		pFrame->InstallMsgHandler(g_pTooltipMessageHandler);

		// Add buttons (index is 1-based)
		MaxBmpFileIcon *pIcon = new MaxBmpFileIcon(_T("ViewportNavigationControls"), 1);
		pToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TOOLBAR_0));
		pIcon = new MaxBmpFileIcon(_T("ViewportNavigationControls"), 13);
		pToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TOOLBAR_1));
		pToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("ViewportNavigationControls"), 3);
		pToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TOOLBAR_2));

		// Set the initial floating position
		SIZE sz;
		RECT rect;
		pToolBar->GetFloatingCUIFrameSize(&sz);
		rect.top = 100;
		rect.left = 100;
		rect.right = rect.left+sz.cx;
		rect.bottom = rect.top+sz.cy;
		GetCUIFrameMgr()->FloatCUIWindow(hWnd, &rect);
		MoveWindow(hWnd, rect.left, rect.right, sz.cx, sz.cy, TRUE);

		// Finally we're done, release the toolbar and frame handles
		ReleaseICustToolbar(pToolBar);
		pToolBar = nullptr;
		ReleaseICUIFrame(pFrame);
	}
}

void PLToolbar::EndEditParams(Interface *ip, IUtil *iu)
{
	m_pMaxInterface = nullptr;

	ICUIFrame *pFrame = GetICUIFrame();
	if (pFrame) {
		pFrame->Hide(TRUE);
		if (!pFrame->IsFloating())
			GetCUIFrameMgr()->RecalcLayout(TRUE);
	}
	ReleaseICUIFrame(pFrame);
}

void PLToolbar::DeleteThis()
{
}
