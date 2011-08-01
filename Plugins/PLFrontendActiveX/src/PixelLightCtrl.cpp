// PixelLightCtrl.cpp : Implementation of PixelLightCtrl
#include "stdafx.h"
#include "PixelLightCtrl.h"


// PixelLightCtrl

PixelLightCtrl::PixelLightCtrl() :
	m_cFrontend(*this)
{
	// We *must* have a real window for this control
	m_bWindowOnly = true;
}

PixelLightCtrl::~PixelLightCtrl()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLFrontend::FrontendImpl functions     ]
//[-------------------------------------------------------]
PLCore::handle PixelLightCtrl::GetWindowHandle() const
{
	return (PLCore::handle)m_hFrontendWnd;
}

PLCore::handle PixelLightCtrl::GetDeviceContext() const
{
	return (PLCore::handle)m_hFrontendDC;
}


//[-------------------------------------------------------]
//[ Private virtual PLFrontend::Impl functions            ]
//[-------------------------------------------------------]
void PixelLightCtrl::Redraw()
{
	// Redraw control
	RedrawWindow();
}

HRESULT PixelLightCtrl::OnDrawAdvanced(ATL_DRAWINFO &di)
{
	// Draw frontend
	FrontendImpl::OnDraw();

	// Done
	return S_OK;
}

LRESULT PixelLightCtrl::OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// Save window and device context handles
	m_hFrontendWnd = m_hWnd;
	m_hFrontendDC  = GetDC();

	// Initialize frontend
	FrontendImpl::OnInit();

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
	// Save new size
	m_nWidth  = LOWORD(lParam);
	m_nHeight = HIWORD(lParam);
	FrontendImpl::OnSize();

	// Done
	return 0;
}
