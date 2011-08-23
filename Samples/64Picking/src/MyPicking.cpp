/*********************************************************\
 *  File: MyPicking.cpp                                  *
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
#include <PLCore/Tools/Timing.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Button.h>
#include <PLEngine/Picking/PickingResult.h>
#include "Application.h"
#include "MyPicking.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLInput;
using namespace PLScene;
using namespace PLEngine;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MyPicking::MyPicking(Application &cApplication) : MousePicking(cApplication.GetFrontend()),
	m_pApplication(&cApplication),
	m_nLastPickingTime(Timing::GetInstance()->GetPastTime())
{
	// Set the camera used for picking
	SetCamera(m_pApplication->GetCamera());
}

/**
*  @brief
*    Destructor
*/
MyPicking::~MyPicking()
{
}

/**
*  @brief
*    Performs the picking
*/
void MyPicking::PerformPicking()
{
	// Get the default input controller of the application
	Controller *pController = reinterpret_cast<Controller*>(m_pApplication->GetInputController());
	if (pController && pController->GetActive()) {
		// Get the "MouseLeft" control
		Control *pControl = pController->GetControl("MouseLeft");
		if (pControl && pControl->GetType() == ControlButton) {
			Button *pButton = reinterpret_cast<Button*>(pControl);
			SceneNode *pPickedSceneNode = nullptr;

			// If the left mouse button is currently down, do NOT perform new picking
			if (!pButton->IsPressed()) {
				// Get the current time data
				const uint64 nPastTime = Timing::GetInstance()->GetPastTime();

				// Perform mouse picking - do not make this test each frame because it may cost some performance
				if ((nPastTime-m_nLastPickingTime) > 100) {
					m_nLastPickingTime = nPastTime;

					// Perform picking - "PerformMousePicking()" is using the current mouse position inside the main window
					// and the currently used camera in order to find the scene node under the mouse cursor
					PickingResult cPickingResult;
					if (PerformMousePicking(cPickingResult))
						pPickedSceneNode = cPickingResult.GetSceneNode();
				} else {
					// Use the previous result
					pPickedSceneNode = m_cCurrentPickedSceneNodeHandler.GetElement();
				}

				// Picked changed?
				if (pPickedSceneNode != m_cCurrentPickedSceneNodeHandler.GetElement()) {
					// Backup the currently picked scene node
					m_cCurrentPickedSceneNodeHandler.SetElement(pPickedSceneNode);
				}
			}

			// Is currently anything picked?
			if (pButton->IsHit() && pPickedSceneNode) {
				// Toggle the debug mode of the picked scene node
				if (pPickedSceneNode->GetDebugFlags() & SceneNode::DebugEnabled) {
					// Disable debug mode
					pPickedSceneNode->SetDebugFlags(pPickedSceneNode->GetDebugFlags() & ~SceneNode::DebugEnabled);
				} else {
					// Enable debug mode
					pPickedSceneNode->SetDebugFlags(pPickedSceneNode->GetDebugFlags() |SceneNode::DebugEnabled);
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::Picking functions           ]
//[-------------------------------------------------------]
bool MyPicking::OnPickingCandidate(SceneNode &cSceneNode)
{
	// Is this scene node visible? If so, we allow picking of it...
	return cSceneNode.IsVisible();
}
