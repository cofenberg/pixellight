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
#include <PLCore/File/Url.h>
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Screen.h>
#include "Application.h"
#include "TestWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
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
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLGui::GuiApplication functions     ]
//[-------------------------------------------------------]
void Application::OnCreateMainWindow()
{
	// [sbusch]
//	String sDir = Url(sFilename).CutFilename();
//	System::GetInstance()->SetCurrentDir(sDir);
//	LoadableManager::GetInstance()->AddBaseDir(sDir);

	// Get GUI
	Gui *pGui = Gui::GetSystemGui();

	// List screens
	System::GetInstance()->GetConsole().Print("Screens:\n");
	for (uint32 i=0; i<pGui->GetScreens().GetNumOfElements(); i++) {
		Screen *pScreen = pGui->GetScreens().Get(i);
		String sName	= pScreen->GetName();
		Vector2i vSize	= pScreen->GetSize();
		Vector2i vPos	= pScreen->GetPos();
		bool bDefault	= pScreen->IsDefault();
		System::GetInstance()->GetConsole().Print(
			String("- ") + sName +
			" [" + vSize.x + 'x' + vSize.y +']' +
			" (" + vPos .x + ',' + vPos .y + ')' +
			(bDefault ? " (*)" : "") +
			'\n');
	}

	// Create window
	TestWindow *pWindow = new TestWindow();
//	pWindow->SetFullscreenEnabled(true);
	pWindow->SetPos(Vector2i(0, 0));
	pWindow->SetSize(Vector2i(640, 480));
	pWindow->Center(CenterScreen);
	pWindow->SetVisible(true);

	// Add modifiers
	pWindow->AddModifier("PLGui::ModClose", "ExitApplication=1");
//	pWindow->AddModifier("PLGui::ModBlend", "");

	// Set main window
	SetMainWindow(pWindow);
}
