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
#include <PLCore/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLFrontendPLGui/RenderWidget.h>
#include <PLFrontendPLGui/RenderWindow.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLGui;
using namespace PLFrontendPLGui;


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
Application::Application() : RendererApplication()
{
	// Set application name and title
	SetName("53RendererMultiView");
	SetTitle(PLT("PL multi view sample main frame"));
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
//[ Private virtual PLRenderer::RendererApplication functions ]
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

	// Create the other two windows - Get the used renderer
	if (GetRendererContext()) {
		Renderer &cRenderer = GetRendererContext()->GetRenderer();

		// Get the display mode to use
		DisplayMode cDisplayMode;
		cDisplayMode.vSize.x    = 320;
		cDisplayMode.vSize.y    = 200;
		cDisplayMode.nColorBits = 32;
		cDisplayMode.nFrequency = 60;

		// Set the surface painter to use depending on whether or not there's a default shader language within the used renderer
		const bool bShaders = (cRenderer.GetDefaultShaderLanguage().GetLength() != 0);

		// Create the triangle sample window
		RenderWindow *pFrame = new RenderWindow(cRenderer, nullptr, &cDisplayMode);
		pFrame->SetPos(Vector2i(600, 0));
		pFrame->SetSize(Vector2i(300, 300));
		pFrame->SetTitle(PLT("PL triangle sample window"));
		pFrame->GetSurface()->SetPainter(cRenderer.CreateSurfacePainter(bShaders ? "SPTriangleShaders" : "SPTriangleFixedFunctions"));
		pFrame->AddModifier("PLGui::ModClose", "CloseWindow=true");
		pFrame->SetVisible(true);

		// Create the texturing sample window
		pFrame = new RenderWindow(cRenderer, nullptr, &cDisplayMode);
		pFrame->SetPos(Vector2i(600, 300));
		pFrame->SetSize(Vector2i(300, 300));
		pFrame->SetTitle(PLT("PL texturing sample window"));
		pFrame->GetSurface()->SetPainter(cRenderer.CreateSurfacePainter(bShaders ? "SPTexturingShaders" : "SPTexturingFixedFunctions"));
		pFrame->AddModifier("PLGui::ModClose", "CloseWindow=true");
		pFrame->SetVisible(true);
	}
}
