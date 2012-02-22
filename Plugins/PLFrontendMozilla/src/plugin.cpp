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
#include <PLCore/Runtime.h>
#include <PLCore/Tools/Timing.h>
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
    delete static_cast<nsPluginInstance *>(aPlugin);
}

////////////////////////////////////////
//
// nsPluginInstance class implementation
//
nsPluginInstance::nsPluginInstance(NPP aInstance) : nsPluginInstanceBase(),
  mInstance(aInstance),
  mInitialized(FALSE),
  mhWnd(nullptr),
  m_hWnd(nullptr),
  m_bFrontendApplicationInitialized(false),
  m_bMouseVisible(true),
  m_bTrapMouse(false),
  m_cFrontend(m_cFrontendContext, *this)
{
	// Scan PL-runtime directory for compatible plugins and load them in as well as scan for compatible data and register it
	PLCore::Runtime::ScanDirectoryPluginsAndData();

	// Do the frontend life cycle thing - let the world know that we have been created
	FrontendImpl::OnCreate();
}

nsPluginInstance::~nsPluginInstance()
{
	// Do the frontend life cycle thing - let the world know that we're going to die
	FrontendImpl::OnDestroy();
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
	m_hWnd = (HWND)aWindow->window;

	{	// Let the world know that this frontend is now going to run
		const PLCore::String sExecutableFilename;
		const PLCore::Array<PLCore::String> lstArguments;
		FrontendImpl::OnRun(sExecutableFilename, lstArguments);
	}

	// Do the frontend life cycle thing - initialize
	if (FrontendImpl::OnStart()) {
		FrontendImpl::OnResume();

		// Frontend application successfully initialized
		m_bFrontendApplicationInitialized = true;
	}

	// Inform that the window size has been changed
	FrontendImpl::OnSize();

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
	// Do the frontend life cycle thing - de-initialize
	if (m_bFrontendApplicationInitialized) {
		FrontendImpl::OnPause();
		FrontendImpl::OnStop();
	}

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
		case WM_MOVE:
			// Update trap mouse if required
			UpdateTrapMouse();
			return 0;

		case WM_SIZE:
			// Update trap mouse if required
			UpdateTrapMouse();

			// Inform that the window size has been changed
			FrontendImpl::OnSize();
			return 0;

		case WM_PAINT:
			// Let the frontend draw into it's window
			FrontendImpl::OnDraw();

			// Ping
			Ping();
			return 0;

		// Drag and drop of files
		case WM_DROPFILES:
		{
			// Get dropped filenames. Because there's no way - without extreme overhead :) - to check whether
			// we really need to use Unicode or ASCII is quite enough, we always use Unicode just to be sure.
			const uint32 nNumOfFiles = DragQueryFileW(reinterpret_cast<HDROP>(wParam), 0xFFFFFFFF, static_cast<LPWSTR>(nullptr), 0);
			if (nNumOfFiles) {
				// Create the file list
				PLCore::Array<PLCore::String> lstFiles;
				lstFiles.Resize(nNumOfFiles);
				for (uint32 i=0; i<nNumOfFiles; i++) {
					// Get the length of the string (+1 for \0)
					const UINT nSize = DragQueryFileW(reinterpret_cast<HDROP>(wParam), i, nullptr, 0) + 1;

					// Create the string and fill it
					wchar_t *pszFile = new wchar_t[nSize];
					DragQueryFileW(reinterpret_cast<HDROP>(wParam), i, pszFile, nSize);

					// Store the string (the PL string takes over the control)
					lstFiles[i] = PLCore::String(pszFile, false, nSize - 1);
				}

				// Inform the frontend
				FrontendImpl::OnDrop(lstFiles);
				return 0;
			}
		}

		default:
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::FrontendImpl functions        ]
//[-------------------------------------------------------]
int nsPluginInstance::Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments)
{
	// Error, this frontend implementation is run and controlled by another application this frontend is embedded into
	return -1;
}

PLCore::handle nsPluginInstance::GetNativeWindowHandle() const
{
	return reinterpret_cast<PLCore::handle>(m_hWnd);
}

void nsPluginInstance::Redraw()
{
	// Redraw frontend window
	RedrawWindow(m_hWnd, nullptr, nullptr, 0);
}

void nsPluginInstance::Ping()
{
	// Check if we're allowed to perform an update right now
	if (PLCore::Timing::GetInstance()->Update()) {
		// Let the frontend update it's states
		FrontendImpl::OnUpdate();
	}
}

PLCore::String nsPluginInstance::GetTitle() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return "";
}

void nsPluginInstance::SetTitle(const PLCore::String &sTitle)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

