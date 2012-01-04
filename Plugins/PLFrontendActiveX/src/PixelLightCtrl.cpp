// PixelLightCtrl.cpp : Implementation of PixelLightCtrl
#include <PLCore/Runtime.h>
#include <PLCore/Tools/Timing.h>
#include "stdafx.h"
#include "PixelLightCtrl.h"


// PixelLightCtrl

PixelLightCtrl::PixelLightCtrl() :
	m_bFrontendApplicationInitialized(false),
	m_bMouseVisible(true),
	m_bTrapMouse(false),
	m_cFrontend(m_cFrontendContext, *this)
{
	// We *must* have a real window for this control
	m_bWindowOnly = true;

	// Scan PL-runtime directory for compatible plugins and load them in as well as scan for compatible data and register it
	PLCore::Runtime::ScanDirectoryPluginsAndData();

	// Do the frontend life cycle thing - let the world know that we have been created
	FrontendImpl::OnCreate();
}

PixelLightCtrl::~PixelLightCtrl()
{
	// Do the frontend life cycle thing - de-initialize
	if (m_bFrontendApplicationInitialized) {
		FrontendImpl::OnPause();
		FrontendImpl::OnStop();
	}

	// Do the frontend life cycle thing - let the world know that we're going to die
	FrontendImpl::OnDestroy();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::Impl functions                ]
//[-------------------------------------------------------]
int PixelLightCtrl::Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments)
{
	// Error, this frontend implementation is run and controlled by another application this frontend is embedded into
	return -1;
}

PLCore::handle PixelLightCtrl::GetNativeWindowHandle() const
{
	return reinterpret_cast<PLCore::handle>(m_hFrontendWnd);
}

void PixelLightCtrl::Redraw()
{
	// Redraw control
	RedrawWindow();
}

void PixelLightCtrl::Ping()
{
	// Check if we're allowed to perform an update right now
	if (PLCore::Timing::GetInstance()->Update()) {
		// Let the frontend update it's states
		FrontendImpl::OnUpdate();
	}
}

PLCore::String PixelLightCtrl::GetTitle() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return "";
}

void PixelLightCtrl::SetTitle(const PLCore::String &sTitle)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

int PixelLightCtrl::GetX() const
{
	// Get window rect (in screen coordinates)
	RECT sRect;
	GetWindowRect(&sRect);
	return sRect.left;
}

int PixelLightCtrl::GetY() const
{
	// Get window rect (in screen coordinates)
	RECT sRect;
	GetWindowRect(&sRect);
	return sRect.top;
}

PLCore::uint32 PixelLightCtrl::GetWidth() const
{
	// Request a relative window position (always (0, 0)) and size (equal to (width, height))
	RECT sRect;
	GetClientRect(&sRect);
	return sRect.right;
}

PLCore::uint32 PixelLightCtrl::GetHeight() const
{
	// Request a relative window position (always (0, 0)) and size (equal to (width, height))
	RECT sRect;
	GetClientRect(&sRect);
	return sRect.bottom;
}

void PixelLightCtrl::GetWindowPositionSize(int &nX, int &nY, PLCore::uint32 &nWidth, PLCore::uint32 &nHeight) const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into

	// Set known default values
	nX = nY = nWidth = nHeight = 0;
}

void PixelLightCtrl::SetWindowPositionSize(int nX, int nY, PLCore::uint32 nWidth, PLCore::uint32 nHeight)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool PixelLightCtrl::GetToggleFullscreenMode() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return false;
}

void PixelLightCtrl::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool PixelLightCtrl::GetFullscreenAltTab() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return false;
}

void PixelLightCtrl::SetFullscreenAltTab(bool bAllowed)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool PixelLightCtrl::IsFullscreen() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
	return false;
}

void PixelLightCtrl::SetFullscreen(bool bFullscreen)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

void PixelLightCtrl::RefreshFullscreen()
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embedded into
}

bool PixelLightCtrl::IsMouseOver() const
{
	// Get the mouse cursor's position (in screen coordinates)
	POINT sPOINT;
	if (GetCursorPos(&sPOINT)) {
		// Get window rectangle (in screen coordinates)
		RECT sRect;
		if (GetWindowRect(&sRect)) {
			// Is the mouse cursor within the window rectangle?
			return (PtInRect(&sRect, sPOINT) == TRUE);
		}
	}

	// Error!
	return false;
}

int PixelLightCtrl::GetMousePositionX() const
{
	if (m_hFrontendWnd) {
		// Get the mouse cursor's position (in screen coordinates)
		POINT sPoint;
		::GetCursorPos(&sPoint);

		// Get the mouse cursor position inside this window
		if (::ScreenToClient(m_hFrontendWnd, &sPoint))
			return sPoint.x;
	}

	// Error!
	return -1;
}

int PixelLightCtrl::GetMousePositionY() const
{
	if (m_hFrontendWnd) {
		// Get the mouse cursor's position (in screen coordinates)
		POINT sPoint;
		::GetCursorPos(&sPoint);

		// Get the mouse cursor position inside this window
		if (::ScreenToClient(m_hFrontendWnd, &sPoint))
			return sPoint.y;
	}

	// Error!
	return -1;
}

bool PixelLightCtrl::IsMouseVisible() const
{
	return m_bMouseVisible;
}

void PixelLightCtrl::SetMouseVisible(bool bVisible)
{
	// Backup the state
	m_bMouseVisible = bVisible;

	// Set mouse cursor visibility
	if (bVisible) {
		// Show mouse cursor
		while (ShowCursor(true) < 0)
			; // Do nothing
	} else {
		// Hide mouse cursor
		while (ShowCursor(false) >= 0)
			; // Do nothing
	}
}

void PixelLightCtrl::SetTrapMouse(bool bTrap)
{
	if (m_hFrontendWnd) {
		// Trap mouse?
		if (bTrap) {
			// Get window rect (in screen coordinates)
			RECT sRect;
			GetWindowRect(&sRect);

			// Trap mouse
			ClipCursor(&sRect); 
		} else {
			// Untrap mouse
			ClipCursor(nullptr);
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
void PixelLightCtrl::UpdateTrapMouse()
{
	// Trap mouse?
	if (m_bTrapMouse) {
		// Get window rect (in screen coordinates)
		RECT sRect;
		::GetWindowRect(m_hFrontendWnd, &sRect);

		// Trap mouse within up-to-date widget rectangle
		::ClipCursor(&sRect); 
	}
}


HRESULT PixelLightCtrl::OnDrawAdvanced(ATL_DRAWINFO &di)
{
	// Let the frontend draw into it's window
	FrontendImpl::OnDraw();

	// Ping
	Ping();

	// Done
	return S_OK;
}

LRESULT PixelLightCtrl::OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// Save window and device context handles
	m_hFrontendWnd = m_hWnd;

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

	// Done
	return 0;
}

LRESULT PixelLightCtrl::OnEraseBkgnd(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// No background, please
	return 0;
}


// [TODO] React on move messages
	// Update trap mouse if required
//	UpdateTrapMouse();


// [TODO] Drag and drop of files


LRESULT PixelLightCtrl::OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// Update trap mouse if required
	UpdateTrapMouse();

	// Inform that the window size has been changed
	FrontendImpl::OnSize();

	// Done
	return 0;
}
