/*********************************************************\
 *  File: GuiPickingQObject.cpp                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Timing.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	#include <QtGui/qevent.h>
	#include <PLFrontendQt/FrontendMainWindow.h>
PL_WARNING_POP
#include <PLFrontendQt/DockWidget/DockWidgetManager.h>
#include <PLScene/Scene/SceneNodeModifiers/SNMTransformGizmo.h>
#include "Gui.h"
#include "GuiPicking.h"
#include "ApplicationQt.h"
#include "GuiPickingQObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
using namespace PLFrontendQt;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiPickingQObject::GuiPickingQObject(GuiPicking &cGuiPicking) :
	m_pGuiPicking(&cGuiPicking),
	m_pTransformGizmo(nullptr),
	m_bCloneMode(false)
{
	// Get the Qt main window
	QWidget *pRenderWindow = m_pGuiPicking->m_pGui->GetFrontendMainWindow()->GetRenderWindow();
	if (pRenderWindow) {
		// This Qt object should receive events from the Qt window
		pRenderWindow->installEventFilter(this);
	}
}

/**
*  @brief
*    Destructor
*/
GuiPickingQObject::~GuiPickingQObject()
{
	// Are we currently in transform mode?
	if (m_pTransformGizmo)
		m_pGuiPicking->SetTransformMode(*m_pTransformGizmo, false);
}

/**
*  @brief
*    Starts the clone mode when all preconditions for it are satisfied and we're not already in clone mode
*/
void GuiPickingQObject::StartCloneMode()
{
	// Ignore this request in case we're already in clone mode, else: Are the preconditions satisfied?
	if (!m_bCloneMode && m_pTransformGizmo) {
		// Position transform gizmo
		if (m_pTransformGizmo->IsInstanceOf("PLScene::SNMTransformGizmoPosition")) {
			// Backup the current position of the owner scene node and start the clone mode
			m_vOriginalValue = m_pTransformGizmo->GetSceneNode().GetPosition();
			m_bCloneMode = true;

		// Rotation transform gizmo
		} else if (m_pTransformGizmo->IsInstanceOf("PLScene::SNMTransformGizmoRotation")) {
			// Backup the current rotation of the owner scene node and start the clone mode
			m_vOriginalValue = m_pTransformGizmo->GetSceneNode().GetTransform().GetRotation().fQ;
			m_bCloneMode = true;

		// Scale transform gizmo
		} else if (m_pTransformGizmo->IsInstanceOf("PLScene::SNMTransformGizmoScale")) {
			// Backup the current scale of the owner scene node and start the clone mode
			m_vOriginalValue = m_pTransformGizmo->GetSceneNode().GetScale();
			m_bCloneMode = true;
		}
	}
}

