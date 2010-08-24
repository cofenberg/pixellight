// PixelLightCtrl.cpp : Implementation of PixelLightCtrl
#include "stdafx.h"
#include "PixelLightCtrl.h"


// PixelLightCtrl

PixelLightCtrl::PixelLightCtrl() :
	m_cPlugin(*this)
{
	// We *must* have a real window for this control
	m_bWindowOnly = true;
}

PixelLightCtrl::~PixelLightCtrl()
{
}


//[-------------------------------------------------------]
//[ Private virtual PluginImpl functions                  ]
//[-------------------------------------------------------]
void PixelLightCtrl::Redraw()
{
	// Redraw control
	RedrawWindow();
}

HRESULT PixelLightCtrl::OnDrawAdvanced(ATL_DRAWINFO &di)
{
	// Draw plugin
	PluginImpl::OnDraw();

	// Done
	return S_OK;
}

LRESULT PixelLightCtrl::OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// Save window and device context handles
	m_hPluginWnd = m_hWnd;
	m_hPluginDC  = GetDC();

	// Initialize plugin
	PluginImpl::OnInit();

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
	PluginImpl::OnSize();

	// Done
	return 0;
}
