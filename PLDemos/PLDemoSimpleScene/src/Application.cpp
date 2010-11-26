/*********************************************************\
 *  File: Application.cpp                                *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Log/Log.h>
#include <PLCore/Tools/Localization.h>
#include <PLGui/Gui/Base/Keys.h>
#include <PLGui/Widgets/Widget.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SPScene.h>
#include <PLScene/Scene/SceneContainer.h>
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
	EventHandlerKeyDown(&Application::NotifyKeyDown, this)
{
	// Set application name and title
	SetName("PLDemoSimpleScene");
	SetTitle(PLT("PL simple scene demo"));
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
//[ Private virtual PLRenderer::RenderApplication functions ]
//[-------------------------------------------------------]
bool Application::OnUpdate()
{
	// One important word at the beginning: DON'T COPYCAT THIS!
	// The following is 'just' a simple demonstration how the scene graph 'can' be used. It's
	// definitely not good to update your scene nodes in the way you can see within this function.
	// Its quite to intricate, inflexible and not performant. Use for example a scene node modifier
	// added to your scene node (in this case 'the white light') for this job!

	// Call base implementation
	if (BasicSceneApplication::OnUpdate()) {
		// Get the scene container with our 'concrete scene'
		SceneContainer *pSceneContainer = GetScene();
		if (pSceneContainer) {
			// Get the scene node with the name 'Light' (our 'white light')
			SceneNode *pLight = pSceneContainer->Get("Light");
			if (pLight) {
				// This variable is used for the light animation. Its just static you keep the implementation
				// for a good demo overview completely within this function.
				static float fLightTimer = 0.0f;

				// We set the current light position using the RTTI class interface. This is quite comfortable
				// and universal because you haven't to care about the concrete class type - just set the
				// variable values. For performance critical situations it's recommened to avoid using this RTTI
				// functions to set your variables and use the conrete provided class interfaces instead.
				pLight->SetAttribute("Position", String::Format("%g %g %g", Math::Sin(fLightTimer),
					Math::Sin(fLightTimer)/2+2, -(Math::Cos(fLightTimer)+5)));

				// Update the light timer by using the time difference between the last and the current frame
				fLightTimer += Timing::GetInstance()->GetTimeDifference();
			}
		}

		// Done
		return true;
	} else {
		// Not updated
		return false;
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
		SetCamera((SNCamera*)pCamera);
	}

	// Create a scene node with the soldier mesh which can produce a shadow
	cContainer.Create("PLScene::SNMesh", "Soldier", "Flags=\"CastShadow|ReceiveShadow\" Position=\"0.0 0.1 -5.0\" Scale=\"0.008 0.008 0.008\" Mesh=\"Data/Meshes/Soldier.mesh\"");

	// Create a light source to illuminate the scene - this light can cast shadows
	cContainer.Create("PLScene::SNPointLight", "Light", "Flags=\"CastShadow|Flares|Corona\" Range=\"4\"");

	// Create the floor
	cContainer.Create("PLScene::SNMesh", "Floor", "Flags=\"CastShadow|ReceiveShadow\" Position=\"0.0 0.0 -5.0\" Rotation=\"0.0 180.0 0.0\" Scale=\"4.0 0.1 4.0\" Mesh=\"Default\"");

	// Setup scene surface painter
	SurfacePainter *pPainter = GetPainter();
	if (pPainter && pPainter->IsInstanceOf("PLScene::SPScene")) {
		SPScene *pSPScene = (SPScene*)pPainter;
		pSPScene->SetRootContainer(cContainer.GetContainer());
		pSPScene->SetSceneContainer(&cContainer);

		// Check renderer API and version number, if legacy hardware is used we can only
		// use a quite primitive scene renderer!
		String sSceneRenderer = "Deferred.sr";
		RendererContext *pRendererContext = GetRendererContext();
		if (pRendererContext) {
			Renderer &cRenderer = pRendererContext->GetRenderer();

			// OpenGL
			uint32 nVersion = 0;
			if (cRenderer.GetAPI(&nVersion) == "OpenGL") {
				if (nVersion < 14) {
					sSceneRenderer = DefaultSceneRenderer;
					PL_LOG(Warning, "Your graphics card is too old to support proper shader rendering. "
									"At least a OpenGL 1.4 compatible graphics card is recommended.")
				}

			// Direct3D
			} else if (cRenderer.GetAPI(&nVersion) == "Direct3D") {
				if (nVersion < 900) {
					sSceneRenderer = DefaultSceneRenderer;
					PL_LOG(Warning, "Your graphics card is too old to support proper shader rendering. "
									"At least a Direct3D 9 compatible graphics card is recommended.")
				}
			}
		}
		pSPScene->SetDefaultSceneRenderer(sSceneRenderer);
	}

	// Set scene container
	SetScene(&cContainer);
}
