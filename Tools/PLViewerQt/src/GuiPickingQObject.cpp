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
	m_pGuiPicking(&cGuiPicking)
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
		// Mouse button double click (QMouseEvent)
		if (pQEvent->type() == QEvent::MouseButtonDblClick) {
			// Cast the received event to QMouseEvent
			QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

			// Left mouse button?
			if (pQMouseEvent->button() == Qt::LeftButton) {
				// Perform picking
				if (m_pGuiPicking) {
					SceneNode *pSceneNode = m_pGuiPicking->PerformPicking();

					// Perform a dock widget manager broadcast
					m_pGuiPicking->GetDockWidgetManager()->CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pSceneNode));

					// Done - filter the event out, i.e. stop it being handled further
					return true;
				}
			}
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}
