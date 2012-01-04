/*********************************************************\
 *  File: Frontend.cpp                                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Tools/Timing.h>
#include <PLCore/Frontend/Frontend.h>
#if defined(WIN32)
	#include "PLFrontendOS/OSWindowWindows.h"
#elif defined(APPLE)
	//#include "PLFrontendOS/OSWindowMacOSX.h"	// [TODO] This is what we really want to use on Mac OS X to stay out of compatibility trouble
	#include "PLFrontendOS/OSWindowLinux.h"	// [TODO] For now, we reuse the X11 implementation from the Linux port
#elif defined(LINUX)
	#include "PLFrontendOS/OSWindowLinux.h"
#endif
#include "PLFrontendOS/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Frontend)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Frontend::Frontend() :
	m_pOSWindow(nullptr),
	m_bQuit(false),
	m_bToggleFullscreenMode(true),
	m_bFullscreenAltTab(true),
	m_bIsFullscreen(false)
{
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::FrontendImpl functions        ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pOSWindow = new OSWindowWindows(*this);
	#elif defined(APPLE)
		// Create Mac OS X implementation

		// [TODO] This is what we really want to use on Mac OS X to stay out of compatibility trouble
		// m_pOSWindow = new OSWindowMacOSX(*this);

		// [TODO] For now, we reuse the X11 implementation from the Linux port
		m_pOSWindow = new OSWindowLinux(*this);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pOSWindow = new OSWindowLinux(*this);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif

	// The frontend message loop
	if (m_pOSWindow->GetNativeWindowHandle()) {
		m_bQuit = false;
		while (!m_bQuit && m_pOSWindow && m_pOSWindow->GetNativeWindowHandle() && m_pFrontend && m_pFrontend->IsRunning()) {
			// Redraw & ping
			Redraw();
			Ping();
		}
	}

	// Destroy the OS specific window implementation
	if (m_pOSWindow) {
		delete m_pOSWindow;
		m_pOSWindow = nullptr;
	}

	// Done
	return 0;
}

handle Frontend::GetNativeWindowHandle() const
{
	return m_pOSWindow ? m_pOSWindow->GetNativeWindowHandle() : NULL_HANDLE;
}

void Frontend::Redraw()
{
	// Ask the OS politely to update (and repaint) the widget
	if (m_pOSWindow)
		m_pOSWindow->Redraw();
}

void Frontend::Ping()
{
	// Check if we're allowed to perform an update right now
	if (!m_bQuit && Timing::GetInstance()->Update()) {
		// Let the frontend update it's states (do this before drawing else, e.g. the first frame may have an unwanted content)
		OnUpdate();
	}

	// Ping the OS window
	if (m_pOSWindow)
		m_bQuit = m_pOSWindow->Ping();
}

String Frontend::GetTitle() const
{
	// Query the OS window implementation
	return m_pOSWindow ? m_pOSWindow->GetTitle() : "";
}

void Frontend::SetTitle(const String &sTitle)
{
	// Query the OS window implementation
	if (m_pOSWindow)
		m_pOSWindow->SetTitle(sTitle);
}

int Frontend::GetX() const
{
	// Query the OS window implementation
	return m_pOSWindow ? m_pOSWindow->GetX() : 0;
}

int Frontend::GetY() const
{
	// Query the OS window implementation
	return m_pOSWindow ? m_pOSWindow->GetY() : 0;
}

uint32 Frontend::GetWidth() const
{
	// Query the OS window implementation
	return m_pOSWindow ? m_pOSWindow->GetWidth() : 0;
}

uint32 Frontend::GetHeight() const
{
	// Query the OS window implementation
	return m_pOSWindow ? m_pOSWindow->GetHeight() : 0;
}

void Frontend::SetWindowPositionSize(int nX, int nY, uint32 nWidth, uint32 nHeight)
{
	// Query the OS window implementation
	if (m_pOSWindow)
		m_pOSWindow->SetWindowPositionSize(nX, nY, nWidth, nHeight);
}

bool Frontend::GetToggleFullscreenMode() const
{
	return m_bToggleFullscreenMode;
}

void Frontend::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	m_bToggleFullscreenMode = bToggleFullscreenMode;
}

bool Frontend::GetFullscreenAltTab() const
{
	return m_bFullscreenAltTab;
}

void Frontend::SetFullscreenAltTab(bool bAllowed)
{
	// Is there a state change?
	if (m_bFullscreenAltTab != bAllowed) {
		// Set the new state
		m_bFullscreenAltTab = bAllowed;

		// Let the OS window do the rest
		if (m_pOSWindow)
			m_pOSWindow->SetFullscreenAltTab(bAllowed);
	}
}

bool Frontend::IsFullscreen() const
{
	return m_bIsFullscreen;
}

void Frontend::SetFullscreen(bool bFullscreen)
{
	// Is there a state change?
	if (m_bIsFullscreen != bFullscreen) {
		// Set the new state
		m_bIsFullscreen = bFullscreen;

		// Let the OS window do the rest
		if (m_pOSWindow)
			m_pOSWindow->SetFullscreen(bFullscreen);
	}
}

void Frontend::RefreshFullscreen()
{
	// Let the OS window do the rest
	if (m_pOSWindow)
		m_pOSWindow->RefreshFullscreen();
}

bool Frontend::IsMouseOver() const
{
	// Let the OS window do the rest
	return m_pOSWindow ? m_pOSWindow->IsMouseOver() : false;
}

int Frontend::GetMousePositionX() const
{
	// Let the OS window do the rest
	return m_pOSWindow ? m_pOSWindow->GetMousePositionX() : -1;
}

int Frontend::GetMousePositionY() const
{
	// Let the OS window do the rest
	return m_pOSWindow ? m_pOSWindow->GetMousePositionY() : -1;
}

bool Frontend::IsMouseVisible() const
{
	// Let the OS window do the rest
	return m_pOSWindow ? m_pOSWindow->IsMouseVisible() : true;
}

void Frontend::SetMouseVisible(bool bVisible)
{
	// Let the OS window do the rest
	if (m_pOSWindow)
		m_pOSWindow->SetMouseVisible(bVisible);
}

void Frontend::SetTrapMouse(bool bTrap)
{
	// Let the OS window do the rest
	if (m_pOSWindow)
		m_pOSWindow->SetTrapMouse(bTrap);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
