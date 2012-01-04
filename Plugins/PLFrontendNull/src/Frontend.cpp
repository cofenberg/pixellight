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
#ifdef WIN32
	#include <PLCore/PLCoreWindowsIncludes.h>
#endif
#include <PLCore/Tools/Timing.h>
#include <PLCore/System/System.h>
#include <PLCore/Frontend/Frontend.h>
#include "PLFrontendNull/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendNull {


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
	m_nTimeToWait(0)
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
	// Do the frontend life cycle thing - initialize
	if (OnStart()) {
		OnResume();

		// The frontend main loop
		while (m_pFrontend && m_pFrontend->IsRunning()) {
			// Time to wait?
			if (m_nTimeToWait) {
				// Let the system some time to process other system tasks etc.
				// If this isn't done the CPU usage is always up to 100%!!
				// Please note that there's no guaranty that the resulting FPS always reaches
				// exactly the maximum FPS limit.
				System::GetInstance()->Sleep(m_nTimeToWait);
			}

			// Redraw & ping
			Redraw();
			Ping();
		}

		// Do the frontend life cycle thing - de-initialize
		OnPause();
		OnStop();

		// Done
		return 0;
	} else {
		// Error!
		return -1;
	}
}

handle Frontend::GetNativeWindowHandle() const
{
	// There's no window handle!
	return NULL_HANDLE;
}

void Frontend::Redraw()
{
	// Let the frontend draw into it's window
	OnDraw();
}

void Frontend::Ping()
{
	// MS Windows: Get and dispatch messages, an application using this frontend may need it for e.g. proper input processing
	#ifdef WIN32
		MSG sMsg;
		while (PeekMessage(&sMsg, nullptr, 0, 0, FALSE)) {
			GetMessage(&sMsg, nullptr, 0, 0);
			TranslateMessage(&sMsg);
			DispatchMessage(&sMsg);
		}
	#endif

	// Check if we're allowed to perform an update right now
	if (Timing::GetInstance()->Update(&m_nTimeToWait)) {
		// Let the frontend update it's states
		OnUpdate();
	}
}

String Frontend::GetTitle() const
{
	// There's no window
	return "";
}

void Frontend::SetTitle(const String &sTitle)
{
	// There's no window
}

int Frontend::GetX() const
{
	// There's no window
	return 0;
}

int Frontend::GetY() const
{
	// There's no window
	return 0;
}

uint32 Frontend::GetWidth() const
{
	// There's no window
	return 0;
}

uint32 Frontend::GetHeight() const
{
	// There's still no window
	return 0;
}

void Frontend::SetWindowPositionSize(int nX, int nY, uint32 nWidth, uint32 nHeight)
{
	// There's no window
}

bool Frontend::GetToggleFullscreenMode() const
{
	// Exactly, no window
	return false;
}

void Frontend::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// No window, again
}

bool Frontend::GetFullscreenAltTab() const
{
	// Return whether or not it's allowed to use Alt-Tab - if there would be a window, but there's no
	return false;
}

void Frontend::SetFullscreenAltTab(bool bAllowed)
{
	// Sorry, this frontend really has no window...
}

bool Frontend::IsFullscreen() const
{
	// ... no window at all...
	return false;
}

void Frontend::SetFullscreen(bool bFullscreen)
{
	// No window = nothing to do in here
}

void Frontend::RefreshFullscreen()
{
	// No window = nothing to do in here
}

bool Frontend::IsMouseOver() const
{
	// We're not interested in GUI stuff
	return false;
}

int Frontend::GetMousePositionX() const
{
	// We're not interested in GUI stuff
	return -1;
}

int Frontend::GetMousePositionY() const
{
	// We're not interested in GUI stuff
	return -1;
}

bool Frontend::IsMouseVisible() const
{
	// We're not interested in GUI stuff
	return false;
}

void Frontend::SetMouseVisible(bool bVisible)
{
	// We're not interested in GUI stuff
}

void Frontend::SetTrapMouse(bool bTrap)
{
	// We're not interested in GUI stuff
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendNull
