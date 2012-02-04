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
#include <QtGui/qtreeview.h>
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include "PLFrontendQt/DataModels/PLTreeItemsDelegate.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneRendererQObject.h"
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
	m_pQTreeView(nullptr),
	m_pSceneRendererDataModel(nullptr),
	m_pDockWidgetSceneRendererQObject(new DockWidgetSceneRendererQObject(*this))
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		m_pQTreeView = new QTreeView();
		pQDockWidget->setWidget(m_pQTreeView);
		m_pSceneRendererDataModel = new DataModels::SceneRendererDataModel::SceneRendererDataModel(pQDockWidget);
		m_pQTreeView->setModel(m_pSceneRendererDataModel);
		m_pQTreeView->expandToDepth(0);
		m_pQTreeView->setDragEnabled(false);
        m_pQTreeView->setDragDropMode(QAbstractItemView::InternalMove);
        m_pQTreeView->setDefaultDropAction(Qt::IgnoreAction);

		// This item delegate adds additional (rudimentary) features when handling edits
		// -> See "DataModels::PLTreeItemsDelegate"-class documentation for details
		m_pQTreeView->setItemDelegate(new DataModels::PLTreeItemsDelegate);

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::BottomDockWidgetArea, pQDockWidget);

		// The Qt object should receive events from the encapsulated Qt dock widget
		pQDockWidget->installEventFilter(m_pDockWidgetSceneRendererQObject);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneRenderer::~DockWidgetSceneRenderer()
{
	// Destroy the QObject instance for Qt's signal/slot mechanisms
	delete m_pDockWidgetSceneRendererQObject;
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

			{ // Usability: Resize the first tree view column given to the size of its contents
				// No need to backup current expanded state and restore it after we're done because we set new content above resulting in that all is collapsed when we're in here
				m_pQTreeView->expandAll();
				m_pQTreeView->resizeColumnToContents(0);
				m_pQTreeView->collapseAll();
			}

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
