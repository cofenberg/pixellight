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
#include <Rocket/Core.h>
#include <libRocket_PL/libRocketAdapter.h>
#include <PLGeneral/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGui;
using namespace PLRenderer;
using namespace PLScene;


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
Application::Application() :
	EventHandlerKeyDown(&Application::NotifyKeyDown, this),
	m_pRocketAdapter(nullptr)
{
	// Set application name and title
	SetName("PLDemo_libRocket");
	SetTitle(PLT("PL libRocket demo"));
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
	if (nKey == PLGUIKEY_ESCAPE) {
		// Shut down the application
		Exit(0);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::OnDeInit()
{
	// Destroy the libRocket adapter instance
	if (m_pRocketAdapter) {
		delete m_pRocketAdapter;
		m_pRocketAdapter = nullptr;
	}

	// Call base implementation
	BasicSceneApplication::OnDeInit();
}

void Application::OnInit()
{
	// This method is call by the application framework when application should initialize itself.
	// At this point, the core components of the application are ready to be used.

	// Call base implementation
	BasicSceneApplication::OnInit();

	// Get the scene context
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		// Create the libRocket adapter instance
		m_pRocketAdapter = new libRocket_PL::libRocketAdapter(pSceneContext->GetRendererContext(), GetMainWindow());
		Rocket::Core::Context *pRocketContext = m_pRocketAdapter->GetRocketContext();
		if (pRocketContext) {
			// Get the application directory - look out! We can't just assume that the current work directory
			// is the same as were the executable is in. If we do so, for example starting the application by using
			// a MS Windows menu shortcut will not work... and just changing the current work directory by using
			// "PLGeneral::System::GetInstance()->SetCurrentDir(GetApplicationContext().GetAppDirectory())" isn't the polite way...
			const String sAppDirectory = GetApplicationContext().GetAppDirectory();

			// Load the fonts
			Rocket::Core::FontDatabase::LoadFontFace((sAppDirectory + "/Data/libRocket/Delicious-Roman.otf").GetUTF8());
			Rocket::Core::FontDatabase::LoadFontFace((sAppDirectory + "/Data/libRocket/Delicious-Bold.otf").GetUTF8());
			Rocket::Core::FontDatabase::LoadFontFace((sAppDirectory + "/Data/libRocket/Delicious-Italic.otf").GetUTF8());
			Rocket::Core::FontDatabase::LoadFontFace((sAppDirectory + "/Data/libRocket/Delicious-BoldItalic.otf").GetUTF8());

			{ // Load the mouse cursor and release the caller's reference
				Rocket::Core::ElementDocument *pElementDocumentCursor = pRocketContext->LoadMouseCursor((sAppDirectory + "/Data/libRocket/cursor.rml").GetUTF8());
				if (pElementDocumentCursor)
					pElementDocumentCursor->RemoveReference();
			}

			{ // Load the document and release the caller's reference
				Rocket::Core::ElementDocument *pElementDocumentDocument = pRocketContext->LoadDocument((sAppDirectory + "/Data/libRocket/demo.rml").GetUTF8());
				if (pElementDocumentDocument) {
					pElementDocumentDocument->Show();
					pElementDocumentDocument->RemoveReference();
				}
			}

			// Add libRocket scene renderer pass instance
			SceneRenderer *pSceneRenderer = GetSceneRendererTool().GetSceneRenderer();
			if (pSceneRenderer) {
				libRocket_PL::SRPlibRocket *pSRPlibRocket = m_pRocketAdapter->CreateSRPlibRocketInstance();
				if (pSRPlibRocket)
					pSceneRenderer->Add(*reinterpret_cast<SceneRendererPass*>(pSRPlibRocket));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLGui::GuiApplication functions       ]
//[-------------------------------------------------------]
void Application::OnCreateMainWindow()
{
	// Call base implementation
	BasicSceneApplication::OnCreateMainWindow();

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
//[ Private virtual PLEngine::BasicSceneApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreateScene(SceneContainer &cContainer)
{
	// Create a camera
	SceneNode *pCamera = cContainer.Create("PLScene::SNCamera", "FreeCamera", "Position=\"1 2 -3\" Rotation=\"25 210 0\"");
	if (pCamera && pCamera->IsInstanceOf("PLScene::SNCamera")) {
		// Make this to our main scene camera
		SetCamera(reinterpret_cast<SNCamera*>(pCamera));
	}

	// Create the floor
	cContainer.Create("PLScene::SNMesh", "Floor", "Position=\"0 0 -5\" Scale=\"4 0.1 4\" Mesh=\"Default\"");

	// Setup scene surface painter
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
		SPScene *pSPScene = static_cast<SPScene*>(pPainter);
		pSPScene->SetRootContainer(cContainer.GetContainer());
		pSPScene->SetSceneContainer(&cContainer);
	}

	// Set scene container
	SetScene(&cContainer);
}
