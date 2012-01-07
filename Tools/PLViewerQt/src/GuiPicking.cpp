/*********************************************************\
 *  File: GuiPicking.cpp                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	#include <QtGui/qlabel.h>
	#include <QtGui/qstatusbar.h>
PL_WARNING_POP
#include <PLCore/Tools/Timing.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLEngine/Picking/PickingResult.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include "Gui.h"
#include "ApplicationQt.h"
#include "GuiPicking.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
using namespace PLEngine;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(GuiPicking)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiPicking::GuiPicking(Gui &cGui) : DockWidget(nullptr, cGui.GetFrontendMainWindow() ? &cGui.GetFrontendMainWindow()->GetDockWidgetManager() : nullptr), MousePicking(cGui.GetApplication().GetFrontend()),
	m_pGui(&cGui),
	m_nLastPickingTime(Timing::GetInstance()->GetPastTime()),
	m_pQLabelStatusBar(new QLabel())
{
	// Get the Qt main window
	PLFrontendQt::FrontendMainWindow *pFrontendMainWindow = cGui.GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// Add to Qt main window status bar
		pFrontendMainWindow->statusBar()->addWidget(m_pQLabelStatusBar);
	}
}

/**
*  @brief
*    Destructor
*/
GuiPicking::~GuiPicking()
{
	// Destroy Qt label shown in the status bar of the Qt main window
	delete m_pQLabelStatusBar;
}

/**
*  @brief
*    Performs the informativ picking
*/
SceneNode *GuiPicking::PerformInformativPicking()
{
	// Get the current time data
	const uint64 nPastTime = Timing::GetInstance()->GetPastTime();

	// Perform mouse picking - do not make this test each frame because it may cost some performance
	if ((nPastTime-m_nLastPickingTime) > 100) {
		m_nLastPickingTime = nPastTime;

		// Perform picking
		return PerformPicking();
	}

	// Use the previous result as currently picked scene node
	return m_cCurrentPickedSceneNodeHandler.GetElement();
}

/**
*  @brief
*    Performs picking
*/
SceneNode *GuiPicking::PerformPicking()
{
	// Set the camera used for picking
	SetCamera(m_pGui->GetApplication().GetCamera());

	// Perform picking - "PerformMousePicking()" is using the current mouse position inside the main window
	// and the currently used camera in order to find the scene node under the mouse cursor
	PickingResult cPickingResult;
	SceneNode *pPickedSceneNode = nullptr;
	if (PerformMousePicking(cPickingResult))
		pPickedSceneNode = cPickingResult.GetSceneNode();

	// Picked changed?
	if (pPickedSceneNode != m_cCurrentPickedSceneNodeHandler.GetElement()) {
		// Backup the currently picked scene node
		m_cCurrentPickedSceneNodeHandler.SetElement(pPickedSceneNode);

		// Update the Qt label shown in the status bar of the Qt main window
		SetLabelStatusBarText(pPickedSceneNode ? pPickedSceneNode->GetAbsoluteName() : "");
	}

	// Done
	return pPickedSceneNode;
}

/**
*  @brief
*    Returns the used scene container
*/
SceneContainer *GuiPicking::GetSceneContainer() const
{
	return m_pGui->GetApplication().GetScene();
}

/**
*  @brief
*    Returns the currently selected object
*/
Object *GuiPicking::GetSelectedObject() const
{
	return m_cCurrentSelectedSceneNodeHandler.GetElement();
}

/**
*  @brief
*    Selects the given object
*/
void GuiPicking::SelectObject(Object *pObject)
{
	// We only know "PLScene::SceneNode" and "PLScene::SceneNodeModifier"
	SceneNode *pSceneNode = nullptr;
	if (pObject) {
		// Is it an "PLScene::SceneNode"-instance?
		if (pObject->IsInstanceOf("PLScene::SceneNode")) {
			pSceneNode = static_cast<SceneNode*>(pObject);

		// Is it an "PLScene::SceneNodeModifier"-instance?
		} else if (pObject->IsInstanceOf("PLScene::SceneNodeModifier")) {
			// Select the owner scene node of this scene node modifer
			pSceneNode = &static_cast<SceneNodeModifier*>(pObject)->GetSceneNode();
		}
	}

	// Get the previously selected scene node
	SceneNode *pPreviousSceneNode = m_cCurrentSelectedSceneNodeHandler.GetElement();

	// State change?
	if (pPreviousSceneNode != pSceneNode) {
		// Disable debug mode of the previous scene node, if there's one
		if (pPreviousSceneNode)
			pPreviousSceneNode->SetDebugFlags(pPreviousSceneNode->GetDebugFlags() & ~SceneNode::DebugEnabled);

		// Enable debug mode of the current scene node, if there's one
		if (pSceneNode)
			pSceneNode->SetDebugFlags(pSceneNode->GetDebugFlags() |SceneNode::DebugEnabled);

		// Backup the current scene node
		m_cCurrentSelectedSceneNodeHandler.SetElement(pSceneNode);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Set the text of the Qt label shown in the status bar of the Qt main window
*/
void GuiPicking::SetLabelStatusBarText(const String &sText)
{
	// Update the Qt label shown in the status bar of the Qt main window
	m_pQLabelStatusBar->setText(sText.GetLength() ? PLFrontendQt::QtStringAdapter::PLToQt("    Scene node: \"" + sText + "\" (double left click to select)") : "");
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::Picking functions           ]
//[-------------------------------------------------------]
bool GuiPicking::OnPickingCandidate(SceneNode &cSceneNode)
{
	// Is this scene node visible? If so, we allow picking of it...
	return cSceneNode.IsVisible();
}
