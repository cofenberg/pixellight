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
	m_pTransformGizmo(nullptr)
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
						if (m_pTransformGizmo)
							m_pGuiPicking->SetTransformMode(*m_pTransformGizmo, true);
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
						m_pGuiPicking->SetTransformMode(*m_pTransformGizmo, false);
						m_pTransformGizmo = nullptr;
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
					// -> The "m_pTransformGizmo" test is just there for safty, "usually" it is not possible to hold down
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
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}
