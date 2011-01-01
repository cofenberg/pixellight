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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLEngine/Gui/RenderWidget.h>
#include <PLEngine/Gui/RenderWindow.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGui;
using namespace PLRenderer;
using namespace PLEngine;


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
	SetName("PLDemoRendererMultiView");
	SetTitle(PLT("PL multi view demo main frame"));
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
	Widget *pWidget = GetMainWindow();

	// Connect event handler
	const DisplayMode *pDisplayMode = NULL;
	if (pWidget) {
		pWidget->EventKeyDown.Connect(&EventHandlerKeyDown);
		// [TODO] Linux: Currently we need to listen to the content widget key events as well ("focus follows mouse"-topic)
		if (pWidget->GetContentWidget() != pWidget)
			pWidget->GetContentWidget()->EventKeyDown.Connect(&EventHandlerKeyDown);

		// Get the display mode to use
		if (pWidget->IsInstanceOf("PLEngine::RenderWidget"))
			pDisplayMode = &((const RenderWidget*)pWidget)->GetDisplayMode();
		else if (pWidget->IsInstanceOf("PLEngine::RenderWindow"))
			pDisplayMode = &((const RenderWindow*)pWidget)->GetDisplayMode();
	}

	// Get the used renderer
	if (GetRendererContext()) {
		Renderer &cRenderer = GetRendererContext()->GetRenderer();

		// Set the surface painter to use depending on whether or not there's a default shader language within the used renderer
		const bool bShaders = (cRenderer.GetDefaultShaderLanguage().GetLength() != 0);

		// Create the triangle demo window
		RenderWindow *pFrame = new RenderWindow(cRenderer, NULL, pDisplayMode);
		pFrame->SetPos(Vector2i(600, 0));
		pFrame->SetSize(Vector2i(300, 300));
		pFrame->SetTitle(PLT("PL triangle demo window"));
		pFrame->GetSurface()->SetPainter(cRenderer.CreateSurfacePainter(bShaders ? "SPTriangleShaders" : "SPTriangleFixedFunctions"));
		pFrame->AddModifier("PLGui::ModClose", "CloseWindow=true");
		pFrame->SetVisible(true);

		// Create the teapot demo window
		pFrame = new RenderWindow(cRenderer, NULL, pDisplayMode);
		pFrame->SetPos(Vector2i(600, 300));
		pFrame->SetSize(Vector2i(300, 300));
		pFrame->SetTitle(PLT("PL teapot demo window"));
		pFrame->GetSurface()->SetPainter(cRenderer.CreateSurfacePainter(bShaders ? "SPTeapotShaders" : "SPTeapotFixedFunctions"));
		pFrame->AddModifier("PLGui::ModClose", "CloseWindow=true");
		pFrame->SetVisible(true);
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
		SetPainter(m_pRendererContext->GetRenderer().CreateSurfacePainter(bShaders ? "SPMultiViewShaders" : "SPMultiViewFixedFunctions"));
	}
}
