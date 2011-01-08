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
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include "PLPlugin/Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGui;
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() : RenderApplication("SPSampleTeapot"),
	EventHandlerKeyDown(&Application::NotifyKeyDown, this)
{
	// Set application title
	SetTitle(PLT("PL teapot sample"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a key is pressed down
*/
void Application::NotifyKeyDown(uint32 nKey)
{
	// Check whether the escape key was pressed
	if (nKey == PLGUIKEY_ESCAPE)
		// Shut down the application
		Exit(0);
}


//[-------------------------------------------------------]
//[ Private virtual PLGui::GuiApplication functions       ]
//[-------------------------------------------------------]
void Application::OnInit()
{
	// Connect event handler
	Widget *pWidget = GetMainWindow();
	if (pWidget)
		pWidget->EventKeyDown.Connect(&EventHandlerKeyDown);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin
