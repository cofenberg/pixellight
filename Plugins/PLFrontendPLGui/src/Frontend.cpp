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
using namespace PLGraphics;
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
	EventHandlerDestroyMainWindow (&Frontend::OnDestroyMainWindow,  this),
	EventHandlerActivateMainWindow(&Frontend::OnActivateMainWindow, this),
	EventHandlerDrawMainWindow    (&Frontend::OnDrawMainWindow,     this),
	EventHandlerDisplayMode       (&Frontend::OnDisplayMode,        this),
	EventHandlerFullscreenMode    (&Frontend::OnFullscreenMode,     this),
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
	if (m_pMainWindow) {
		m_pMainWindow->SignalDestroy .Disconnect(EventHandlerDestroyMainWindow);
		m_pMainWindow->SignalActivate.Disconnect(EventHandlerActivateMainWindow);
		m_pMainWindow->SignalDraw    .Disconnect(EventHandlerDrawMainWindow);
	}

	// Set pointer to main window
	m_pMainWindow = pMainWindow;

	// Connect event handler
	if (m_pMainWindow) {
		m_pMainWindow->SignalDestroy .Connect(EventHandlerDestroyMainWindow);
		m_pMainWindow->SignalActivate.Connect(EventHandlerActivateMainWindow);
		m_pMainWindow->SignalDraw    .Connect(EventHandlerDrawMainWindow);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::FrontendImpl functions      ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sApplicationClass)
{
	// Create main window
	OnCreateMainWindow();

	// The frontend main loop
	while (Gui::GetSystemGui()->IsActive() && m_pMainWindow && m_pMainWindow->GetNativeWindowHandle() && m_cFrontend.IsRunning()) {
		// Redraw & ping
		Redraw();
		Ping();
	}

	// Destroy main window
	if (m_pMainWindow) {
		m_pMainWindow->Destroy();
		m_pMainWindow = nullptr;
	}

	// Shut down system GUI
	Gui::GetSystemGui()->Shutdown();

	// Done
	return 0;
}

handle Frontend::GetNativeWindowHandle() const
{
	return (m_pMainWindow && m_pMainWindow->GetContentWidget()) ? m_pMainWindow->GetContentWidget()->GetNativeWindowHandle() : NULL_HANDLE;
}

void Frontend::Redraw()
{
	// Ask PLGui politly to update (and repaint) the widget
	if (m_pMainWindow)
		m_pMainWindow->Redraw();
}

void Frontend::Ping()
{
	// Check if there are system messages waiting (non-blocking)
	if (Gui::GetSystemGui()->HasPendingMessages()) {
		// Process all waiting messages
		Gui::GetSystemGui()->ProcessMessages();
	}
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

	// There's no need to have a widget background because we're render into it
	// (avoids flickering caused by automatic background overdraw)
	pWindow->GetContentWidget()->SetBackgroundColor(Color4::Transparent);

	// Connect event handler
	// [TODO]
//	pWindow->EventDisplayMode   .Connect(EventHandlerDisplayMode);
//	pWindow->EventFullscreenMode.Connect(EventHandlerFullscreenMode);

	// [TODO] Add within PLGui something like MessageOnEnterMoveSize&MessageOnLeaveMoveSize?
	//        Background: When moving/sizing the window, the application will also be paused during this period (WM_EXITSIZEMOVE/WM_ENTERSIZEMOVE MS Windows events)...
	//                    it's just annyoing when you move or size a window and the controlled scene camera is spinning around while you do so...

	// Set main window
	SetMainWindow(pWindow);

	// Show the window, but do not activate it right now
	pWindow->SetVisible(true);

	// Do the frontend lifecycle thing - start
	OnStart();

	// Show and activate the window
	pWindow->Activate();
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
void Frontend::OnDestroyMainWindow()
{
	// Do the frontend lifecycle thing - stop
	OnStop();

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
void Frontend::OnActivateMainWindow(bool bActivate)
{
	// Do the frontend lifecycle thing - resume/pause
	if (bActivate)
		OnResume();
	else
		OnPause();
}

/**
*  @brief
*    Called when main window was drawn
*/
void Frontend::OnDrawMainWindow(Graphics &cGraphics)
{
	// [TODO] Redraw, but only if the draw area isn't null - looks like PLGui currently doesn't provide the required information to perform this test

	// [TODO] Update stuff
	OnDraw();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendPLGui
