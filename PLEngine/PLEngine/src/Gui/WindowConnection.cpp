/*********************************************************\
 *  File: WindowConnection.cpp                           *
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
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLRenderer/Renderer/SurfaceWindow.h>
#include <PLRenderer/Renderer/SurfacePainter.h>
#include "PLEngine/Gui/WindowConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGui;
using namespace PLRenderer;
namespace PLEngine {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WindowConnection::WindowConnection(Renderer &cRenderer, Widget &cWidget, Widget *pEventWidget) :
	EventHandlerDestroy(&WindowConnection::OnDestroy, this),
	EventHandlerShow   (&WindowConnection::OnShow,    this),
	EventHandlerHide   (&WindowConnection::OnHide,    this),
	EventHandlerKeyDown(&WindowConnection::OnKeyDown, this),
	m_pRenderer(&cRenderer),
	m_pWidget(&cWidget),
	m_bFullscreenMode(false),
	m_bToggleFullscreenMode(false),
	m_bFullscreenAltTab(false),
	m_bFullscreenAltTabKey(false),
	m_nHotkeyIDAltTab(0)
{
	// Connect event handlers
	Widget *pWidget = pEventWidget ? pEventWidget : &cWidget;
	pWidget->SignalDestroy.Connect(&EventHandlerDestroy);
	pWidget->SignalShow   .Connect(&EventHandlerShow);
	pWidget->SignalHide   .Connect(&EventHandlerHide);
	pWidget->SignalKeyDown.Connect(&EventHandlerKeyDown);
	// [TODO] Linux: Currently we need to listen to the content widget key signals as well ("focus follows mouse"-topic)
	if (pWidget->GetContentWidget() != pWidget)
		pWidget->GetContentWidget()->SignalKeyDown.Connect(&EventHandlerKeyDown);
}

/**
*  @brief
*    Destructor
*/
WindowConnection::~WindowConnection()
{
}

/**
*  @brief
*    Initializes the window connection
*/
void WindowConnection::Initialize(const DisplayMode *pDisplayMode, bool bFullscreen)
{
	// De-init window
	DeInit();

	// Display mode information given?
	if (pDisplayMode) {
		// Just copy over the given information
		m_sDisplayMode = *pDisplayMode;
	} else {
		// Use default settings
		m_sDisplayMode.vSize      = m_pWidget->GetSize();
		m_sDisplayMode.nColorBits = 32;
		m_sDisplayMode.nFrequency = 60;
	}

	// Initialize renderer surface handler
	InitWidget(bFullscreen);

	// Emit the initial events so other components can set their proper initial states
	if (bFullscreen)
		OnFullscreenMode();
	else
		OnDisplayMode();
}

/**
*  @brief
*    Returns information about the used display mode
*/
const DisplayMode &WindowConnection::GetDisplayMode() const
{
	return m_sDisplayMode;
}

/**
*  @brief
*    Sets a new display mode
*/
void WindowConnection::SetDisplayMode(const DisplayMode &sDisplayMode)
{
	// Even if there's no change within the display mode, the real widget size currently may be another than the display size -
	// in this situation, it's usually nice if the widget size is updated to the set display size, so, we don't perform an early escape test

	// Are we currently within fullscreen mode?
	if (IsFullscreen()) {
		// Any state change?
		if (m_sDisplayMode.vSize         != sDisplayMode.vSize      ||
			m_sDisplayMode.nColorBits    != sDisplayMode.nColorBits ||
			m_sDisplayMode.nFrequency    != sDisplayMode.nFrequency) {
			// Copy over the new settings
			m_sDisplayMode = sDisplayMode;

			// Backup information
			const SurfaceWindow *pSurface  = static_cast<SurfaceWindow*>(GetSurface());
			if (pSurface && pSurface->GetWindow()) {
				// Backup information
				bool			bFullscreen = IsFullscreen();
				SurfacePainter *pPainter    = GetSurface()->GetPainter();
				GetSurface()->SetPainter(nullptr, false);

				// De-init window
				DeInit();

				// Set new widget size
				m_pWidget->SetWindowState(StateNormal);
				m_pWidget->SetSize(GetDisplayMode().vSize);

				// Init widget
				InitWidget(bFullscreen);

				// Set widget into fullscreen state? (the display should now already have the proper size)
				m_pWidget->SetWindowState(StateFullscreen);

				// Set previous surface painter
				GetSurface()->SetPainter(pPainter, false);
			}
		}
	} else {
		// Just copy over the new settings
		m_sDisplayMode = sDisplayMode;
	}

	// Emit event by using the proper virtual method
	OnDisplayMode();
}

