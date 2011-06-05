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
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLRenderer/RendererContext.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGui;
using namespace PLRenderer;


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
Application::Application() : RenderApplication(),
	EventHandlerKeyDown(&Application::NotifyKeyDown, this)
{
	// Set application name and title
	SetName("PLDemoRendererRTT");
	SetTitle(PLT("PL render to texture demo"));
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
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a key is pressed down
*/
void Application::NotifyKeyDown(uint32 nKey, uint32 nModifiers)
{
	// Check whether the escape key was pressed
	if (nKey == PLGUIKEY_ESCAPE)
		// Shut down the application
		Exit(0);
}


//[-------------------------------------------------------]
//[ Private virtual PLGui::GuiApplication functions       ]
//[-------------------------------------------------------]
void Application::OnCreateMainWindow()
{
	// Call base implementation
	RenderApplication::OnCreateMainWindow();

	// Connect event handler
	Widget *pWidget = GetMainWindow();
	if (pWidget) {
		pWidget->EventKeyDown.Connect(&EventHandlerKeyDown);
		// [TODO] Linux: Currently we need to listen to the content widget key events as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget)
			pWidget->GetContentWidget()->EventKeyDown.Connect(&EventHandlerKeyDown);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::RenderApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreatePainter()
{
	// Get the renderer context instance
	RendererContext *pRendererContext = GetRendererContext();
	if (pRendererContext) {
		// Set the surface painter to use depending on whether or not there's a default shader language within the used renderer
		const bool bShaders = (pRendererContext->GetRenderer().GetDefaultShaderLanguage().GetLength() != 0);

		// Create and set the surface painter
		SetPainter(m_pRendererContext->GetRenderer().CreateSurfacePainter(bShaders ? "SPRTTShaders" : "SPRTTFixedFunctions"));
	}
}