/**
*  @brief
*    Ends the clone mode and starts the clone action, but only if we're in fact in clone mode
*/
void GuiPickingQObject::EndCloneMode()
{
	// Ignore this request in case we're not in clone mode
	if (m_bCloneMode) {
		// Is the used transform gizmo still valid?
		if (m_pTransformGizmo) {
			// Stop transform mode
			SNMTransformGizmo *pTransformGizmo = m_pTransformGizmo;
			m_pGuiPicking->SetTransformMode(*m_pTransformGizmo, false);
			m_pTransformGizmo = nullptr;

			// Pointer to the last added scene node clone
			SceneNode *pSceneNodeClone = nullptr;

			// Position transform gizmo
			if (pTransformGizmo->IsInstanceOf("PLScene::SNMTransformGizmoPosition")) {
				// Get the scene node which should be cloned
				SceneNode &cSceneNode = pTransformGizmo->GetSceneNode();

				// Calculate the position delta
				const Vector3 vOriginal = m_vOriginalValue;
				const Vector3 vDelta    = cSceneNode.GetPosition() - vOriginal;

				// Set the original scene node back to it's original position
				Vector3 vCurrentPosition = vOriginal;
				cSceneNode.SetPosition(vCurrentPosition);

				// Ask the user for the number of desired clones (with a decent limited number)
				const uint32 nNumOfClones = GetNumOfClones();

				// Create the clones
				const int nIndex = cSceneNode.GetContainerIndex() + 1;
				for (uint32 i=0; i<nNumOfClones; i++) {
					// Create the clone
					const int nCurrentIndex = nIndex + i;
					pSceneNodeClone = cSceneNode.CloneAtIndex(nCurrentIndex);
					if (pSceneNodeClone) {
						// Advance the current position
						vCurrentPosition += vDelta;

						// Give this scene node clone the current position
						pSceneNodeClone->SetPosition(vCurrentPosition);

						// Perform a dock widget manager broadcast
						m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("AddedObject", Params<void, Object&, int>(*pSceneNodeClone, nCurrentIndex));
					}
				}

			// Rotation transform gizmo
			} else if (pTransformGizmo->IsInstanceOf("PLScene::SNMTransformGizmoRotation")) {
				// Get the scene node which should be cloned
				SceneNode &cSceneNode = pTransformGizmo->GetSceneNode();

				// Calculate the rotation delta
				Quaternion qOrignalRotationInverted = m_vOriginalValue.fV;
				qOrignalRotationInverted.UnitInvert();
				const Quaternion qDelta = qOrignalRotationInverted*cSceneNode.GetTransform().GetRotation();

				// Set the original scene node back to it's original rotation
				Quaternion qCurrentRotation = m_vOriginalValue.fV;
				cSceneNode.GetTransform().SetRotation(qCurrentRotation);

				// Ask the user for the number of desired clones (with a decent limited number)
				const uint32 nNumOfClones = GetNumOfClones();

				// Create the clones
				const int nIndex = cSceneNode.GetContainerIndex() + 1;
				for (uint32 i=0; i<nNumOfClones; i++) {
					// Create the clone
					const int nCurrentIndex = nIndex + i;
					pSceneNodeClone = cSceneNode.CloneAtIndex(nCurrentIndex);
					if (pSceneNodeClone) {
						// Advance the current rotation
						qCurrentRotation *= qDelta;

						// Give this scene node clone the current rotation
						pSceneNodeClone->GetTransform().SetRotation(qCurrentRotation);

						// Perform a dock widget manager broadcast
						m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("AddedObject", Params<void, Object&, int>(*pSceneNodeClone, nCurrentIndex));
					}
				}

			// Scale transform gizmo
			} else if (pTransformGizmo->IsInstanceOf("PLScene::SNMTransformGizmoScale")) {
				// Get the scene node which should be cloned
				SceneNode &cSceneNode = pTransformGizmo->GetSceneNode();

				// Calculate the scale delta
				const Vector3 vOriginal = m_vOriginalValue;
				const Vector3 vDelta    = cSceneNode.GetScale() - vOriginal;

				// Set the original scene node back to it's original scale
				Vector3 vCurrentScale = vOriginal;
				cSceneNode.SetScale(vCurrentScale);

				// Ask the user for the number of desired clones (with a decent limited number)
				const uint32 nNumOfClones = GetNumOfClones();

				// Create the clones
				const int nIndex = cSceneNode.GetContainerIndex() + 1;
				for (uint32 i=0; i<nNumOfClones; i++) {
					// Create the clone
					const int nCurrentIndex = nIndex + i;
					pSceneNodeClone = cSceneNode.CloneAtIndex(nCurrentIndex);
					if (pSceneNodeClone) {
						// Advance the current scale
						vCurrentScale += vDelta;

						// Give this scene node clone the current scale
						pSceneNodeClone->SetScale(vCurrentScale);

						// Perform a dock widget manager broadcast
						m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("AddedObject", Params<void, Object&, int>(*pSceneNodeClone, nCurrentIndex));
					}
				}
			}

			// Make the last added scene node clone to the currently selected scene node
			if (pSceneNodeClone) {
				// Perform a dock widget manager broadcast
				m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pSceneNodeClone));
			}
		}

		// End the clone mode
		m_bCloneMode = false;
	}
}