int nsPluginInstance::GetX() const
{
	// Get window rect (in screen coordinates)
	RECT sRect;
	::GetWindowRect(m_hWnd, &sRect);
	return sRect.left;
}

int nsPluginInstance::GetY() const
{
	// Get window rect (in screen coordinates)
	RECT sRect;
	::GetWindowRect(m_hWnd, &sRect);
	return sRect.top;
}

PLCore::uint32 nsPluginInstance::GetWidth() const
{
	// Request a relative window position (always (0, 0)) and size (equal to (width, height))
	RECT sRect;
	::GetClientRect(m_hWnd, &sRect);
	return sRect.right;
}

PLCore::uint32 nsPluginInstance::GetHeight() const
{
	// Request a relative window position (always (0, 0)) and size (equal to (width, height))
	RECT sRect;
	::GetClientRect(m_hWnd, &sRect);
	return sRect.bottom;
}

void nsPluginInstance::GetWindowPositionSize(int &nX, int &nY, PLCore::uint32 &nWidth, PLCore::uint32 &nHeight) const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into

	// Set known default values
	nX = nY = nWidth = nHeight = 0;
}

void nsPluginInstance::SetWindowPositionSize(int nX, int nY, PLCore::uint32 nWidth, PLCore::uint32 nHeight)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool nsPluginInstance::GetToggleFullscreenMode() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return false;
}

void nsPluginInstance::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool nsPluginInstance::GetFullscreenAltTab() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return false;
}

void nsPluginInstance::SetFullscreenAltTab(bool bAllowed)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool nsPluginInstance::IsFullscreen() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return false;
}

void nsPluginInstance::SetFullscreen(bool bFullscreen)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

void nsPluginInstance::RefreshFullscreen()
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool nsPluginInstance::IsMouseOver() const
{
	if (m_hWnd) {
		// Get the mouse cursor's position (in screen coordinates)
		POINT sPOINT;
		if (::GetCursorPos(&sPOINT)) {
			// Get window rectangle (in screen coordinates)
			RECT sRect;
			if (::GetWindowRect(m_hWnd, &sRect)) {
				// Is the mouse cursor within the window rectangle?
				return (::PtInRect(&sRect, sPOINT) == TRUE);
			}
		}
	}

	// Error!
	return false;
}

int nsPluginInstance::GetMousePositionX() const
{
	if (m_hWnd) {
		// Get the mouse cursor's position (in screen coordinates)
		POINT sPoint;
		::GetCursorPos(&sPoint);

		// Get the mouse cursor position inside this window
		if (::ScreenToClient(m_hWnd, &sPoint))
			return sPoint.x;
	}

	// Error!
	return -1;
}

int nsPluginInstance::GetMousePositionY() const
{
	if (m_hWnd) {
		// Get the mouse cursor's position (in screen coordinates)
		POINT sPoint;
		::GetCursorPos(&sPoint);

		// Get the mouse cursor position inside this window
		if (::ScreenToClient(m_hWnd, &sPoint))
			return sPoint.y;
	}

	// Error!
	return -1;
}

bool nsPluginInstance::IsMouseVisible() const
{
	return m_bMouseVisible;
}

void nsPluginInstance::SetMouseVisible(bool bVisible)
{
	// Backup the state
	m_bMouseVisible = bVisible;

	// Set mouse cursor visibility
	if (bVisible) {
		// Show mouse cursor
		while (::ShowCursor(true) < 0)
			; // Do nothing
	} else {
		// Hide mouse cursor
		while (::ShowCursor(false) >= 0)
			; // Do nothing
	}
}

void nsPluginInstance::SetTrapMouse(bool bTrap)
{
	if (m_hWnd) {
		// Trap mouse?
		if (bTrap) {
			// Get window rect (in screen coordinates)
			RECT sRect;
			::GetWindowRect(m_hWnd, &sRect);

			// Trap mouse
			::ClipCursor(&sRect); 
		} else {
			// Untrap mouse
			::ClipCursor(nullptr);
		}

		// Backup the state
		m_bTrapMouse = bTrap;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Update trap mouse if required
*/
void nsPluginInstance::UpdateTrapMouse()
{
	// Trap mouse?
	if (m_bTrapMouse) {
		// Get window rect (in screen coordinates)
		RECT sRect;
		::GetWindowRect(m_hWnd, &sRect);

		// Trap mouse within up-to-date widget rectangle
		::ClipCursor(&sRect); 
	}
}


static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  nsPluginInstance *pPlugin = reinterpret_cast<nsPluginInstance*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
  if (pPlugin) {
	  return pPlugin->ProcessMessage(hWnd, msg, wParam, lParam);
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}