/**
*  @brief
*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
bool WindowConnection::GetToggleFullscreenMode() const
{
	return m_bToggleFullscreenMode;
}

/**
*  @brief
*    Sets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
void WindowConnection::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Set the new state
	m_bToggleFullscreenMode = bToggleFullscreenMode;
}

/**
*  @brief
*    Gets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
bool WindowConnection::GetFullscreenAltTab() const
{
	return m_bFullscreenAltTab;
}

/**
*  @brief
*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
void WindowConnection::SetFullscreenAltTab(bool bAllowed)
{
	m_bFullscreenAltTab = bAllowed;
	if (m_bFullscreenAltTab || !IsFullscreen()) {
		if (!m_bFullscreenAltTabKey) {
			// Release Alt-Tab hotkey
			m_pWidget->UnregisterHotkey(m_nHotkeyIDAltTab);
		}
	} else {
		if (!m_bFullscreenAltTabKey) {
			// Catch Alt-Tab hotkey so it can't be used during fullscreen
			m_nHotkeyIDAltTab = m_pWidget->RegisterHotkey(PLGUIMOD_ALT, PLGUIKEY_TAB);
		}
	}
}

/**
*  @brief
*    Returns whether the window is in fullscreen mode or not
*/
bool WindowConnection::IsFullscreen() const
{
	// Return fullscreen mode
	return m_bFullscreenMode;
}

/**
*  @brief
*    Sets the window's fullscreen mode
*/
void WindowConnection::SetFullscreen(bool bFullscreen)
{
	// Set fullscreen mode
	if (IsFullscreen() != bFullscreen) {
		// Backup information
		const SurfaceWindow *pSurface  = static_cast<SurfaceWindow*>(GetSurface());
		if (pSurface && pSurface->GetWindow()) {
			// Backup information
			SurfacePainter *pPainter = GetSurface()->GetPainter();
			GetSurface()->SetPainter(nullptr, false);

			// De-init window
			DeInit();

			// [HACK] If the widget is currently maximized, change back to normal - if we don't do this and changing from
			// maximized to fullscreen, the window title is visible within the fullscreen mode...
			if (bFullscreen && m_pWidget->GetWindowState() == StateMaximized)
				m_pWidget->SetWindowState(StateNormal);

			// Init widget
			InitWidget(bFullscreen);

			// Set previous surface painter
			GetSurface()->SetPainter(pPainter, false);

			// Set widget into fullscreen state? (the display should now already have the proper size)
			if (bFullscreen) {
				m_pWidget->SetWindowState(StateFullscreen);
			} else {
				m_pWidget->SetWindowState(StateNormal);
				m_pWidget->SetSize(GetDisplayMode().vSize);
			}

			// Emit event by using the proper virtual method
			OnFullscreenMode();
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual WindowConnection functions          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called when the display mode was changed
*/
void WindowConnection::OnDisplayMode()
{
	// Emit event
	EventDisplayMode();
}

/**
*  @brief
*    Function that is called when the fullscreen mode was changed
*/
void WindowConnection::OnFullscreenMode()
{
	// Emit event
	EventFullscreenMode();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
WindowConnection::WindowConnection(const WindowConnection &cSource) :
	m_pWidget(nullptr),
	m_bFullscreenMode(false),
	m_bToggleFullscreenMode(false),
	m_bFullscreenAltTab(false),
	m_bFullscreenAltTabKey(false)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
WindowConnection &WindowConnection::operator =(const WindowConnection &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Initializes the render widget
*/
void WindowConnection::InitWidget(bool bFullscreen)
{
	// Get the native window handle
	handle nWindow = m_pWidget->GetContentWidget()->GetWindowHandle();

	// Initialize renderer surface handler
	Init(*m_pRenderer, nWindow, m_sDisplayMode, bFullscreen);

	// Backup the fullscreen mode
	m_bFullscreenMode = GetSurface() ? static_cast<SurfaceWindow*>(GetSurface())->IsFullscreen() : false;

	// Update fullscreen Alt-Tab
	SetFullscreenAltTab(GetFullscreenAltTab());
}

/**
*  @brief
*    Function that is called when the GUI widget is destroyed
*/
void WindowConnection::OnDestroy()
{
	// De-init window
	DeInit();
}

/**
*  @brief
*    Function that is called when the GUI widget is shown
*/
void WindowConnection::OnShow()
{
	// Activate the surface
	if (GetSurface())
		GetSurface()->SetActive(true);
}

/**
*  @brief
*    Function that is called when the GUI widget is hidden
*/
void WindowConnection::OnHide()
{
	// Deactivate the surface
	if (GetSurface())
		GetSurface()->SetActive(false);
}

/**
*  @brief
*    Called when a key is pressed down
*/
void WindowConnection::OnKeyDown(uint32 nKey, uint32 nModifiers)
{
	// Fullscreen mode toggle allowed and ALT+ENTER pressed?
	if (m_bToggleFullscreenMode && nKey == PLGUIKEY_RETURN && (nModifiers & PLGUIMOD_ALT) != 0)
		SetFullscreen(!IsFullscreen());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