/**
*  @brief
*    Asks the user for the number of desired clones (with a decent limited number)
*/
uint32 GuiPickingQObject::GetNumOfClones() const
{
	// Pause timing
	// -> Avoids e.g. that the original scene node changes it's states via script, modifiers and so on
	// -> "Feels" right
	const bool bPausedBackup = Timing::GetInstance()->IsPaused();
	Timing::GetInstance()->Pause(true);

	// Ask the user for the number of desired clones (with a decent limited number)
	Array<String> lstNumberOfClones;
	for (uint32 i=1; i<11; i++)
		lstNumberOfClones.Add(i);
	const String sNumOfClones = m_pGuiPicking->m_pGui->InputDialog("Clone", "Please specify the number of clones", lstNumberOfClones);

	// Restore previous pause state
	Timing::GetInstance()->Pause(bPausedBackup);

	// Return the desired number of clones
	return sNumOfClones.GetLength() ? sNumOfClones.GetUInt32() : 0;
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool GuiPickingQObject::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Get the Qt main window
	QWidget *pRenderWindow = m_pGuiPicking->m_pGui->GetFrontendMainWindow()->GetRenderWindow();

	// Handle Qt main window events
	if (pQObject == pRenderWindow) {
		switch (pQEvent->type()) {
			// Mouse button pressed (QMouseEvent)
			case QEvent::MouseButtonPress:
			{
				// Cast the received event to QMouseEvent
				QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

				// Left mouse button?
				if (pQMouseEvent->button() == Qt::LeftButton) {
					// Are we currently in transform mode?
					if (!m_pTransformGizmo) {
						// Is currently any of the transform gizmo axis selected?
						m_pTransformGizmo = m_pGuiPicking->IsAnyTransformGizmoAxisSelected();
						if (m_pTransformGizmo) {
							// Start transform mode
							m_pGuiPicking->SetTransformMode(*m_pTransformGizmo, true);

							// Start the clone mode when all preconditions for it are satisfied and we're not already in clone mode
							if (pQMouseEvent->modifiers().testFlag(Qt::ShiftModifier))
								StartCloneMode();
						}
					}
				}

				// We do not filter out the event because we add only additional handling
				break;
			}

			// Mouse button released (QMouseEvent)
			case QEvent::MouseButtonRelease:
			{
				// Cast the received event to QMouseEvent
				QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

				// Left mouse button?
				if (pQMouseEvent->button() == Qt::LeftButton) {
					// Are we currently in transform mode?
					if (m_pTransformGizmo) {
						// End the clone mode and starts the clone action, but only if we're in fact in clone mode
						EndCloneMode();

						// Stop transform mode, if this was not already done
						if (m_pTransformGizmo) {
							m_pGuiPicking->SetTransformMode(*m_pTransformGizmo, false);
							m_pTransformGizmo = nullptr;
						}
					}
				}

				// We do not filter out the event because we add only additional handling
				break;
			}

			// Mouse button double click (QMouseEvent)
			case QEvent::MouseButtonDblClick:
			{
				// Cast the received event to QMouseEvent
				QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

				// Left mouse button?
				if (pQMouseEvent->button() == Qt::LeftButton) {
					// It appears that the user intends to select something
					// -> In case a transform gizmo axis is currently selected, ignore this request
					// -> The "m_pTransformGizmo" test is just there for safety, "usually" it is not possible to hold down
					//    the left mouse button while at the same time performing a double-click with it :D
					if (!m_pTransformGizmo && !m_pGuiPicking->IsAnyTransformGizmoAxisSelected()) {
						// Perform picking
						SceneNode *pSceneNode = m_pGuiPicking->PerformPicking();

						// Perform a dock widget manager broadcast
						m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pSceneNode));
					}
				}

				// We do not filter out the event because we add only additional handling
				break;
			}

			// Key pressed (QKeyEvent)
			case QEvent::KeyPress:
			{
				// Cast the received event to QKeyEvent
				QKeyEvent *pQKeyEvent= static_cast<QKeyEvent*>(pQEvent);

				// Evaluate the pressed key
				switch (pQKeyEvent->key()) {
					// Delete
					case Qt::Key_Delete:
						// Delete the currently selected scene node
						if (m_pGuiPicking->m_pSceneNode)
							m_pGuiPicking->m_pSceneNode->Delete();
						break;
				}
				break;
			}
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}
