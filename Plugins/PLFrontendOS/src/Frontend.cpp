/*********************************************************\
 *  File: Frontend.cpp                                   *
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
#if defined(WIN32)
	#include "PLFrontendOS/OSWindowWindows.h"
#elif defined(LINUX)
	// This header must be included after Frontend.h because the X11/Xlib.h header is included in this header,
	// which has some defines which are also used in some header included by Frontend.h
	#include "PLFrontendOS/OSWindowLinux.h"
#endif
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
	m_cFrontend(*this),
	m_pOSWindow(nullptr),
	m_bQuit(false)
{
	// Do the frontend lifecycle thing - let the world know that we have been created
	OnCreate();
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
	// Do the frontend lifecycle thing - let the world know that we're going to die
	OnDestroy();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::FrontendImpl functions        ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sApplicationClass)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pOSWindow = new OSWindowWindows(*this);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pOSWindow = new OSWindowLinux(*this);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif

	// The frontend message loop
	m_bQuit = false;
	while (!m_bQuit && m_pOSWindow && m_pOSWindow->GetNativeWindowHandle() && m_cFrontend.IsRunning()) {
		// Redraw & ping
		Redraw();
		Ping();
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
	// Ask the OS politly to update (and repaint) the widget
	if (m_pOSWindow)
		m_pOSWindow->Redraw();
}

void Frontend::Ping()
{
	if (m_pOSWindow)
		m_bQuit = m_pOSWindow->Ping();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
