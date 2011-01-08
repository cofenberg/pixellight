/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


#include <windows.h>
#include <windowsx.h>
#include "plugin.h"

//////////////////////////////////////
//
// general initialization and shutdown
//
NPError NS_PluginInitialize()
{
  return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
}

/////////////////////////////////////////////////////////////
//
// construction and destruction of our plugin instance object
//
nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
  if(!aCreateDataStruct)
    return nullptr;

  nsPluginInstance * plugin = new nsPluginInstance(aCreateDataStruct->instance);
  return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
  if(aPlugin)
    delete (nsPluginInstance *)aPlugin;
}

////////////////////////////////////////
//
// nsPluginInstance class implementation
//
nsPluginInstance::nsPluginInstance(NPP aInstance) : nsPluginInstanceBase(),
  mInstance(aInstance),
  mInitialized(FALSE),
  m_cPlugin(*this)
{
  mhWnd = nullptr;
}

nsPluginInstance::~nsPluginInstance()
{
}

static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
static WNDPROC lpOldProc = nullptr;

NPBool nsPluginInstance::init(NPWindow* aWindow)
{
  if(aWindow == nullptr)
    return FALSE;

  mhWnd = (HWND)aWindow->window;
  if(mhWnd == nullptr)
    return FALSE;
	// Save window and device context handles
	m_hPluginWnd = (HWND)aWindow->window;
	m_hPluginDC  = GetDC(m_hPluginWnd);

	// Initialize plugin
	PluginImpl::OnInit();

	// Save size
	m_nWidth  = aWindow->width;
	m_nHeight = aWindow->height;
	PluginImpl::OnSize();

  // subclass window so we can intercept window messages and
  // do our drawing to it
  lpOldProc = SubclassWindow(mhWnd, (WNDPROC)PluginWinProc);

  // associate window with our nsPluginInstance object so we can access 
  // it in the window procedure
  SetWindowLongPtr(mhWnd, GWLP_USERDATA, (LONG_PTR)this);

  mInitialized = TRUE;
  return TRUE;
}

void nsPluginInstance::shut()
{
  // subclass it back
  SubclassWindow(mhWnd, lpOldProc);
  mhWnd = nullptr;
  mInitialized = FALSE;
}

NPBool nsPluginInstance::isInitialized()
{
  return mInitialized;
}

const char * nsPluginInstance::getVersion()
{
  return NPN_UserAgent(mInstance);
}

LRESULT nsPluginInstance::ProcessMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_SIZE:
		{
			// Save new size
			m_nWidth  = LOWORD(lParam);
			m_nHeight = HIWORD(lParam);
			PluginImpl::OnSize();
			return 0;
		}

		case WM_PAINT:
		{
			// Draw plugin
			PluginImpl::OnDraw();
			return 0;
		}

		default:
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//[-------------------------------------------------------]
//[ Private virtual PluginImpl functions                  ]
//[-------------------------------------------------------]
void nsPluginInstance::Redraw()
{
	// Redraw plugin window
	RedrawWindow(m_hPluginWnd, nullptr, nullptr, 0);
}

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  nsPluginInstance *pPlugin = (nsPluginInstance*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
  if (pPlugin) {
	  return pPlugin->ProcessMessage(hWnd, msg, wParam, lParam);
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}
