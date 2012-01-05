/*********************************************************\
 *  File: DockWidgetSceneRenderer.cpp                    *
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
#include <QtGui/qtreeview.h>
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <PLCore/Base/Class.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLEngine/Application/EngineApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetSceneRenderer)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneRenderer::DockWidgetSceneRenderer(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidgetScene(pQMainWindow, pDockWidgetManager),
	SlotOnDestroyed(this),
	m_pSceneRendererDataModel(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		pQDockWidget->setWidget(pQTreeView);
		m_pSceneRendererDataModel = new DataModels::SceneRendererDataModel::SceneRendererDataModel(pQDockWidget);
		pQTreeView->setModel(m_pSceneRendererDataModel);
		pQTreeView->expandToDepth(0);

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::BottomDockWidgetArea, pQDockWidget);

		// This Qt object should receive events from the encapsulated Qt dock widget
		pQDockWidget->installEventFilter(this);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneRenderer::~DockWidgetSceneRenderer()
{
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool DockWidgetSceneRenderer::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Widget is shown (do only take it into account if there's a valid scene renderer model instance)
	if (m_pSceneRendererDataModel && pQEvent->type() == QEvent::Show) {
		// Get encapsulated Qt dock widget
		QDockWidget *pQDockWidget = GetQDockWidget();
		if (pQObject == GetQDockWidget()) {
			// The encapsulated Qt dock widget is shown, ensure that we have a scene renderer
			if (!m_pSceneRendererDataModel->GetSceneRenderer()) {
				// Set a default scene renderer to have a decent standard behaviour
				SceneRenderer *pSceneRenderer = nullptr;
				{
					CoreApplication *pApplication = CoreApplication::GetApplication();
					if (pApplication && pApplication->IsInstanceOf("PLEngine::EngineApplication"))
						pSceneRenderer = static_cast<PLEngine::EngineApplication*>(pApplication)->GetSceneRendererTool().GetSceneRenderer();
					SelectSceneRenderer(pSceneRenderer);
				}

				// Set window title
				QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
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
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene renderer assigned with this dock widget was destroyed
*/
void DockWidgetSceneRenderer::OnDestroyed()
{
	// Argh! Mayday! We lost our scene renderer!
	// -> Now no scene renderer is currently selected
	SelectSceneRenderer(nullptr);

	// Get encapsulated Qt dock widget and hide it, it will get refreshed automatically when the encapsulated Qt dock widget is shown again
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget)
		pQDockWidget->hide();
}

/**
*  @brief
*    Selects the given scene renderer
*/
void DockWidgetSceneRenderer::SelectSceneRenderer(SceneRenderer *pSceneRenderer)
{
	// Is there a scene renderer model instance?
	if (m_pSceneRendererDataModel) {
		// Get the currently assigned scene renderer
		SceneRenderer *pCurrentSceneRenderer = m_pSceneRendererDataModel->GetSceneRenderer();

		// State change?
		if (pCurrentSceneRenderer != pSceneRenderer) {
			// Disconnect event handler
			if (pCurrentSceneRenderer)
				pCurrentSceneRenderer->EventDestroyed.Disconnect(SlotOnDestroyed);

			// Assign new scene renderer
			m_pSceneRendererDataModel->SetSceneRenderer(pSceneRenderer);

			// Connect event handler
			if (pSceneRenderer)
				pSceneRenderer->EventDestroyed.Connect(SlotOnDestroyed);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
