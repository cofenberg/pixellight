/*********************************************************\
 *  File: OSWindowWindows.cpp                            *
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
#include "../resource.h"
#include "PLFrontendOS/Frontend.h"
#include "PLFrontendOS/OSWindowWindows.h"
#include <Shellapi.h>	// For "ExtractIcon()"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static window callback function
*/
LRESULT CALLBACK OSWindowWindows::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	// Get pointer to window
	OSWindowWindows *pOSWindowWindows = nullptr;
	if (nMsg == WM_CREATE) {
		pOSWindowWindows = static_cast<OSWindowWindows*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
	} else {
		if (hWnd != nullptr)
			pOSWindowWindows = reinterpret_cast<OSWindowWindows*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	// Disable screen saver and monitor power management...
	if (nMsg == WM_SYSCOMMAND && (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER))
		return 0;

	// If we get a message for a dead window, something is wrong
	if (pOSWindowWindows && pOSWindowWindows->m_bDestroyed) {
		// There is always a WM_NCDESTROY coming after WM_DESTROY, so this will be called which
		// is OK. But we don't need the message, so just give back here to be sure that nothing can go wrong...
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);
	}

	// We need a window now
	if (pOSWindowWindows != nullptr) {
		// Process message
		switch (nMsg) {
			// Initialize window
			case WM_CREATE:
				// Set window pointer and handle (SetWindowLongPtr is the 64bit equivalent to SetWindowLong)
				::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pOSWindowWindows));
				pOSWindowWindows->m_hWnd = hWnd;

				// Show the window, but do not activate it right now
				::ShowWindow(hWnd, SW_SHOWNOACTIVATE);

				// Doing the following frontend lifecycle thing in here would be nice, but when done this way, the window border
				// will be potentially invisible until OnStart() returns... but this may take some seconds... not nice to look at...
				// pOSWindowWindows->m_pFrontendOS->OnStart();
				return 0;

			// Destroy window
			case WM_DESTROY:
				// Do the frontend lifecycle thing - stop
				pOSWindowWindows->m_pFrontendOS->OnStop();

				// Mark window destroyed
				pOSWindowWindows->m_bDestroyed = true;
				pOSWindowWindows->m_hWnd	   = nullptr;
				return 0;

			// Got focus
			case WM_SETFOCUS:
			case WM_EXITSIZEMOVE:	// Beside focus, do the same for moving/sizing a window - it just feels right this way
									// (e.g. no spinning around controlled camera while sizing a window)
				// Do the frontend lifecycle thing - resume
				pOSWindowWindows->m_pFrontendOS->OnResume();
				return 0;

			// Lost focus
			case WM_KILLFOCUS:
			case WM_ENTERSIZEMOVE:	// Beside focus, do the same for moving/sizing a window - it just feels right this way
									// (e.g. no spinning around controlled camera while sizing a window)
				// Do the frontend lifecycle thing - pause
				pOSWindowWindows->m_pFrontendOS->OnPause();
				return 0;

			case WM_SYSKEYDOWN:
				// Is it allowed to toggle the fullscreen mode using hotkeys? If so, toggle fullscreen right now?
				if (pOSWindowWindows->m_pFrontendOS->GetToggleFullscreenMode() && (lParam & (1 << 29)) && wParam == VK_RETURN) {	// Bit 29 = the ALT-key
					// Toggle fullscreen mode
					pOSWindowWindows->m_pFrontendOS->SetFullscreen(!pOSWindowWindows->m_pFrontendOS->IsFullscreen());
					return 0;
				}
				break;

			// Process hotkey
			case WM_HOTKEY:
				// We catched the hotkey
				return 0;

			case WM_PAINT:
			{
				// Begin paint
				::PAINTSTRUCT sPaint;
				::BeginPaint(hWnd, &sPaint);

				// Redraw, but only if the draw area isn't null
				if (!::IsRectEmpty(&sPaint.rcPaint)) {
					// Let the frontend draw into it's window
					pOSWindowWindows->m_pFrontendOS->OnDraw();
				}

				// End paint
				::EndPaint(hWnd, &sPaint);
				return 0;
			}
		}
	}

	// Let the OS handle this message...
	return hWnd ? ::DefWindowProc(hWnd, nMsg, wParam, lParam) : 0;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
