/*********************************************************\
 *  File: DockWidgetSceneRendererQObject.cpp             *
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
#include <QtGui/qevent.h>
#include <QtGui/qdockwidget.h>
#include <PLCore/Base/Class.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLEngine/Application/EngineApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneRenderer.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneRendererQObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneRendererQObject::DockWidgetSceneRendererQObject(DockWidgetSceneRenderer &cDockWidgetSceneRenderer) :
	m_pDockWidgetSceneRenderer(&cDockWidgetSceneRenderer)
{
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneRendererQObject::~DockWidgetSceneRendererQObject()
{
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool DockWidgetSceneRendererQObject::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Widget is shown (do only take it into account if there's a valid scene renderer model instance)
	DataModels::SceneRendererDataModel::SceneRendererDataModel *pSceneRendererDataModel = m_pDockWidgetSceneRenderer->m_pSceneRendererDataModel;
	if (pSceneRendererDataModel && pQEvent->type() == QEvent::Show) {
		// Get encapsulated Qt dock widget
		QDockWidget *pQDockWidget = m_pDockWidgetSceneRenderer->GetQDockWidget();
		if (pQObject == pQDockWidget) {
			// The encapsulated Qt dock widget is shown, ensure that we have a scene renderer
			if (!pSceneRendererDataModel->GetSceneRenderer()) {
				// Set a default scene renderer to have a decent standard behaviour
				SceneRenderer *pSceneRenderer = nullptr;
				{
					CoreApplication *pApplication = CoreApplication::GetApplication();
					if (pApplication && pApplication->IsInstanceOf("PLEngine::EngineApplication"))
						pSceneRenderer = static_cast<PLEngine::EngineApplication*>(pApplication)->GetSceneRendererTool().GetSceneRenderer();
					m_pDockWidgetSceneRenderer->SelectSceneRenderer(pSceneRenderer);
				}

				// Set window title
				QString sQStringWindowTitle = pQDockWidget->tr(m_pDockWidgetSceneRenderer->GetClass()->GetProperties().Get("Title"));
				if (pSceneRenderer) {
					sQStringWindowTitle += ": ";
					sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + pSceneRenderer->GetName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
				}
				pQDockWidget->setWindowTitle(sQStringWindowTitle);
			}

			// Done - filter the event out, i.e. stop it being handled further
			return true;
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
