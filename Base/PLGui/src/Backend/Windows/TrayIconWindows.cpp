/*********************************************************\
 *  File: TrayIconWindows.cpp                            *
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
#include "PLGui/PLGuiWindowsIncludes.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/TrayIcon.h"
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Backend/Windows/ImageWindows.h"
#include "PLGui/Backend/Windows/TrayIconWindows.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Global definitions                                    ]
//[-------------------------------------------------------]
#define PL_TRAYICON		(WM_USER + 110)		// Tray icon message


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TrayIconWindows::TrayIconWindows(TrayIcon &cTrayIcon) : TrayIconImpl(cTrayIcon),
	m_pWindow(nullptr),
	m_nID(101),
	m_bVisible(false)
{
}

/**
*  @brief
*    Destructor
*/
TrayIconWindows::~TrayIconWindows()
{
	// Destroy tray icon
	DestroyTrayIcon();
}


//[-------------------------------------------------------]
//[ Private virtual TrayIconImpl functions                ]
//[-------------------------------------------------------]
void TrayIconWindows::CreateTrayIcon()
{
	// The tray icon will be created and deleted whenever it is made visible/invisible, so don't do anything here
}

void TrayIconWindows::DestroyTrayIcon()
{
	// Remove tray icon
	SetVisible(false);
}

void TrayIconWindows::SetVisible(bool bVisible)
{
	// As NIM_HIDDEN doesn't seem to work on my computer, just use add and remove instead ...
	if (!m_bVisible && bVisible) {
		// Create helper window
		if (!m_pWindow) {
			// [TODO] Pass GUI here somehow
			m_pWindow = new Widget();
			m_pWindow->SetUserData(static_cast<void*>(m_pTrayIcon));
		}

		// Get icon handle
		ImageWindows *pImageWindows = static_cast<ImageWindows*>(m_pTrayIcon->GetIcon().GetImpl());
		HICON hIcon = pImageWindows ? pImageWindows->GetIconHandle() : LoadIcon(nullptr, IDI_QUESTION);

		// Set options to create the icon
		memset(&m_sNotifyIcon, 0, sizeof(NOTIFYICONDATA));
		m_sNotifyIcon.cbSize			= sizeof(NOTIFYICONDATA);
		m_sNotifyIcon.hWnd				= reinterpret_cast<HWND>(m_pWindow->GetNativeWindowHandle());
		m_sNotifyIcon.uID				= m_nID;
		m_sNotifyIcon.uFlags			= NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_sNotifyIcon.uCallbackMessage	= PL_TRAYICON;
		m_sNotifyIcon.uVersion			= NOTIFYICON_VERSION;
		m_sNotifyIcon.hIcon				= hIcon;
		String sTooltip					= m_pTrayIcon->GetTooltip();
		wcsncpy_s(m_sNotifyIcon.szTip, 64, sTooltip.GetUnicode(), sTooltip.GetLength()+1);

		// Create notify icon
		Shell_NotifyIcon(NIM_ADD, &m_sNotifyIcon);

		// Tray icon visible
		m_bVisible = true;
	} else if (m_bVisible && !bVisible) {
		// Set options to destroy the tray icon
		NOTIFYICONDATA sNotifyIcon;
		memset(&sNotifyIcon, 0, sizeof(NOTIFYICONDATA));
		sNotifyIcon.cbSize	= sizeof(NOTIFYICONDATA);
		sNotifyIcon.hWnd	= reinterpret_cast<HWND>(m_pWindow->GetNativeWindowHandle());
		sNotifyIcon.uID		= m_nID;
		sNotifyIcon.uFlags	= 0;

		// Delete notify icon
		Shell_NotifyIcon(NIM_DELETE, &sNotifyIcon);

		// Tray icon destroyed
		m_bVisible = false;
	}
}

void TrayIconWindows::Update()
{
	// Only change something, if the tray icon is visible (otherwise it will be updated automatically by SetVisible)
	if (m_bVisible) {
		// Get ImageWindows implementation
		ImageWindows *pImageWindows = static_cast<ImageWindows*>(m_pTrayIcon->GetIcon().GetImpl());
		HICON hIcon = pImageWindows->GetIconHandle();

		// Set options for tray icon
		NOTIFYICONDATA sNotifyIcon;
		memset(&sNotifyIcon, 0, sizeof(NOTIFYICONDATA));
		sNotifyIcon.cbSize	= sizeof(NOTIFYICONDATA);
		sNotifyIcon.hWnd	= reinterpret_cast<HWND>(m_pWindow->GetNativeWindowHandle());
		sNotifyIcon.uID		= m_nID;
		sNotifyIcon.uFlags	= NIF_ICON | NIF_TIP;
		sNotifyIcon.hIcon	= hIcon;
		String sTooltip		= m_pTrayIcon->GetTooltip();
		wcsncpy_s(sNotifyIcon.szTip, 64, sTooltip.GetUnicode(), sTooltip.GetLength()+1);

		// Modify notify icon
		Shell_NotifyIcon(NIM_MODIFY, &sNotifyIcon);
	}
}

void TrayIconWindows::ShowNotification(const String &sTitle, const String &sText)
{
	// Set ballon tooltip options
	m_sNotifyIcon.uFlags = NIF_INFO;
	wcsncpy_s(m_sNotifyIcon.szInfo, sText.GetUnicode(), sText.GetLength()+1);
	wcsncpy_s(m_sNotifyIcon.szInfoTitle, sTitle.GetUnicode(), sTitle.GetLength()+1);
	m_sNotifyIcon.dwInfoFlags = NIIF_USER | NIIF_NOSOUND;
	m_sNotifyIcon.uTimeout = 10000;

	// Modify tray icon
	Shell_NotifyIcon (NIM_MODIFY, &m_sNotifyIcon);

	// Reset text for it not to reappear later (necessary?)
	m_sNotifyIcon.szInfo[0] = 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
