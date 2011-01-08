/*********************************************************\
 *  File: Application.cpp                                *
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
#include <PLGeneral/System/Console.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/MessageFilterDebug.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Screen.h>
#include "GuiTestWindow.h"
#include "Application.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application()
{
	// Set application name and title
	SetName("98GuiTest");
	SetTitle(PLT("PLSample 98 - GuiTest"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}

/**
*  @brief
*    Test: Display GUI test
*/
void Application::TestGui()
{
	// Start
	System::GetInstance()->GetConsole().Print("Starting GUI\n");

	// Get GUI
	Gui *pGui = Gui::GetSystemGui();

	// Add debug message filter
	MessageFilterDebug *pMessageFilterDebug = new MessageFilterDebug();
	pMessageFilterDebug->SetDebugMode(DebugModeAll);
	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnDestroy);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnInternalMessage);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnTimer);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnMouseEnter);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnMouseLeave);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnMouseOver);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnGetFocus);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnLooseFocus);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnActivate);
//	pMessageFilterDebug->AddRule(FilterInclusive, MessageOnWindowState);
//	pMessageFilterDebug->AddRule(FilterInclusive, "TestFrame");
	pGui->AddMessageFilter(pMessageFilterDebug);

	// Create PL icon
	Image cIcon(*pGui, "PLGui/pixellight.png");

	// Open main window
	GuiTestWindow *pWindow = new GuiTestWindow();
	pWindow->SetIcon(cIcon);
	pWindow->SetPos(Vector2i(100, 100));
	pWindow->SetVisible(true);
	pWindow->SetFocus();

	// Message loop
	while (pGui->IsActive()) {
		pGui->ProcessMessages();
	}

	// Shut down GUI
	pGui->Shutdown();

	// Stop
	System::GetInstance()->GetConsole().Print("Stopping GUI\n");
}

/**
*  @brief
*    Test: Display available screens
*/
void Application::TestScreens()
{
	// Get GUI
	Gui *pGui = Gui::GetSystemGui();

	// List screens
	System::GetInstance()->GetConsole().Print("Screens:\n");
	for (uint32 i=0; i<pGui->GetScreens().GetNumOfElements(); i++) {
		// Get screen
		Screen *pScreen = pGui->GetScreens().Get(i);

		// Print screen info
		String sScreen = pScreen->GetName();
		System::GetInstance()->GetConsole().Print("- " + sScreen + "\n");
	}
}

/**
*  @brief
*    Test: List available fonts
*/
void Application::TestFonts()
{
	// Get GUI
	Gui *pGui = Gui::GetSystemGui();

	// List fonts
	const PLGeneral::List<FontInfo> &lstFonts = pGui->GetFontManager().GetFonts();
	System::GetInstance()->GetConsole().Print("Available fonts:\n");
	for (uint32 i=0; i<lstFonts.GetNumOfElements(); i++) {
		// Get font
		FontInfo cFontInfo = lstFonts[i];

		// Get font info
		String sFamily = cFontInfo.GetFamily();
		String sHeight = String() + (int)cFontInfo.GetHeight();
		String sWeight = "Normal";
		if (cFontInfo.GetWeight() == WeightBold)  sWeight = "Bold";
		if (cFontInfo.GetWeight() == WeightLight) sWeight = "Light";
		String sStyle = "Normal";
		if (cFontInfo.GetStyle() == StyleItalics) sStyle = "Italics";

		// Print font info
		System::GetInstance()->GetConsole().Print("- Family: '" + sFamily + "' Height: '" + sHeight + "' Weight: '" + sWeight + "' Style: '" + sStyle + "'\n");
	}
	System::GetInstance()->GetConsole().Print("\n");
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::Main()
{
	// Run test
	TestGui();
//	TestScreens();
//	TestFonts();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
