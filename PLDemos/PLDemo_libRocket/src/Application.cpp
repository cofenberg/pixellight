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
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include <libRocket_PL/SRPlibRocket.h>
#include <libRocket_PL/FileInterfacePL.h>
#include <libRocket_PL/SystemInterfacePL.h>
#include <libRocket_PL/MessageFilterRocket.h>
#include <libRocket_PL/RenderInterfacePLShaders.h>
#include <PLGeneral/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Gui.h>
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() :
	EventHandlerKeyDown(&Application::NotifyKeyDown, this),
	m_pRocketContext(nullptr),
	m_pRocketRenderInterface(nullptr),
	m_pRocketSystemInterface(nullptr),
	m_pRocketFileInterface(nullptr),
	m_pMessageFilterRocket(nullptr)
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
	if (nKey == PLGUIKEY_ESCAPE)
		// Shut down the application
		Exit(0);
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ConsoleApplication functions  ]
//[-------------------------------------------------------]
void Application::OnDeInit()
{
	// Remove message filter that feeds PLGui messages into libRocket
	if (m_pMessageFilterRocket) {
		// PLGui destroys automatically the "m_pMessageFilterRocket"-instance
		Gui::GetSystemGui()->RemoveMessageFilter(m_pMessageFilterRocket);
		m_pMessageFilterRocket = nullptr;
	}

	// De-initialize libRocket
	if (m_pRocketContext) {
		m_pRocketContext->RemoveReference();
		m_pRocketContext = nullptr;
	}
	Rocket::Core::Shutdown();
	if (m_pRocketFileInterface) {
		delete m_pRocketFileInterface;
		m_pRocketFileInterface = nullptr;
	}
	if (m_pRocketSystemInterface) {
		delete m_pRocketSystemInterface;
		m_pRocketSystemInterface = nullptr;
	}
	if (m_pRocketRenderInterface) {
		delete m_pRocketRenderInterface;
		m_pRocketRenderInterface = nullptr;
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

	// Initialize libRocket
	InitRocket();
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


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes libRocket
*/
void Application::InitRocket()
{
	// Get the scene context
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		// Get the widget of the main window
		Widget *pMainWindow = GetMainWindow();

		// Create and set the render interface
		if (pMainWindow)
			m_pRocketRenderInterface = new libRocket_PL::RenderInterfacePLShaders(pSceneContext->GetRendererContext(), pMainWindow->GetSize().x, pMainWindow->GetSize().y);
		else
			m_pRocketRenderInterface = new libRocket_PL::RenderInterfacePLShaders(pSceneContext->GetRendererContext(), 640, 480);
		Rocket::Core::SetRenderInterface(m_pRocketRenderInterface);

		// Create and set the file interface
		m_pRocketFileInterface = new libRocket_PL::FileInterfacePL();
		Rocket::Core::SetFileInterface(m_pRocketFileInterface);

		// Create and set the system interface
		m_pRocketSystemInterface = new libRocket_PL::SystemInterfacePL();
		Rocket::Core::SetSystemInterface(m_pRocketSystemInterface);

		// Initialize libRocket
		Rocket::Core::Initialise();
		Rocket::Controls::Initialise();

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

		// Create and set the context
		if (pMainWindow)
			m_pRocketContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(pMainWindow->GetSize().x, pMainWindow->GetSize().y));
		else
			m_pRocketContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(640, 480));
		Rocket::Debugger::Initialise(m_pRocketContext);

		{ // Load the mouse cursor and release the caller's reference
			Rocket::Core::ElementDocument *pElementDocumentCursor = m_pRocketContext->LoadMouseCursor((sAppDirectory + "/Data/libRocket/cursor.rml").GetUTF8());
			if (pElementDocumentCursor)
				pElementDocumentCursor->RemoveReference();
		}

		{ // Load the document and release the caller's reference
			Rocket::Core::ElementDocument *pElementDocumentDocument = m_pRocketContext->LoadDocument((sAppDirectory + "/Data/libRocket/demo.rml").GetUTF8());
			if (pElementDocumentDocument) {
				pElementDocumentDocument->Show();
				pElementDocumentDocument->RemoveReference();
			}
		}

		// Add message filter that feeds PLGui messages from the content widget of the main window into libRocket
		m_pMessageFilterRocket = new libRocket_PL::MessageFilterRocket(*m_pRocketContext);
		// [TODO] Currently, when using an target widget, some events like mouse wheel or key are send from another widget than the content widget...
//		m_pMessageFilterRocket = new libRocket_PL::MessageFilterRocket(*m_pRocketContext, GetMainWindow() ? GetMainWindow()->GetContentWidget() : nullptr);
		Gui::GetSystemGui()->AddMessageFilter(m_pMessageFilterRocket);

		// Add libRocket scene renderer pass instance
		SceneRenderer *pSceneRenderer = GetSceneRendererTool().GetSceneRenderer();
		if (pSceneRenderer) {
			libRocket_PL::SRPlibRocket *pSRPlibRocket = new libRocket_PL::SRPlibRocket(*m_pRocketContext, *(static_cast<libRocket_PL::RenderInterfacePL*>(m_pRocketRenderInterface)));
			pSceneRenderer->Add(*pSRPlibRocket);
		}
	}
}