OSWindowWindows::OSWindowWindows(Frontend &cFrontendOS) :
	m_pFrontendOS(&cFrontendOS),
	m_hInstance(::GetModuleHandle(nullptr)),
	m_nThreadID(::GetCurrentThreadId()),
	m_hWnd(nullptr),
	m_bDestroyed(false),
	m_nHotkeyIDAltTab(0),
	m_bWindowRectBackup(false)
{
	MemoryManager::Set(&m_sWindowRectBackup, 0, sizeof(RECT));

	// Tell the frontend about this instance at once because it may already be required during frontend lifecycle initialization
	m_pFrontendOS->m_pOSWindow = this;

	// Create window class
	m_WndClass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	m_WndClass.lpfnWndProc		= static_cast<WNDPROC>(WndProc);
	m_WndClass.cbClsExtra		= 0;
	m_WndClass.cbWndExtra		= 0;
	m_WndClass.hInstance		= m_hInstance;
	m_WndClass.hIcon			= nullptr;	// ... set below...
	m_WndClass.hCursor			= ::LoadCursor(nullptr, IDC_ARROW);
	m_WndClass.hbrBackground	= nullptr;
	m_WndClass.lpszMenuName		= nullptr;
	m_WndClass.lpszClassName	= TEXT("PLFrontendOS_OSWindowWindows");

	{ // Use the default process icon... if there's one...
		// Get the filename of this process
		wchar_t szModule[MAX_PATH];
		::GetModuleFileName(m_hInstance, szModule, sizeof(szModule));

		// Extract the icon (don't forget to call "DestroyIcon()" on it)
		m_WndClass.hIcon = m_hIcon = ::ExtractIcon(m_hInstance, szModule, 0);
	}

	// If there's no default process icon, we're using the standard PixelLight icon
	if (!m_WndClass.hIcon) {
		// "GetModuleHandle(nullptr)" returns the instance of the calling process, but for the icon we need the one of this shared library

		// Get the filename of this shared library
		MEMORY_BASIC_INFORMATION sMemoryBasicInformation;
		static const int nDummy = 0;
		::VirtualQuery(&nDummy, &sMemoryBasicInformation, sizeof(MEMORY_BASIC_INFORMATION));
		wchar_t szModule[MAX_PATH];
		::GetModuleFileName(static_cast<HMODULE>(sMemoryBasicInformation.AllocationBase), szModule, sizeof(szModule));

		// Finally, load the icon with the instance of this shared library
		m_WndClass.hIcon = ::LoadIcon(::GetModuleHandle(szModule), MAKEINTRESOURCE(IDI_PL));
	}

	// Register window class
	if (::RegisterClass(&m_WndClass)) {
		// Set window style
		const DWORD dwStyle    = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		const DWORD dwExtStyle = 0;

		// Create the window
		m_hWnd = ::CreateWindowExA(dwExtStyle,
								  "PLFrontendOS_OSWindowWindows",
								   "",
								   dwStyle,
								   CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								   HWND_DESKTOP,
								   0,
								   ::GetModuleHandle(nullptr),
								   this);
		if (m_hWnd) {
			// Do the frontend lifecycle thing - start
			m_pFrontendOS->OnStart();

			// Show and activate the window
			::SetForegroundWindow(m_hWnd);
		} else {
			// Could not create widget
			m_bDestroyed = true;
		}
	} else {
		// Error registering window class
	}
}

/**
*  @brief
*    Destructor
*/
OSWindowWindows::~OSWindowWindows()
{
	// Check if the window has already been destroyed
	if (m_hWnd) {
		// Send destroy message to window
		::DestroyWindow(m_hWnd);
	}

	// Unregister window class
	if (!::UnregisterClass(L"PLFrontendOS_OSWindowWindows", m_hInstance)) {
		// Error unregistering window class
	}

	// Is there an extracted icon to destroy?
	if (m_hIcon)
		::DestroyIcon(m_hIcon);
}

int OSWindowWindows::RegisterHotkey(UINT nModKey, UINT nKey)
{
	if (m_hWnd) {
		// Get new hotkey ID
		static int nHotkeyID = 0xC000;
		nHotkeyID++;

		// Register hotkey
		::RegisterHotKey(m_hWnd, nHotkeyID, nModKey, nKey);
		return nHotkeyID;
	} else {
		// Error!
		return 0;
	}
}

