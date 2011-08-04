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
#if defined(WIN32)
	#include "PLFrontendOS/OSWindowWindows.h"
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
	m_cFrontend(*this),
	m_pOSWindow(nullptr)
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
//[ Public virtual PLCore::FrontendImpl functions         ]
//[-------------------------------------------------------]
handle Frontend::GetNativeWindowHandle() const
{
	return m_pOSWindow ? m_pOSWindow->GetNativeWindowHandle() : NULL_HANDLE;
}

void Frontend::Ping()
{
	// Look if messages are waiting (non-blocking)
	MSG sMsg;
	while (PeekMessage(&sMsg, nullptr, 0, 0, PM_NOREMOVE)) {
		// Get the waiting message
		GetMessage(&sMsg, nullptr, 0, 0);

		// Process message
		TranslateMessage(&sMsg);
		DispatchMessage(&sMsg);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::FrontendImpl functions        ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sApplicationClass, const String &sExecutableFilename, const Array<String> &lstArguments)
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

	// The Windows message loop
	bool bQuit = false;
	while (!bQuit && m_pOSWindow && m_pOSWindow->GetNativeWindowHandle() && m_cFrontend.IsRunning()) {
		// Look if messages are waiting
		MSG sMsg;
		while (PeekMessage(&sMsg, nullptr, 0, 0, PM_REMOVE)) {
			if (sMsg.message == WM_QUIT)
				bQuit = true;
			TranslateMessage(&sMsg);
			DispatchMessage(&sMsg);
		}

		// [TODO] Update stuff
		OnDraw();
	}

	// Destroy the OS specific window implementation
	if (m_pOSWindow) {
		delete m_pOSWindow;
		m_pOSWindow = nullptr;
	}

	// Done
	return 0;
}

void Frontend::Redraw()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
