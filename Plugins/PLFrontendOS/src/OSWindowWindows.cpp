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
#include "PLFrontendOS/Frontend.h"
#include "PLFrontendOS/OSWindowWindows.h"


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
			pOSWindowWindows = reinterpret_cast<OSWindowWindows*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	// Disable screen saver and monitor power management...
	// [TODO] Always? Shouldn't this be an option?
//	if (nMsg == WM_SYSCOMMAND && (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER))
//		return 0;

	// If we get a message for a dead window, something is wrong
	if (pOSWindowWindows && pOSWindowWindows->m_bDestroyed) {
		// There is always a WM_NCDESTROY coming after WM_DESTROY, so this will be called which
		// is OK. But we don't need the message, so just give back here to be sure that nothing can go wrong...
		return DefWindowProc(hWnd, nMsg, wParam, lParam);
	}

	// We need a window now
	if (pOSWindowWindows != nullptr) {
		// Process message
		switch (nMsg) {
			// Initialize window
			case WM_CREATE:
				// Set window pointer and handle (SetWindowLongPtr is the 64bit equivalent to SetWindowLong)
				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pOSWindowWindows));
				pOSWindowWindows->m_hWnd = hWnd;

				// Show the window, but do not activate it right now
				ShowWindow(hWnd, SW_SHOWNOACTIVATE);

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

			case WM_PAINT:
			{
				// Begin paint
				PAINTSTRUCT sPaint;
				BeginPaint(hWnd, &sPaint);

				// [TODO]
				pOSWindowWindows->m_pFrontendOS->OnDraw();

				// End paint
				EndPaint(hWnd, &sPaint);
				return 0;
			}
		}
	}

	// Let the OS handle this message...
	return hWnd ? DefWindowProc(hWnd, nMsg, wParam, lParam) : 0;
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
	m_hInstance(GetModuleHandle(nullptr)),
	m_nThreadID(GetCurrentThreadId()),
	m_hWnd(nullptr),
	m_bDestroyed(false)
{
	// Tell the frontend about this instance at once because it may already be required during frontend lifecycle initialization
	m_pFrontendOS->m_pOSWindow = this;

	// Create window class
	m_WndClass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	m_WndClass.lpfnWndProc		= static_cast<WNDPROC>(WndProc);
	m_WndClass.cbClsExtra		= 0;
	m_WndClass.cbWndExtra		= 0;
	m_WndClass.hInstance		= m_hInstance;
	m_WndClass.hIcon			= nullptr;
	m_WndClass.hCursor			= LoadCursor(nullptr, IDC_ARROW);
	m_WndClass.hbrBackground	= nullptr;
	m_WndClass.lpszMenuName		= nullptr;
	m_WndClass.lpszClassName	= TEXT("PLFrontendOS_OSWindowWindows");

	// Register window class
	if (!RegisterClass(&m_WndClass)) {
		// Error registering window class
	}

	{ // Create the window
		// Get parent widget
		const HWND hParent = nullptr;

		// Set window style
		const DWORD dwStyle   = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		const DWORD dwExtStyle = 0;

		// Create widget
		m_hWnd = CreateWindowExA(dwExtStyle,
								 "PLFrontendOS_OSWindowWindows",
								 "",
								 dwStyle,
								 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								 hParent,
								 0,
								 GetModuleHandle(nullptr),
								 this);
		if (m_hWnd == nullptr) {
			// Could not create widget
			m_bDestroyed = true;
		}
	}

	// Do the frontend lifecycle thing - start
	m_pFrontendOS->OnStart();

	// Show and activate the window
	ShowWindow(m_hWnd, SW_SHOW);
}

/**
*  @brief
*    Destructor
*/
OSWindowWindows::~OSWindowWindows()
{
	// Check if the window has already been destroyed
	if (!m_bDestroyed) {
		// Send destroy message to window
		DestroyWindow(m_hWnd);
	}

	// Unregister window class
	if (!UnregisterClass(L"PLFrontendOS_OSWindowWindows", m_hInstance)) {
		// Error unregistering window class
	}
}


//[-------------------------------------------------------]
//[ Private virtual OSWindow functions                    ]
//[-------------------------------------------------------]
handle OSWindowWindows::GetNativeWindowHandle() const
{
	return reinterpret_cast<handle>(m_hWnd);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