void OSWindowWindows::UnregisterHotkey(int nID)
{
	// Unregister hotkey
	if (m_hWnd)
		::UnregisterHotKey(m_hWnd, nID);
}


//[-------------------------------------------------------]
//[ Private virtual OSWindow functions                    ]
//[-------------------------------------------------------]
handle OSWindowWindows::GetNativeWindowHandle() const
{
	return reinterpret_cast<handle>(m_hWnd);
}

void OSWindowWindows::Redraw()
{
	if (m_hWnd)
		::RedrawWindow(m_hWnd, nullptr, nullptr, RDW_INVALIDATE);
}

bool OSWindowWindows::Ping()
{
	bool bQuit = false;

	// Look if messages are waiting (non-blocking)
	MSG sMsg;
	while (::PeekMessage(&sMsg, nullptr, 0, 0, PM_NOREMOVE)) {
		// Get the waiting message
		::GetMessage(&sMsg, nullptr, 0, 0);
		if (sMsg.message == WM_QUIT)
			bQuit = true;

		// Process message
		::TranslateMessage(&sMsg);
		::DispatchMessage(&sMsg);
	}

	// Done
	return bQuit;
}

uint32 OSWindowWindows::GetWidth() const
{
	if (m_hWnd) {
		RECT sRect;
		::GetClientRect(m_hWnd, &sRect);
		return sRect.right;
	} else {
		return 0;
	}
}

uint32 OSWindowWindows::GetHeight() const
{
	if (m_hWnd) {
		RECT sRect;
		::GetClientRect(m_hWnd, &sRect);
		return sRect.bottom;
	} else {
		return 0;
	}
}

void OSWindowWindows::SetFullscreenAltTab(bool bAllowed)
{
	if (m_hWnd) {
		// Register/unregister hotkey
		if (bAllowed && m_pFrontendOS->IsFullscreen()) {
			// Catch Alt-Tab hotkey so it can't be used during fullscreen
			if (!m_nHotkeyIDAltTab)
				m_nHotkeyIDAltTab = RegisterHotkey(MOD_ALT, VK_TAB);
		} else {
			// Release Alt-Tab hotkey
			if (m_nHotkeyIDAltTab) {
				UnregisterHotkey(m_nHotkeyIDAltTab);
				m_nHotkeyIDAltTab = 0;
			}
		}
	}
}

void OSWindowWindows::SetFullscreen(bool bFullscreen)
{
	if (m_hWnd) {
		// Update fullscreen Alt-Tab
		SetFullscreenAltTab(m_pFrontendOS->GetFullscreenAltTab());

		// Backup the current window position & size?
		if (bFullscreen && !m_bWindowRectBackup) {
			GetWindowRect(m_hWnd, &m_sWindowRectBackup);
			m_bWindowRectBackup = true;
		}

		{ // Update window style
			// Get the current window style
			LONG nStyle = GetWindowLong(m_hWnd, GWL_STYLE);

			// Modify the current window style
			if (bFullscreen)
				nStyle &= ~(WS_BORDER | WS_CAPTION | WS_THICKFRAME);	// Hide decoration
			else
				nStyle |= (WS_BORDER | WS_CAPTION | WS_THICKFRAME);		// Show decoration

			// Set the new window style
			SetWindowLong(m_hWnd, GWL_STYLE, nStyle);
		}

		// Inform that the fullscreen mode was changed
		m_pFrontendOS->OnFullscreenMode();

		// Switch to fullscreen?
		if (bFullscreen) {
			// For fullscreen, place the window left/top and set new size
			::SetWindowPos(m_hWnd, nullptr, 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN), SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED);
		} else {
			// Restore window position & size
			if (m_bWindowRectBackup) {
				::SetWindowPos(m_hWnd, nullptr, m_sWindowRectBackup.left, m_sWindowRectBackup.top, m_sWindowRectBackup.right - m_sWindowRectBackup.left,
							   m_sWindowRectBackup.bottom - m_sWindowRectBackup.top, SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED);
				m_bWindowRectBackup = false;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
