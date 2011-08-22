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
#include <QStringList>
#include <PLCore/Core.h>
#include <PLCore/Tools/Timing.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include "Application.h"
#include "Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLFrontendQt;
namespace PLEditor {


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
	m_bFrontendApplicationInitialized(false),
	m_cFrontend(m_cFrontendContext, *this)
{
	// Scan PL-runtime directory for compatible plugins and load them in as well as scan for compatible data and register it
	Runtime::ScanDirectoryPluginsAndData();

	// Set the name of the application class to use
	m_cFrontend.ApplicationClass = "PLEngine::EngineApplication";

	// Do the frontend life cycle thing - let the world know that we have been created
	OnCreate();

	// Let the world know that this frontend is now going to run
	const String sExecutableFilename = QtStringAdapter::QtToPL(Application::instance()->arguments().at(0));
	const Array<String> lstArguments;
	OnRun(sExecutableFilename, lstArguments);

	// Do the frontend life cycle thing - initialize
	if (OnStart()) {
		OnResume();

		// Frontend application successfully initialized
		m_bFrontendApplicationInitialized = true;
	}
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
	// Do the frontend life cycle thing - de-initialize
	if (m_bFrontendApplicationInitialized) {
		OnPause();
		OnStop();
	}

	// Do the frontend life cycle thing - let the world know that we're going to die
	OnDestroy();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::FrontendImpl functions        ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Error, this frontend implementation is run and controlled by the Qt application this frontend is embedded into
	return -1;
}

int Frontend::Run(int argc, wchar_t **argv)
{
	// Error, this frontend implementation is run and controlled by the Qt application this frontend is embedded into
	return -1;
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
	// Check if we're allowed to perform an update right now
	if (Timing::GetInstance()->Update()) {
		// Let the frontend update it's states
		OnUpdate();
	}
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor
