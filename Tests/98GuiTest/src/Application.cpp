/*********************************************************\
 *  File: Application.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
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
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application)


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
		System::GetInstance()->GetConsole().Print("- " + sScreen + '\n');
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
	const List<FontInfo> &lstFonts = pGui->GetFontManager().GetFonts();
	System::GetInstance()->GetConsole().Print("Available fonts:\n");
	for (uint32 i=0; i<lstFonts.GetNumOfElements(); i++) {
		// Get font
		FontInfo cFontInfo = lstFonts[i];

		// Get font info
		String sFamily = cFontInfo.GetFamily();
		String sHeight = String() + cFontInfo.GetHeight();
		String sWeight = "Normal";
		if (cFontInfo.GetWeight() == WeightBold)  sWeight = "Bold";
		if (cFontInfo.GetWeight() == WeightLight) sWeight = "Light";
		String sStyle = "Normal";
		if (cFontInfo.GetStyle() == StyleItalics) sStyle = "Italics";

		// Print font info
		System::GetInstance()->GetConsole().Print("- Family: '" + sFamily + "' Height: '" + sHeight + "' Weight: '" + sWeight + "' Style: '" + sStyle + "'\n");
	}
	System::GetInstance()->GetConsole().Print('\n');
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
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
