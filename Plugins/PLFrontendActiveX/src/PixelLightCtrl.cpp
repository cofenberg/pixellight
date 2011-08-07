// PixelLightCtrl.cpp : Implementation of PixelLightCtrl
#include <PLCore/Tools/Timing.h>
#include "stdafx.h"
#include "PixelLightCtrl.h"


// PixelLightCtrl

PixelLightCtrl::PixelLightCtrl() :
	m_cFrontend(*this),
	m_bFrontendApplicationInitialized(false)
{
	// We *must* have a real window for this control
	m_bWindowOnly = true;

	// Do the frontend lifecycle thing - let the world know that we have been created
	FrontendImpl::OnCreate();
}

PixelLightCtrl::~PixelLightCtrl()
{
	// Do the frontend lifecycle thing - de-initialize
	if (m_bFrontendApplicationInitialized) {
		FrontendImpl::OnPause();
		FrontendImpl::OnStop();
	}

	// Do the frontend lifecycle thing - let the world know that we're going to die
	FrontendImpl::OnDestroy();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::Impl functions                ]
//[-------------------------------------------------------]
int PixelLightCtrl::Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments, const PLCore::String &sApplicationClass)
{
	// Error, this frontend implementation is run and controlled by another application this frontend is embeded into
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

PLCore::uint32 PixelLightCtrl::GetWidth() const
{
	RECT sRect;
	::GetClientRect(m_hFrontendWnd, &sRect);
	return sRect.right;
}

PLCore::uint32 PixelLightCtrl::GetHeight() const
{
	RECT sRect;
	::GetClientRect(m_hFrontendWnd, &sRect);
	return sRect.bottom;
}

bool PixelLightCtrl::GetToggleFullscreenMode() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embeded into
	return false;
}

void PixelLightCtrl::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embeded into
}

bool PixelLightCtrl::GetFullscreenAltTab() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embeded into
	return false;
}

void PixelLightCtrl::SetFullscreenAltTab(bool bAllowed)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embeded into
}

bool PixelLightCtrl::IsFullscreen() const
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embeded into
	return false;
}

void PixelLightCtrl::SetFullscreen(bool bFullscreen)
{
	// Ignore - This frontend implementation is run and controlled by another application this frontend is embeded into
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

	// Do the frontend lifecycle thing - initialize
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

LRESULT PixelLightCtrl::OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// Inform that the window size has been changed
	FrontendImpl::OnSize();

	// Done
	return 0;
}
