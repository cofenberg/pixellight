/*********************************************************\
 *  File: GuiPickingQObject.cpp                          *
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
	#include <QtGui/qevent.h>
	#include <PLFrontendQt/FrontendMainWindow.h>
PL_WARNING_POP
#include <PLFrontendQt/DockWidget/DockWidgetManager.h>
#include "Gui.h"
#include "GuiPicking.h"
#include "ApplicationQt.h"
#include "GuiPickingQObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLFrontendQt;
using namespace PLCore;
using namespace PLScene;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiPickingQObject::GuiPickingQObject(GuiPicking &cGuiPicking) :
	m_pGuiPicking(&cGuiPicking),
	m_bCameraDisabled(false)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = m_pGuiPicking->m_pGui->GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// This Qt object should receive events from the Qt main window
		pFrontendMainWindow->installEventFilter(this);
	}
}

/**
*  @brief
*    Destructor
*/
GuiPickingQObject::~GuiPickingQObject()
{
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool GuiPickingQObject::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = m_pGuiPicking->m_pGui->GetFrontendMainWindow();

	// Handle Qt main window events
	if (pQObject == pFrontendMainWindow) {
		switch (pQEvent->type()) {
			// Mouse button pressed (QMouseEvent)
			case QEvent::MouseButtonPress:
				// Is currently any of the transform gizmo axis selected?
				if (m_pGuiPicking->IsAnyTransformGizmoAxisSelected()) {
					// Disable the camera so one is able to play around with the transform gizmo without controlling the camera at the same time
					SceneNode *pSceneNode = reinterpret_cast<SceneNode*>(m_pGuiPicking->m_pGui->GetApplication().GetCamera());
					if(pSceneNode) {
						pSceneNode->SetActive(false);
						m_bCameraDisabled = true;

						// Done - filter the event out, i.e. stop it being handled further
						return true;
					}
				}
				break;

			// Mouse button released (QMouseEvent)
			case QEvent::MouseButtonRelease:
				// In case the camera was disabled by us, enable it
				if (m_bCameraDisabled) {
					SceneNode *pSceneNode = reinterpret_cast<SceneNode*>(m_pGuiPicking->m_pGui->GetApplication().GetCamera());
					if(pSceneNode) {
						pSceneNode->SetActive(true);
						m_bCameraDisabled = false;

						// Done - filter the event out, i.e. stop it being handled further
						return true;
					}
				}
				break;

			// Mouse button double click (QMouseEvent)
			case QEvent::MouseButtonDblClick:
			{
				// Cast the received event to QMouseEvent
				QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

				// Left mouse button?
				if (pQMouseEvent->button() == Qt::LeftButton) {
					// It appears that the user intends to select something
					// -> In case a transform gizmo axis is currently selected, ignore this request
					// -> The "m_bCameraDisabled" test is just there for safty, "usually" it is not possible to hold down
					//    the left mouse button while at the same time performing a double-click with it :D
					if (!m_pGuiPicking->IsAnyTransformGizmoAxisSelected() && !m_bCameraDisabled) {
						// Perform picking
						SceneNode *pSceneNode = m_pGuiPicking->PerformPicking();

						// Perform a dock widget manager broadcast
						m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pSceneNode));

						// Done - filter the event out, i.e. stop it being handled further
						return true;
					}
				}
				break;
			}
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}
