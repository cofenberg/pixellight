/*********************************************************\
 *  File: WidgetWindows.cpp                              *
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
#include "PLGui/Gui/Base/GuiMessage.h"
#include "PLGui/Gui/Resources/Cursor.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Screen.h"
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Backend/Windows/WidgetWindows.h"
#include "PLGui/Backend/Windows/ImageWindows.h"
#include "PLGui/Backend/Windows/CursorWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLMath;
namespace PLGui
{


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WidgetWindows::WidgetWindows(Widget &cWidget) : WidgetImpl(cWidget),
	m_hWnd(nullptr),
	m_bWrapper(false),
	m_bDestroyed(false),
	m_nWindowState(StateNormal),
	m_bFullscreen(false),
	m_bShowInTaskbar(false),
	m_nTransparency(NoTransparency),
	m_bIgnoreSetFocus(false),
	m_bTrapMouse(false)
{
}

/**
*  @brief
*    Destructor
*/
WidgetWindows::~WidgetWindows()
{
	// If not done already, destroy the widget
	if (!m_bWrapper) {
		Destroy();
	}
}


//[-------------------------------------------------------]
//[ Public virtual WidgetImpl functions                   ]
//[-------------------------------------------------------]
void WidgetWindows::CreateWidget()
{
	// Get parent widget
	HWND hParent = m_pWidget->GetParent() ? (HWND)m_pWidget->GetParent()->GetWindowHandle() : nullptr;

	// Set window style
	uint32 nWinStyle, nExtStyle;
	GetWindowStyle(nWinStyle, nExtStyle);

	// Create widget
	m_hWnd = CreateWindowExA(nExtStyle,
							 "PLGuiWidget",
							 "",
							 nWinStyle,
							 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							 hParent,
							 0,
							 GetModuleHandle(nullptr),
							 this);
	if (m_hWnd == nullptr) {
		// Could not create widget
		m_hWnd = nullptr;
		m_bDestroyed = true;
		return;
	}
}

void WidgetWindows::CreateWrapperWidget(handle nWindowHandle)
{
	// Mark as wrapper widget
	m_bWrapper = true;

	// Save window handle
	m_hWnd = (HWND)nWindowHandle;
}

bool WidgetWindows::IsDestroyed() const
{
	// Return destroyed-flag
	return m_bDestroyed;
}

void WidgetWindows::Destroy()
{
	// Check if the widget has already been destroyed
	if (!m_bDestroyed) {
		// Send destroy message to widget
		DestroyWindow(m_hWnd);
	}
}

handle WidgetWindows::GetWindowHandle() const
{
	// Return window handle
	return (handle)m_hWnd;
}

void WidgetWindows::SetParent(WidgetImpl *pParent)
{
	// [TODO] Implement SetParent functionality
	/*
	// Get parent widget
	HWND hParent = nullptr;
	if (m_pWidget->GetParentWidget()) {
		hParent = m_pWidget->GetParentWidget()->GetWindowHandle();
	}

	// Set new parent widget
	::SetParent(m_hWnd, hParent);
	*/
}

bool WidgetWindows::IsShowInTaskbar() const
{
	// Check flag
	return m_bShowInTaskbar;
}

void WidgetWindows::SetShowInTaskbar(bool bShowInTaskbar)
{
	// Update flag
	m_bShowInTaskbar = bShowInTaskbar;

	// Update window style
	bool bVisible = IsVisible();
	SetVisible(false);
	UpdateWindowStyle();
	SetVisible(bVisible);
}

void WidgetWindows::MoveToScreen(Screen &cScreen)
{
	// Set position to upper left corner of screen
	m_pWidget->SetPos(cScreen.GetPos());
}

Vector2i WidgetWindows::GetPos() const
{
	// Get window rect
	RECT sWindowRect;
	GetWindowRect(m_hWnd, &sWindowRect);

	// Get parent rect to get a result relative to the parent widget
	RECT sParentRect;
	sParentRect.left = sParentRect.top = 0;
	if (m_pWidget->GetParent()) {
		GetWindowRect((HWND)m_pWidget->GetParent()->GetWindowHandle(), &sParentRect);
	}

	// Get position
	return Vector2i(sWindowRect.left - sParentRect.left, sWindowRect.top  - sParentRect.top);
}

void WidgetWindows::SetPos(const Vector2i &vPos)
{
	Vector2i vSize = GetSize();
	MoveWindow(m_hWnd, vPos.x, vPos.y, vSize.x, vSize.y, true);

	// Update trap mouse if required
	UpdateTrapMouse();
}

Vector2i WidgetWindows::GetSize() const
{
	// Get client rect
	RECT sRect;
	GetClientRect(m_hWnd, &sRect);

	// Return size
	return Vector2i(sRect.right, sRect.bottom);
}

