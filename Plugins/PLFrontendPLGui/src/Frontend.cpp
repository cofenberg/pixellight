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
#include <PLCore/Core.h>
#include <PLCore/Log/Log.h>
#include <PLCore/File/File.h>
#include <PLCore/File/Directory.h>
#include <PLCore/File/FileSearch.h>
#include <PLCore/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LocalizationGroup.h>
#include <PLCore/Tools/LoadableType.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Widgets/Windows/Window.h>
#include "PLFrontendPLGui/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGui;
namespace PLFrontendPLGui {


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
	EventHandlerDestroy       (&Frontend::OnDestroy,        this),
	EventHandlerActivate	  (&Frontend::OnActivate,       this),
	EventHandlerDisplayMode   (&Frontend::OnDisplayMode,    this),
	EventHandlerFullscreenMode(&Frontend::OnFullscreenMode, this),
	m_cFrontend(*this),
	m_pMainWindow(nullptr)
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

	// Shut down system GUI
	Gui::GetSystemGui()->Shutdown();
}

/**
*  @brief
*    Get main window
*/
Widget *Frontend::GetMainWindow() const
{
	// Return pointer to main window
	return m_pMainWindow;
}

/**
*  @brief
*    Set main window
*/
void Frontend::SetMainWindow(Widget *pMainWindow)
{
	// Disconnect event handler
	if (m_pMainWindow)
		m_pMainWindow->SignalDestroy.Disconnect(EventHandlerDestroy);

	// Set pointer to main window
	m_pMainWindow = pMainWindow;

	// Connect event handler
	if (m_pMainWindow)
		m_pMainWindow->SignalDestroy.Connect(EventHandlerDestroy);
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::FrontendImpl functions         ]
//[-------------------------------------------------------]
handle Frontend::GetNativeWindowHandle() const
{
	return (m_pMainWindow && m_pMainWindow->GetContentWidget()) ? m_pMainWindow->GetContentWidget()->GetNativeWindowHandle() : NULL_HANDLE;
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::FrontendImpl functions      ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sApplicationClass, const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Create main window
	OnCreateMainWindow();

	// Do the frontend lifecycle thing - initialize
	int nResult = 0;	// By default, no error
	if (OnStart()) {
		OnResume();

		// The frontend main loop
		Gui *pGui = Gui::GetSystemGui();
		while (pGui->IsActive() && m_pMainWindow && m_cFrontend.IsRunning()) {
			// Check if there are system messages waiting (make a non-blocking main loop)
			if (pGui->HasPendingMessages())
				pGui->ProcessMessages();

			// [TODO] Update stuff
			OnDraw();
		}

		// Do the frontend lifecycle thing - de-initialize
		OnPause();
		OnStop();
	} else {
		// Error!
		nResult = -1;
	}

	// Destroy main window
	if (m_pMainWindow) {
		m_pMainWindow->Destroy();
		m_pMainWindow = nullptr;
	}

	// Done
	return nResult;
}

void Frontend::Redraw()
{
}


//[-------------------------------------------------------]
//[ Protected virtual Frontend functions                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called to open the application's main window
*/
void Frontend::OnCreateMainWindow()
{
	// Create standard window
	Window *pWindow = new Window();
	pWindow->AddModifier("PLGui::ModClose", "ExitApplication=1");
	pWindow->SetSize(Vector2i(640, 480));
	pWindow->SetVisible(true);
	pWindow->Activate();

	// Connect event handler
	// [TODO]
//	pWindow->SignalActivate     .Connect(EventHandlerActivate);
//	pWindow->EventDisplayMode   .Connect(EventHandlerDisplayMode);
//	pWindow->EventFullscreenMode.Connect(EventHandlerFullscreenMode);

	// Set main window
	SetMainWindow(pWindow);
}

/**
*  @brief
*    Called when the display mode was changed
*/
void Frontend::OnDisplayMode()
{
	// Do nothing by default
}

/**
*  @brief
*    Called when the fullscreen mode was changed
*/
void Frontend::OnFullscreenMode()
{
	// Do nothing by default
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when main window was destroyed
*/
void Frontend::OnDestroy()
{
	// [TODO]
	/*
	// Get the main widget
	const Widget *pWidget = GetMainWindow();
	if (pWidget && pWidget->IsInstanceOf("PLEngine::RenderWindow")) {
		// Write fullscreen state back to the configuration
		GetConfig().SetVar("PLEngine::RendererConfig", "Fullscreen", String::Format("%d", static_cast<const RenderWindow*>(pWidget)->IsFullscreen()));

		// Write down display mode information
		const DisplayMode &sDisplayMode = static_cast<const RenderWindow*>(pWidget)->GetDisplayMode();
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayWidth",     String::Format("%d", sDisplayMode.vSize.x));
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayHeight",    String::Format("%d", sDisplayMode.vSize.y));
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayColorBits", String::Format("%d", sDisplayMode.nColorBits));
		GetConfig().SetVar("PLEngine::RendererConfig", "DisplayFrequency", String::Format("%d", sDisplayMode.nFrequency));
	}
	*/

	// We lost our main window :/
	m_pMainWindow = nullptr;
}

/**
*  @brief
*    Called when main window was (de-)activated
*/
void Frontend::OnActivate(bool bActivate)
{
	// Activate input controller when window is active, otherwise stop input
//	if (m_pInputController)
//		m_pInputController->SetActive(bActivate);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendPLGui
