/*********************************************************\
 *  File: GuiApplication.cpp                            *
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
#include <PLGeneral/System/System.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include <PLGeneral/Log/Log.h>
#include <PLCore/Core.h>
#include <PLCore/Tools/Localization.h>
#include <PLCore/Tools/LocalizationGroup.h>
#include <PLCore/Tools/LoadableType.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLGui/Gui/Gui.h"
#include "PLGui/Widgets/Windows/Window.h"
#include "PLGui/Application/GuiApplication.h"


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLCore;
namespace PLGui {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(GuiApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiApplication::GuiApplication(const PLGeneral::String &sGuiFilename) : ConsoleApplication(),
	EventHandlerOnDestroy(&GuiApplication::OnDestroyMainWindow, this),
	m_pMainWindow(nullptr)
{
	// Set application title
	SetTitle("PixelLight GUI application");
}

/**
*  @brief
*    Destructor
*/
GuiApplication::~GuiApplication()
{
}

/**
*  @brief
*    Get main window
*/
Widget *GuiApplication::GetMainWindow() const
{
	// Return pointer to main window
	return m_pMainWindow;
}

/**
*  @brief
*    Set main window
*/
void GuiApplication::SetMainWindow(Widget *pMainWindow)
{
	// Disconnect event handler
	if (m_pMainWindow)
		m_pMainWindow->SignalDestroy.Disconnect(&EventHandlerOnDestroy);

	// Set pointer to main window
	m_pMainWindow = pMainWindow;

	// Connect event handler
	if (m_pMainWindow)
		m_pMainWindow->SignalDestroy.Connect(&EventHandlerOnDestroy);
}


//[-------------------------------------------------------]
//[ Protected virtual ConsoleApplication functions        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization function that is called prior to OnInit()
*/
bool GuiApplication::Init()
{
	// Call base implementation
	if (ConsoleApplication::Init()) {
		// Create main window
		OnCreateMainWindow();
		if (!m_bRunning) return false;

		// Done
		return true;
	}

	// Error
	return false;
}

/**
*  @brief
*    Main function
*/
void GuiApplication::Main()
{
	// Run main loop
	Gui *pGui = Gui::GetSystemGui();
	while (pGui->IsActive() && m_bRunning) {
		// Get GUI messages
		pGui->ProcessMessages();
	}
}

/**
*  @brief
*    De-initialization function that is called after OnDeInit()
*/
void GuiApplication::DeInit()
{
	// Call base implementation
	ConsoleApplication::DeInit();

	// Shut down system GUI
	Gui::GetSystemGui()->Shutdown();
}


//[-------------------------------------------------------]
//[ Protected virtual GuiApplication functions            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called to open the application's main window
*/
void GuiApplication::OnCreateMainWindow()
{
	// [TODO] Load GUI from file if filename is provided

	// Create standard window
	Window *pWindow = new Window();
	pWindow->AddModifier("PLGui::ModClose", "ExitApplication=1");
	pWindow->SetTitle(GetTitle());
	pWindow->SetSize(Vector2i(640, 480));
	pWindow->SetVisible(true);

	// Set main window
	SetMainWindow(pWindow);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a window was destroyed
*/
void GuiApplication::OnDestroyMainWindow()
{
	// We lost our main window :/
	m_pMainWindow = nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