void WidgetWindows::SetSize(const Vector2i &vSize)
{
	Vector2i vPos = GetPos();
	MoveWindow(m_hWnd, vPos.x, vPos.y, vSize.x, vSize.y, true);

	// Update trap mouse if required
	UpdateTrapMouse();
}

void WidgetWindows::SetZPos(EZPos nZPos, Widget *pWidget)
{
	// Get handle to widget that will be on top of our widget
	HWND hWndAfter = nullptr;
	if (nZPos == ZBehind && pWidget) {
		// This widget will be in front of our widget
		hWndAfter = (HWND)pWidget->GetWindowHandle();
	} else if (nZPos == ZAbove && pWidget) {
		// This widget will be behind our widget
		hWndAfter = GetNextWindow((HWND)pWidget->GetWindowHandle(), GW_HWNDPREV);
		if (!hWndAfter) hWndAfter = HWND_TOP;
	} else if (nZPos == ZTop) {
		// Our widget will be on top of the screen
		hWndAfter = HWND_TOP;
	} else if (nZPos == ZBottom) {
		// Our widget will be on the bottom
		hWndAfter = HWND_BOTTOM;
	}

	// Set Z position
	SetWindowPos((HWND)GetWindowHandle(), hWndAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

bool WidgetWindows::IsTopmost() const
{
	// Check if window has the WS_EX_TOPMOST style set
	LONG_PTR nExtStyle = ::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);
	return ((nExtStyle & WS_EX_TOPMOST) != 0);
}

void WidgetWindows::SetTopmost(bool bTopmost)
{
	// Get position and size
	Vector2i vPos  = GetPos();
	Vector2i vSize = GetSize();

	// Choose show command
	HWND   hPos  =    bTopmost ? HWND_TOPMOST   : HWND_NOTOPMOST;
	uint32 nShow = IsVisible() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

	// Set widget position
	SetWindowPos(m_hWnd, hPos, vPos.x, vPos.y, vSize.x, vSize.y, nShow | SWP_NOACTIVATE);
}

EWindowState WidgetWindows::GetWindowState() const
{
	// Return window state
	return m_nWindowState;
}

void WidgetWindows::SetWindowState(EWindowState nWindowState)
{
	// Has something changed?
	if (m_nWindowState != nWindowState) {
		// Save fullscreen-mode
		m_bFullscreen = (nWindowState == StateFullscreen);

		// Change window state
		if (nWindowState == StateMinimized) {
			ShowWindow(m_hWnd, SW_MINIMIZE);
		} else if (nWindowState == StateMaximized) {
			ShowWindow(m_hWnd, SW_MAXIMIZE);
		} else if (nWindowState == StateNormal) {
			ShowWindow(m_hWnd, SW_SHOWNORMAL);
		} else if (nWindowState == StateFullscreen) {
			ShowWindow(m_hWnd, SW_MAXIMIZE);
		}

		// Save new window state
		m_nWindowState = nWindowState;
	}
}

void WidgetWindows::SetTransparency(ETransparency nTransparency, const Color4 &cColor)
{
	// Set transparency mode
	m_nTransparency = nTransparency;

	// Update only extended window style
	UpdateWindowStyle(true);

	// Check type of transparency
	if (m_nTransparency == ColorKeyTransparency) {
		// Use color key
		SetLayeredWindowAttributes(m_hWnd,
								   RGB(cColor.GetRInt(), cColor.GetGInt(), cColor.GetBInt()),
								   cColor.GetAInt(),
								   LWA_COLORKEY);
	} else if (m_nTransparency == AlphaTransparency) {
		// Use alpha value
		SetLayeredWindowAttributes(m_hWnd, 0, cColor.GetAInt(), LWA_ALPHA);
	} else {
		// Redraw widget
		InvalidateRect(m_hWnd, nullptr, true);
		UpdateWindow(m_hWnd);
	}
}

bool WidgetWindows::IsVisible() const
{
	// Return widget's visibility
	return (IsWindowVisible(m_hWnd) > 0);
}

void WidgetWindows::SetVisible(bool bVisible)
{
	// Shall the window be activated?
	ShowWindow(m_hWnd, bVisible ? SW_SHOWNA : SW_HIDE);
}

bool WidgetWindows::IsEnabled() const
{
	// Return widget's state
	return (IsWindowEnabled(m_hWnd) > 0);
}

void WidgetWindows::SetEnabled(bool bEnabled)
{
	// Enable or disable window
	EnableWindow(m_hWnd, bEnabled ? TRUE : FALSE);
}

void WidgetWindows::Activate()
{
	::SetForegroundWindow(m_hWnd);
}

void WidgetWindows::SetFocus()
{
	// Set focus to widget
	::SetFocus(m_hWnd);
}

void WidgetWindows::Redraw()
{
	// Redraw widget
	InvalidateRect(m_hWnd, nullptr, true);
	UpdateWindow(m_hWnd);
}

void WidgetWindows::SetCaptureMouse(bool bCapture)
{
	if (bCapture) SetCapture(m_hWnd);
	else		  ReleaseCapture();
}

void WidgetWindows::SetTrapMouse(bool bTrap)
{
	// Trap mouse?
	if (bTrap) {
		// Get window rect (in screen coordinates)
		RECT sRect;
		GetWindowRect(m_hWnd, &sRect); 

		// Trap mouse
		ClipCursor(&sRect); 
	} else {
		// Untrap mouse
		ClipCursor(nullptr);
	}

	// Backup the state
	m_bTrapMouse = bTrap;
}

uint32 WidgetWindows::RegisterHotkey(uint32 nModKey, uint32 nKey)
{
	// Get new hotkey ID
	static uint32 nHotkeyID = 0xC000;
	nHotkeyID++;

	// Register hotkey
	::RegisterHotKey(m_hWnd, nHotkeyID, nModKey, nKey);
	return nHotkeyID;
}

void WidgetWindows::UnregisterHotkey(uint32 nID)
{
	// Unregister hotkey
	::UnregisterHotKey(m_hWnd, nID);
}

void WidgetWindows::SetTitle(const String &sTitle)
{
	// Set widget title
	if (sTitle.GetFormat() == String::ASCII)	SetWindowTextA(m_hWnd, sTitle.GetASCII());
	else										SetWindowTextW(m_hWnd, sTitle.GetUnicode());
}

void WidgetWindows::SetIcon(const Image &cIcon)
{
	// Get icon handle
	ImageWindows *pImageWindows = (ImageWindows*)cIcon.GetImpl();
	HICON hIcon = pImageWindows ? pImageWindows->GetIconHandle() : nullptr;

	// Set icon
	::SendMessageA(m_hWnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
	::SendMessageA(m_hWnd, WM_SETICON, (WPARAM)ICON_BIG,   (LPARAM)hIcon);
}

void WidgetWindows::SetCursor(const Cursor &cCursor)
{
	// Set mouse cursor to what is specified for the particular window
	::SetCursor(((CursorWindows*)m_pWidget->GetCursor().GetImpl())->GetHandle());
}

bool WidgetWindows::GetMousePos(Vector2i &vPos)
{
	// Get the absolute mouse cursor position on the screen
	POINT sPoint;
	::GetCursorPos(&sPoint);

	// This backend function is only called if the mouse is currently over the window, as a result, we don't
	// need to perform a test like "if (::WindowFromPoint(sPoint) == m_hWnd)"

	// Get the mouse cursor position inside this window
	::ScreenToClient(m_hWnd, &sPoint);

	// Write out the mouse cursor position inside this window
	vPos.x = sPoint.x;
	vPos.y = sPoint.y;

	// Done, the mouse cursor is currently over this window
	return true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get window style according to the current state and options of the window
*/
void WidgetWindows::GetWindowStyle(uint32 &nWinStyle, uint32 &nExtStyle)
{
	nWinStyle = 0;
	nExtStyle = 0;

	// Set base style
	nWinStyle = (m_pWidget->GetParent() ? WS_CHILD : WS_POPUP);
	nExtStyle = 0;

	// Clip siblings
	nWinStyle |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Accept drag&drop of files
	nExtStyle |= WS_EX_ACCEPTFILES;

	// Use transparent (layered) window?
	if (m_nTransparency == ColorKeyTransparency || m_nTransparency == AlphaTransparency)
		nExtStyle |= WS_EX_LAYERED;

	// Show window in taskbar?
	if (m_bShowInTaskbar) {
		// Show window in toolbar
		nExtStyle |= WS_EX_APPWINDOW;

		// Add system menu
		nWinStyle |= WS_SYSMENU;
	} else {
		// Hide window from toolbar
		nExtStyle |= WS_EX_TOOLWINDOW;
	}
}

/**
*  @brief
*    Update window style of the widget
*/
void WidgetWindows::UpdateWindowStyle(bool bExtOnly)
{
	// Get new window style
	uint32 nWinStyle, nExtStyle;
	GetWindowStyle(nWinStyle, nExtStyle);

	// Apply window style
	if (!bExtOnly)
		::SetWindowLongPtr(m_hWnd, GWL_STYLE,	nWinStyle);
	::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, nExtStyle);
	::SetWindowPos(m_hWnd, nullptr, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

/**
*  @brief
*    Update trap mouse if required
*/
void WidgetWindows::UpdateTrapMouse()
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
